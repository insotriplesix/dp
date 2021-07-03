import kotlin.math.floor
 
fun main() {
    repeat(readLine()!!.toInt()) {
        readLine()!!
            .split(' ')
            .map { it.toLong() }
            .let { Triple(it[0], it[1], it[2]) }
            .let { (a, b, n) ->
                if (floor(n % 2.0).toInt() != 0) {
                    Pair(a * (floor(n / 2.0) + 1).toLong(), b * floor(n / 2.0).toLong())
                } else {
                    Pair(a * (floor(n / 2.0)).toLong(), b * floor(n / 2.0).toLong())
                }
            }
            .let { (r, l) ->
                println(r - l)
            }
    }
}
