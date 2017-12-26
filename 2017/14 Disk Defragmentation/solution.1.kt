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
    File("connections.txt")
    .forEachLine {
        val line = it.split(" <-> ")
        connections[line[0].toInt()] = 
            if (line[1].length > 0) { line[1].split(", ").map { it.toInt() }.toSet() }
            else { setOf() }
    }

    // Part 2
    var uncovered = connections.keys.toMutableSet()
    println(uncovered.size)
    var n_groups = 0
    while(uncovered.size > 0) {
        uncovered.removeAll(make_group(uncovered.first()))
        n_groups++
    }
    println(n_groups)
}