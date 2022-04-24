fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split("\t") }
        .map {
            val action = it.last().split(":")
            Triple(it.first(), action.first(), action.last())
        }
        .groupBy({ it.first }, { it.second to it.third })
        .map { entry ->
            val queries = entry.value
                .filter { it.first == "query" }
                .map { it.second }
            val urls = entry.value
                .filter { it.first == "url" }
                .map { it.second }
            val zipped = queries.map { q -> urls.map { u -> q to u  } }.flatten()

            zipped.map { "${entry.key}\t${it.first}\t${it.second}" }
        }
        .flatten()
        .forEach(::println)
}
