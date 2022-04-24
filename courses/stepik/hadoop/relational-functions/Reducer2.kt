fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map { it.trim().split("\t") }
        .groupBy({ it.last() }, { it.first() })
        .let { it["A"]?.intersect((it["B"] ?: emptySet()).toSet()) }
        ?.joinToString("\n")
        ?.let(::println)
}
