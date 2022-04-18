fun main() {
    // put your code here
    generateSequence(::readLine)
        .joinToString("\n")
        .split("\n")
        .asSequence()
        .map { it.trim().split(" ") }
        .map { words ->
            words.map { word ->
                words.mapNotNull { nextWord ->
                    if (word != nextWord) "$word,$nextWord" else null
                }
            }
        }
        .flatten()
        .map { subList ->
            subList
                .map { it.split(",") }
                .groupBy({ it.first() }, { it.last() })
                .entries
                .map { entry ->
                    entry.key to entry.value
                        .map { word ->
                            "$word:${entry.value.count { it == word }}"
                        }
                        .toSet()
                        .joinToString(separator = ",")
                }
        }.flatten()
        .forEach(::printResult)
}

fun printResult(pair: Pair<String, String>) {
    println("${pair.first}\t${pair.second}")
}
