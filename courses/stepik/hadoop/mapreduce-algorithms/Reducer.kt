fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map {
            it.trim().split("\t")
        }
        .groupBy({ it.first() }, { it.last().toInt() })
        .mapValues { entry -> entry.value.sum() / entry.value.size }
        .forEach(::printResult)
}

fun printResult(entry: Map.Entry<String, Int>) {
    println("${entry.key}\t${entry.value}")
}
