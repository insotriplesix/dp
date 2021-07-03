import kotlin.math.floor
import kotlin.math.min
 
fun main() {
    repeat(readLine()!!.toInt()) {
        readLine()!!
            .split(' ')
            .map { it.toInt() }
            .let { Pair(it[0], it[1]) }
            .let { (n, k) ->
                if (floor(n % k.toDouble()).toInt() != 0) {
                    Triple(true, n, k)
                } else {
                    Triple(false, n, k)
                }
            }
            .let { (isOdd, n, k) ->
                val freq = floor(n / k.toDouble()).toInt()
                val sb = StringBuilder()
                for (i in 97 until 97 + min(n / freq, k)) {
                    sb.append(i.toChar().toString().repeat(freq))
                }
                if (isOdd) {
                    for (i in 97 until 97 + (n - sb.length)) {
                        sb.append(i.toChar().toString())
                    }
                }
                println(sb.toString())
            }
    }
}
