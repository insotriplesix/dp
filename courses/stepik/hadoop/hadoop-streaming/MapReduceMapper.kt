fun main() {
    // put your code here
    val input = generateSequence(::readLine).joinToString(" ")
    val words = input.split(' ')
    for (word in words) {
        println("$word\t1")
    }
}
