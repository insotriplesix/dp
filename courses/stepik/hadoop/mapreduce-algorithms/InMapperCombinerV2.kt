fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map {
            it.trim().split(" ")
        }
        .map {
            it.groupingBy { word -> word }.eachCount()
        }
        .flatMap { it.entries }
        .groupBy { it.key }
        .mapValues { entry -> entry.value.sumOf { it.value } }
        .forEach(::printResult)
}

fun printResult(entry: Map.Entry<String, Int>) {
    println("${entry.key}\t${entry.value}")
}
