import java.io.File

fun divs(line: List<Int>): Int {
    line.forEach { x ->
        line.forEach { y ->
            if (x !=  y && x % y == 0) {
                return x / y
            }
        }
    }
    return 0
}


fun main(args: Array<String>) {
    val sheet = File("input.txt")
                 .readLines()
                 .map { it.split(' ', '\t')
                 .map { it.toInt() } }
    println(sheet.sumBy { it.max()!! - it.min()!! })

    // Part 2 with divs
    println(sheet.sumBy(::divs))

    // Part 2 with lambda
    println(sheet.sumBy { line ->
        line.forEach{ x ->
            line.forEach { y ->
                if (x !=  y && x % y == 0) {
                    return@sumBy x / y
                }
            }
        }
        return@sumBy 0
    })

    // Solution from Reddit
    println(sheet.sumBy {
        it.map { x -> it.map { y -> Pair(x, y) } }
        .flatten()
        .filter { it.first != it.second }
        .first { it.first % it.second == 0 }
        .run { this.first / this.second }
    })
}
