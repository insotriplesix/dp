////////////////////////////////////////////////////////////////////////////////////////////////
/*
@DynamicTest

@TestFactory

@SyncTable

@FeignClient

@KafkaListener, @KafkaHandler, @Payload

@Validated

@RelaxedMockK

@EnableCaching

@EventListener

@DecoratedWith

@AbstractErrorWebExceptionHandler

@DefaultErrorAttributes

@KafkaTemplate

@SoftAssertions

@AbstractHealthIndicator
*/
////////////////////////////////////////////////////////////////////////////////////////////////

private inline fun <reified T> readJsonFile(s: String): List<T> {
	val ref = jsonMapper.getTypeFactory().constructCollectionType(List::class.java, T::class.java)
	val source = resourceLoader.getResource(s)
	return jsonMapper.readValue(source.inputStream, ref)
}

////////////////////////////////////////////////////////////////////////////////////////////////

@Bean
fun objectMapper(): ObjectMapper {
	val mapper = ObjectMapper()
	mapper.propertyNamingStrategy = PropertyNamingStrategy.LOWER_CAMEL_CASE
	mapper.registerKotlinModule()
	mapper.disable(DeserializationFeature.FAIL_ON_IGNORED_PROPERTIES)
	mapper.disable(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES)
        	.registerModule(Jdk8Module())
        	.registerModule(JavaTimeModule()) // Поддержка Java 8 типов даты/времени (спецификация JSR-310)
        	.disable(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS)

	return mapper
}

////////////////////////////////////////////////////////////////////////////////////////////////

@Configuration
public class JsonConfig {

	@Bean
	public ObjectMapper objectMapper() {
    	ObjectMapper mapper = new ObjectMapper();
    	mapper.registerModules(getSimpleModule(), new Jdk8Module(), new JavaTimeModule())
        	.disable(DeserializationFeature.FAIL_ON_IGNORED_PROPERTIES)
        	.disable(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES)
        	.disable(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS)
        	.setSerializationInclusion(JsonInclude.Include.NON_NULL)
        	.setPropertyNamingStrategy(PropertyNamingStrategy.LOWER_CAMEL_CASE);
    	return mapper;
	}

