fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split("\t") }
        .map { it.last() to "${it.first()}${it.last()}" }
        .groupBy({ it.first }, { it.second })
        .mapValues { it.value.toSet().size }
        .forEach(::printResult)
}

fun printResult(entry: Map.Entry<String, Int>) {
    println("${entry.key}\t${entry.value}")
}
