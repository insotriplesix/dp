fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map {
            it.trim().split("\t")
        }
        .map { line ->
            line.first() to line.last().split(",")
        }
        .map { pair ->
            pair.second.map { pair.first + ',' + it }
        }
        .flatten()
        .forEach(::printResult)
}

fun printResult(element: String) {
    println("$element\t1")
}
