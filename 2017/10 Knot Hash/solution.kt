import java.io.File

fun main(args: Array<String>) {
    var numbers = MutableList<Int>(256, { it })
    var skip = 0
    var position = 0
    File("input.txt")
    .readText()
    .split(',')
    .map { it.toInt() }
    .forEach { length ->
        println("$position $length $skip")
        for (i in 0..length/2-1) {
            val a = (position + i) % 256
            val b = (position + length-1  - i) % 256
            val t = numbers[a]
            numbers[a] = numbers[b]
            numbers[b] = t
        }
        position = (position + length + skip) % 256
        skip++
        println(numbers)
    }
    println(numbers[0] * numbers[1])
}
