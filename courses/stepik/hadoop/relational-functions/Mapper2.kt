fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .joinToString(separator = "\n") { it.trim().split("\t").last() }
        .let(::println)
}
