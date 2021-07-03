fun main() {
    repeat(readLine()!!.toInt()) {
        readLine()!!
            .split(' ')
            .sumOf { it.toInt() }
            .also { println(it) }
    }
}
