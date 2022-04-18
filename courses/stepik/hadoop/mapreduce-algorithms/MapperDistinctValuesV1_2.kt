fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map { it.trim().split(",").last() }
        .forEach(::printResult)
}

fun printResult(element: String) {
    println("$element\t1")
}
