fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map {
            it.trim().split(" ")
        }
        .map {
            it.groupingBy { word -> word }.eachCount()
        }
        .forEach {
            it.entries.forEach(::printResult)
        }
}

fun printResult(entry: Map.Entry<String, Int>) {
    println("${entry.key}\t${entry.value}")
}
