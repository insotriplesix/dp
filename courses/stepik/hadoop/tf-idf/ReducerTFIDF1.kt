fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split("\t") }
        .map { line ->
            val (word, docNumber) = line.first().split("#", limit = 2)
            val one = line.last()
            line.first() to Triple(word, docNumber, one)
        }
        .groupBy({ it.first }, { it.second })
        .map {
            val (word, docNumber, _) = it.value.first()
            val count = it.value.fold(0) { acc, triple -> acc + triple.third.toInt() }
            "$word\t$docNumber\t$count"
        }
        .forEach(::println)
}
