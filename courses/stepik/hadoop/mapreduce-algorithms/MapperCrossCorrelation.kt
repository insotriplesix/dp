fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split(" ") }
        .map { words ->
            words.map { word ->
                words.mapNotNull { nextWord ->
                    if (word != nextWord) "$word,$nextWord" else null
                }
            }.flatten()
        }.flatten()
        .forEach(::printResult)
}

fun printResult(element: String) {
    println("$element\t1")
}
