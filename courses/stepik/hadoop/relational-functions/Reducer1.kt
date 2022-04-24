fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map { it.trim().split("\t").first() }
        .toSet()
        .forEach(::println)
}
