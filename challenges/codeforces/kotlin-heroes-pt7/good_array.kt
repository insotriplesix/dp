fun main() {
    readLine()!!.toInt()
    readLine()!!
        .split(' ')
        .map { it.toLong() }
        .getBeautyIndices()
        .also { result ->
            println(result.size)
            println(result.joinToString(separator = " "))
        }
}
 
fun List<Long>.getBeautyIndices(): List<Int> {
    val newList = mutableListOf<Int>()
    val totalSum = this.sum()
    var totalMax = 0L
    var innerMax = 0L
    var idx = 0
 
    this
        .onEachIndexed { index, elem ->
            if (elem > totalMax) {
                totalMax = elem
                idx = index
            }
        }
        .onEachIndexed { index, elem ->
            if (index != idx) {
                innerMax = kotlin.math.max(elem, innerMax)
            }
        }
        .forEachIndexed { j, elem ->
            if (elem == totalMax) {
                if (totalSum - elem - innerMax == innerMax) {
                    newList.add(j + 1)
                }
            } else {
                if (totalSum - elem - totalMax == totalMax) {
                    newList.add(j + 1)
                }
            }
        }
 
    return newList
}
