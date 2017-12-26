import java.io.File

fun main(args: Array<String>) {
    val lines = File("input.txt")
        .readLines()
        .map { it.split(' ') }

    println(lines.count { it.distinct().size == it.size })
    println(lines.count { it.map { it.toList().sorted() }
                            .distinct()
                            .size == it.size } )
}
