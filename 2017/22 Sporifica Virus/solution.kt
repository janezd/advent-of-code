import java.io.File

fun main(args: Array<String>) {
    val lines = File("input.txt").readLines()
    val infected = HashSet(
        lines
        .mapIndexed { y, line -> line.mapIndexed { x, it -> Pair(Pair(x, y), it == '#') } }
        .flatten()
        .filter { it.second }
        .map { it.first }
    )
    var dir = 0  // ^>v<
    var x = lines.size / 2
    var y = lines.size / 2
    var inf_count = 0
    (1..10000).forEach {
        val pos = Pair(x, y)
        if (infected.contains(pos)) { dir++; infected.remove(pos) }
        else { dir += 3; infected.add(pos); inf_count++ }
        when (dir % 4) {
            0 -> y--
            1 -> x++
            2 -> y++
            3 -> x--
        }
    }
    print(inf_count)
}

// 5000 too low