	@NotNull
	private SimpleModule getSimpleModule() {
    	SimpleModule module = new SimpleModule();
    	module.addSerializer(CamundaVariableType.class, new CamundaVariableTypeSerializer());
    	LocalDateSerializer dateSerializer = new LocalDateSerializer(DateTimeFormatter.ofPattern("yyyy-MM-dd"));
    	module.addSerializer(LocalDate.class, dateSerializer);
    	return module;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////

@Configuration
class JsonConfig {

	@Bean
	fun getGson(): Gson =
    	GsonBuilder()
        	.setPrettyPrinting()
        	.serializeNulls()
        	.setFieldNamingStrategy(FieldNamingPolicy.LOWER_CASE_WITH_UNDERSCORES)
        	.create()

}

////////////////////////////////////////////////////////////////////////////////////////////////

@Bean
public SecurityContext securityContext() {
	return SecurityContext.builder()
        	.securityReferences(defaultAuth())
        	.forPaths(PathSelectors.any())
        	.build();
}

public List<SecurityReference> defaultAuth() {
	AuthorizationScope authorizationScope = new AuthorizationScope("global", "accessEverything");
	AuthorizationScope[] scopes = new AuthorizationScope[]{authorizationScope};
	return Arrays.asList(new SecurityReference("JWT", scopes));
}

////////////////////////////////////////////////////////////////////////////////////////////////

// Этот класс необходим для возможности корректного выключения трейсинга:
// 	https://github.com/opentracing-contrib/java-spring-jaeger#completely-disable-tracing

@ConditionalOnProperty(value = ["opentracing.jaeger.enabled"], havingValue = "false", matchIfMissing = false)
@Configuration
class TracingConfig {

	@Bean
	fun jaegerTracer(): Tracer =
    	JaegerTracer
        	.Builder("egr")
        	.withReporter(InMemoryReporter())
        	.withSampler(ConstSampler(false))
        	.build()


}

////////////////////////////////////////////////////////////////////////////////////////////////

private fun parseHost(host: String): Array<String> {
	val split = host.split(":".toRegex()).dropLastWhile { it.isEmpty() }.toTypedArray()
	if (split.size != 2 || !split[1].matches("[0-9]+".toRegex())) {
    	throw ArangoDBException(
        	"Could not load host '$host' from property-value spring.data.arangodb.hosts. Expected format ip:port,ip:port,..."
    	)
	}
	return split
}

////////////////////////////////////////////////////////////////////////////////////////////////

private fun String?.toLocalDateTime(): LocalDateTime? =
	this?.ifBlank { null }?.let { stringDate ->
    	try {
        	LocalDateTime.parse(stringDate).withNano(0)
    	} catch (e: DateTimeParseException) {
        	logger.error("Не удалось сконвертировать строку [$stringDate] в дату!")
        	null
    	}
	}

private fun String?.toLocalDate(): LocalDate? =
	this?.ifBlank { null }?.let { stringDate ->
    	try {
        	LocalDate.parse(stringDate)
    	} catch (e: DateTimeParseException) {
        	logger.error("Не удалось сконвертировать строку [$stringDate] в дату!")
        	null
    	}
	}

////////////////////////////////////////////////////////////////////////////////////////////////

@Component
class AppMetrics(private val meterRegistry: MeterRegistry) {

	// Метрика: Время обработки пачки транзакций
	private val batchProcessingTime = Timer
        	.builder("migration-transactions.batchProcessingTime")
        	.description("Время обработки пачки транзакций")
        	.tags("migration-transactions", "batchProcessingTime")
        	.register(meterRegistry)

	// Метрика: Время преобразования транзакции
	private val transactionConvTime = Timer
        	.builder("migration-transactions.transactionConvTime")
        	.description("Время преобразования транзакции")
        	.tags("migration-transactions", "transactionConvTime")
        	.register(meterRegistry)

	// Метрика: Количество обработанных пачек
	private val processedBatchCount = Counter
        	.builder("migration-transactions.processedBatchCount")
        	.description("Количество обработанных пачек")
        	.tags("migration-transactions", "processedBatchCount")
        	.register(meterRegistry)

	// Метрика: Количество преобразованных транзакций
	private val convertedTransactionCount = Counter
        	.builder("migration-transactions.convertedTransactionCount")
        	.description("Количество преобразованных транзакций")
        	.tags("migration-transactions", "convertedTransactionCount")
        	.register(meterRegistry)

	// Метрика: Количество ошибок при обработке пачек
	private val batchProcessingExceptionsCount = Counter
        	.builder("migration-transactions.batchProcessingExceptionsCount")
        	.description("Количество ошибок при обработке пачек")
        	.tags("migration-transactions", "batchProcessingExceptionsCount")
        	.register(meterRegistry)

	// Метрика: Количество ошибок при преобразовании транзакций
	private val transactionConvExceptionsCount = Counter
        	.builder("migration-transactions.transactionConvExceptionsCount")
        	.description("Количество ошибок при преобразовании транзакций")
        	.tags("migration-transactions", "transactionConvExceptionsCount")
        	.register(meterRegistry)

	private fun <T> timeMeter(timer: Timer, counter: Counter, exceptionCounter: Counter, block: () -> T): T {
    	val startTime = System.nanoTime()
    	return try {
        	block()
                	.also { timer.record(System.nanoTime() - startTime, TimeUnit.NANOSECONDS) }
                	.also { counter.increment() }
    	} catch (e: Throwable) {
        	exceptionCounter.increment()
        	throw e
    	}
	}

	// Измеритель метрик для обработки пачек
	fun <T> batchProcessingMeter(block: () -> T): T =
        	timeMeter(batchProcessingTime, processedBatchCount, batchProcessingExceptionsCount, block)

	// Измеритель метрик для преобразования транзакций
	fun <T> transactionConvMeter(block: () -> T): T =
        	timeMeter(transactionConvTime, convertedTransactionCount, transactionConvExceptionsCount, block)

}


@KafkaHandler
fun processDocument(documents: List<Document?>) {
	logger.info { ">>> Обработка батча размером [${documents.size}]" }
	appMetrics.batchProcessingMeter {
    	transactionRepository.saveAll(
            	documents
                    	.asSequence()
                    	.filter { validateAllKey(it) }
                    	.onEach { accountKafkaTemplate.send(accountKafkaTemplate.defaultTopic, it?.payerAccount) }
                    	.onEach { accountKafkaTemplate.send(accountKafkaTemplate.defaultTopic, it?.recipientAccount) }
                    	.map {
                        	appMetrics.transactionConvMeter {
                            	documentMapper.convert(it)
                        	}
                    	}
                    	.filterIsInstance<Transaction>()
    	)
	}
	logger.info { "<<< Завершена обработка батча размером [${documents.size}]" }
}

////////////////////////////////////////////////////////////////////////////////////////////////

final inline fun <reified W : Any> executeQuery(q: String): List<W> {
    	val cursor = template.query(q, W::class.java)
    	return cursor.asListRemaining() ?: emptyList()
	}

final inline fun <reified W : Any> executeQuery(q: String): List<W> = executeQuery(q, emptyMap())

final inline fun <reified W : Any> executeQuery(q: String, bindVars: Map<String, Any>): List<W> {
	val cursor = template.query(q, bindVars, W::class.java)
	return cursor.asListRemaining() ?: emptyList()
}

////////////////////////////////////////////////////////////////////////////////////////////////

// Время расчета риск-профиля
	suspend fun calcRiskProfileTimeMeter(block: suspend () -> RiskProfileInfo?): RiskProfileInfo? {
    	val sample = Timer.start(meterRegistry)
    	return block()
        	.also {
            	sample.stop(
                	meterRegistry.timer(
                    	"risk-profile.timer.calcRiskProfile",
                    	"risk-profile",
                    	it?.code ?: ClientRiskProfile.undefine.code
                	)
            	)
        	}
	}

	// Время обработки фактора для риск-профиля
	fun <T> calcFactorTimeMeter(factorCode: String, block: () -> T): T {
    	val sample = Timer.start(meterRegistry)
    	return block()
        	.also {
            	sample.stop(
                	meterRegistry.timer(
                    	"risk-profile.timer.clientFactorCalc",
                    	"factors",
                    	factorCode
                	)
            	)
        	}
	}

////////////////////////////////////////////////////////////////////////////////////////////////

@Configuration
@ComponentScan("ru.cft.aml")
@ConditionalOnClass(ArangoDatabase::class, HealthIndicator::class, HealthIndicatorAutoConfiguration::class)
@ConditionalOnBean(ArangoDatabase::class)
@ConditionalOnEnabledHealthIndicator("arango")
@AutoConfigureBefore(HealthIndicatorAutoConfiguration::class)
class ArangoHealthIndicatorAutoConfiguration(
	private val arangoDatabase: ArangoDatabase
) : CompositeHealthIndicatorConfiguration<ArangoHealthIndicator, ArangoDatabase>() {

	@Bean
	@ConditionalOnMissingBean(name = ["arangoHealthIndicator"])
	fun arangoHealthIndicator(): HealthIndicator {
    	return createHealthIndicator(arangoDatabase)
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////

@Component
class GlobalErrorAttributes : DefaultErrorAttributes() {

	private companion object : KLogging()

	override fun getErrorAttributes(request: ServerRequest, includeStackTrace: Boolean): Map<String, Any> {
    	val map = super.getErrorAttributes(request, includeStackTrace)

    	return when (val error = getError(request)) {
        	is GlobalException -> {
            	logger.debug(error) {
                	"Бизнес ошибка при REST запросе"
            	}

            	map.apply {
                	this["exception"] = error.javaClass.simpleName
                	this["message"] = error.message
                	this["status"] = error.status.value()
                	this["error"] = error.status.reasonPhrase
            	}
        	}

        	is WebExchangeBindException -> {
            	logger.debug(error) {
                	"Невалидные данные в запросе"
            	}

            	val errors =
                    	error.fieldErrors
                            	.map {
                                	ValidationError(
                                        	field = it.field,
                                        	message = it.defaultMessage ?: "WTF"
                                	)
                            	}

            	mapOf(
                    	"message" to "Невалидные данные в запросе",
                    	"status" to "400",
                    	"errors" to errors
            	)
        	}

        	is ExpiredJwtException -> {
            	mapOf("status" to HttpStatus.UNAUTHORIZED.value(),
                    	"error" to error.message
            	) as Map<String, Any>
        	}

        	is WriterException -> {
            	map.apply {
                	this["exception"] = error.javaClass.simpleName
                	this["message"] = "Не удалось создать файл. Список данных пуст!"
                	this["status"] = 400
            	}
        	}

        	is CheckColumnException -> {
            	map.apply {
                	this["exception"] = error.javaClass.simpleName
                	this["message"] = "Не удалось создать файл. Запрашиваемого поля в выборке данных не существует!"
                	this["status"] = 400
            	}
        	}

        	else -> {
            	logger.error(error) {
                	"Системная ошибка REST запроса"
            	}

            	map.apply {
                	this["message"] = "Непредвиденная ошибка на сервере, обратитесь к администратору"
                	this["status"] = "500"
                	this["error"] = "Системная ошибка"
            	}
        	}
    	}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////

. . .
