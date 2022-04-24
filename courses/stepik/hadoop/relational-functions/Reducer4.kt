fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map { it.trim().split("\t") }
        .groupBy({ it.last() }, { it.first() })
        .let {
            val diffA = it["A"]?.minus((it["B"] ?: emptySet()).toSet())
            val diffB = it["B"]?.minus((it["A"] ?: emptySet()).toSet()) ?: emptySet()
            diffA?.union(diffB)?.sorted()
        }
        ?.joinToString("\n")
        .let(::println)
}
