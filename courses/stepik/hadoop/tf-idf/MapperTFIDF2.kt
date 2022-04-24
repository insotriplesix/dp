fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map {
            val elements = it.trim().split("\t")
            Triple(elements[0], elements[1], elements[2])
        }
        .map { "${it.first}\t${it.second};${it.third};1" }
        .forEach(::println)
}
