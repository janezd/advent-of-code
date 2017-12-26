import java.io.File
import kotlin.text.Regex

data class Disk(
    val weight: Int,
    val subdisks: List<String>
)

val tree = HashMap<String, Disk>()

fun balance(name: String) : Int {
    val d = tree[name]!!
    val subs = d.subdisks.map { balance(it) }
    val mi = subs.min() ?: 0
    val ma = subs.max() ?: 0
    if (mi == ma) {
        return d.weight + subs.size * mi
    }
    else if (mi < 0) {
        return mi
    }
    if (subs.count { it == mi } == 1) {
        val which = subs.indexOf(mi)
        return -(tree[d.subdisks[which]]!!.weight + (ma - mi))
    }
    else {
        val which = subs.indexOf(ma)
        return -(tree[d.subdisks[which]]!!.weight - (ma - mi))
    }
}

fun main(args: Array<String>) {
    Regex("(\\w+) \\((\\d+)\\)( -> (.*))?")
    .findAll(File("input.txt").readText())
    .forEach {
        tree[it.groupValues[1]] = Disk(
            it.groupValues[2].toInt(),
            it.groupValues[4]
              .split(',')
              .map { it.trim() }
              .filter { it.length > 0 }
        )
    }

    val root = (
        tree.keys
        - tree.values
          .map { it.subdisks.toSet() }
          .reduce { x, y -> x.union(y) }).first()

    println(root)
    println(-balance(root))
}