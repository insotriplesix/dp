import kotlin.math.absoluteValue
 
fun main() {
    readLine()!!.toInt()
    readLine()!!
        .split(' ')
        .map { it.toInt() }
        .sorted()
        .windowed(2, 2)
        .sumOf { team ->
            (team.first() - team.last()).absoluteValue
        }
        .also {
            print(it)
        }
}
