import java.io.File

fun main(args: Array<String>) {
    val lines = File("input.txt").readLines()
    val infected = lines
        .mapIndexed { y, line -> line.mapIndexed { x, it -> Pair(x, y) to (if (it == '#') 2 else 0) } }
        .flatten()
        .toMap()
        .toMutableMap()
    val changes = listOf(3, 0, 1, 2)
    var dir : Int = 0  // ^>v<
    var x = lines.size / 2
    var y = lines.size / 2
    var inf_count = 0
    (1..10000000).forEach {
        val pos = Pair(x, y)
        dir += changes[infected.getOrDefault(pos, 0)]
        infected[pos] = (infected.getOrDefault(pos, 0) + 1) % 4
        if (infected[pos] == 2) { inf_count++ }
        when (dir % 4) {
            0 -> y--
            1 -> x++
            2 -> y++
            3 -> x--
        }
    }
    print(inf_count)
}
