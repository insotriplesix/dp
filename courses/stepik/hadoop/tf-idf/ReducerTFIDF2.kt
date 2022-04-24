fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split("\t") }
        .map { line ->
            val word = line.first()
            val (docNumber, count, one) = line.last().split(";", limit = 3)
            word to Triple(docNumber, count, one)
        }
        .groupBy({ it.first }, { it.second })
        .map {
            val n = it.value.fold(0) { acc, triple -> acc + triple.third.toInt() }
            it.value.map { triple ->
                "${it.key}#${triple.first}\t${triple.second}\t$n"
            }
        }
        .flatten()
        .forEach(::println)
}
