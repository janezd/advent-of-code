import java.io.File

fun main(args: Array<String>) {
    var numbers = File("input.txt").readLines().map { it.toInt() }.toMutableList()
    var pos = 0
    var steps = 0
    while (pos < numbers.size) {
        numbers[pos]++
        pos = pos + numbers[pos] - 1
        steps++
    }
    println(steps)

    numbers = File("input.txt").readLines().map { it.toInt() }.toMutableList()
    pos = 0
    steps = 0
    while (pos < numbers.size) {
        var next = pos + numbers[pos]
        if (numbers[pos] >= 3) numbers[pos]-- else numbers[pos]++
        pos = next
        steps++
    }
    println(steps)

}