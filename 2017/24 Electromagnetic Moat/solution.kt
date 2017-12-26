import java.io.File

fun strongest(start: Int, available: List<List<Int>>) : Int {
    return (available
        .filter { it.contains(start) }
        .map { it.sum() + strongest(it.sum() - start, available.minus<List<Int>>(it)) }
        .max() ?: 0)
}

fun longstrong(start: Int, available: List<List<Int>>) : Double {
    return (available
        .filter { it.contains(start) }
        .map { 1 + it.sum() / 10000.0 + longstrong(it.sum() - start, available.minus<List<Int>>(it)) }
        .max() ?: 0.0)
}

fun main(args: Array<String>) {
    val components = File("input.txt")
    .readLines()
    .map { it.split('/').map { it.toInt() } }

    println(strongest(0, components))
    println(longstrong(0, components))
}