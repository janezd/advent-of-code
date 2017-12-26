import java.io.File

val connections = HashMap<Int, Set<Int>>()

fun make_group(start: Int): MutableSet<Int> {
    val to_check = mutableSetOf<Int>()
    val in_group = mutableSetOf<Int>()
    to_check.add(start)
    while(to_check.size > 0) {
        val el = to_check.first()
        to_check.remove(el)
        in_group.add(el)
        connections[el]!!.forEach { if (!in_group.contains(it)) { to_check.add(it) } }
    }
    return in_group
}

fun main(args: Array<String>) {
    File("input.txt")
    .forEachLine {
        val line = it.split(" <-> ")
        connections[line[0].toInt()] = line[1].split(", ").map { it.toInt() }.toSet()
    }

    // Part 1
    val group0 = make_group(0)
    println(group0.size)

    // Part 2
    var uncovered = connections.keys.toMutableSet()
    uncovered.removeAll(group0)
    var n_groups = 1
    while(uncovered.size > 0) {
        uncovered.removeAll(make_group(uncovered.first()))
        n_groups++
    }
    println(n_groups)
}