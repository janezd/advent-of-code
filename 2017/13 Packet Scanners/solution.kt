import java.io.File

fun main(args: Array<String>) {
    val scanners = File("input.txt")
                   .readLines()
                   .map { it.split(": ").map { it.toInt() } }

    println(scanners
            .filter { it[0] % (2 * it[1] - 2) == 0 }
            .sumBy { it[0] * it[1] })

    var delay = 0
    while(scanners.any { (it[0] + delay) % (2 * it[1] - 2) == 0 }) {
        delay++
    }
    println(delay)
}
