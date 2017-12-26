import java.io.File

fun knot_hash(lengths: List<Int>) : Array<Int> {
    var numbers = MutableList<Int>(256, { it })
    var skip = 0
    var position = 0
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
    var hash = Array<Int>(16, { 0 })
    for(block in 0..255 step 16) {
        var t = 0
        for(el in block..block+15) {
            t = t xor numbers[el]
        }
        hash[block / 16] = t
    }
    return hash
}

fun ones(hash: Array<Int>): Int { 
    return hash.sumBy {h -> (0..15).sumBy { (h shr it) % 2 } }
}


fun is1(x: Int, y: Int, hashes: List<Array<Int>>) : Boolean {
    return (hashes[y][x / 8] and (128 shr (x % 8))) != 0
}

fun to_code(x: Int, y: Int) : Int {
    return x + 128 * y
}

fun main(args: Array<String>) {
    val hashes = (0..127).map {
        knot_hash(("vbqugkhl-" + it.toString()).map { it.toChar().toInt() } + arrayOf(17, 31, 73, 47, 23))
    }
    println(hashes.sumBy(::ones))

    File("connections.txt").printWriter().use { out ->
        for(y in 0..127) {
            for(x in 0..127) {
                if (!is1(x, y, hashes)) {
                    continue
                }
                val neighbours = MutableList<Int>(0, { it })
                if ((y > 0) && is1(x, y - 1, hashes)) neighbours.add(to_code(x, y - 1))
                if ((y < 127) && is1(x, y + 1, hashes)) neighbours.add(to_code(x, y + 1))
                if ((x > 0) && is1(x - 1, y, hashes)) neighbours.add(to_code(x - 1, y))
                if ((x < 127) && is1(x + 1, y, hashes)) neighbours.add(to_code(x + 1, y))
                val neighs = neighbours.joinToString(", ")
                out.println("${to_code(x, y)} <-> $neighs")
            }
        }
    }
}



