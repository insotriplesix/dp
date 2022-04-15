fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .map {
            it.trim().split("\t").let { element -> element.first() to element.last() }
        }
        .groupBy {
            it.first
        }
        .map {
            it.key to it.value.fold(0) { acc, pair -> acc + pair.second.toInt() }
        }
        .joinToString(separator = "") {
            it.first + "\t" + it.second + "\n"
        }
        .let {
            println(it)
        }
}
