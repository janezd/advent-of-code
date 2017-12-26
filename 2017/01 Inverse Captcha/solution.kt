import java.io.File

fun main(args: Array<String>) {
    var s = File("input.txt").readText().trim()
    val slen : Int = s.length

    // Two versions each
    
    println(s.filterIndexed {i, c -> c == s[(i + 1) % slen] }
             .sumBy { it - '0' })
    println((s + s[0]).zipWithNext{ a, b -> if (a == b) a - '0' else 0}
                      .sum())

    println(2 * s.take(slen / 2)
                 .filterIndexed {i, c -> c == s[i + slen / 2] }
                 .sumBy { it - '0' })
    println(2 * s.take(slen / 2)
                 .zip(s.drop(slen / 2))
                 .sumBy { if (it.first == it.second) it.first - '0' else 0})
}
