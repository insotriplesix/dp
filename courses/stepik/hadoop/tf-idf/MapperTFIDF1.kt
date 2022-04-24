fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split(":", limit = 2) }
        .map { it.first() to it.last().replace(regex = Regex("[^a-zA-Z0-9]"), " ") }
        .map { it.first to it.second.split(" ") }
        .map { pair -> pair.first to pair.second.filter { it.isNotEmpty() } }
        .map { pair -> pair.second.map { "$it#${pair.first}\t1" } }
        .map { it.joinToString("\n") }
        .joinToString(separator = "\n")
        .let(::println)
}
