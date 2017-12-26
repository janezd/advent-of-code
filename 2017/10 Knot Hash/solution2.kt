import java.io.File

fun toHex(x: Int) : String {
    return (x + (if (x < 10) 48 else 87)).toChar().toString()
}

fun main(args: Array<String>) {
    var numbers = MutableList<Int>(256, { it })
    var skip = 0
    var position = 0
    val lengths = File("input.txt").readBytes().map { it.toInt() } + arrayOf(17, 31, 73, 47, 23)
    println(lengths)
    for(r in 1..64) {
        for(length in lengths) {
            for (i in 0..length/2-1) {
                val a = (position + i) % 256
                val b = (position + length-1  - i) % 256
                val t = numbers[a]
                numbers[a] = numbers[b]
                numbers[b] = t
            }
            position = (position + length + skip) % 256
            skip++
        }
    }
    var result = ""
    for(block in 0..255 step 16) {
        var t = 0
        for(el in block..block+15) {
            t = t xor numbers[el]
        }
        result += toHex(t / 16) + toHex(t % 16)
    }
    println(result)
}
