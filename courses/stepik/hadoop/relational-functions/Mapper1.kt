fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split("\t") }
        .filter { it.getOrNull(1) == "user10" }
        .map { it.joinToString(separator = "\t") }
        .joinToString(separator = "\n")
        .let(::println)
}
