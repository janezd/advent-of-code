import java.io.File

fun main(args: Array<String>) {
    var blocks = File("input.txt")
        .readText()
        .split("\t")
        .map { it.toInt() }
    val n_blocks = blocks.size

    val seen = HashMap<List<Int>, Int>();

    var step = 0;
    while (!seen.containsKey(blocks)) {
        seen[blocks] = step++;
        var to_reallocate = blocks.max()!!
        var where = blocks.indexOf(to_reallocate)
        var temp_blocks = blocks.toMutableList()
        temp_blocks[where] = 0;
        while (to_reallocate > 0) {
            where = (where + 1) % n_blocks
            temp_blocks[where]++;
            to_reallocate--;
        }
        blocks = temp_blocks.toList()
    }

    println("Cycle at step $step; cycle size ${step - seen[blocks]!!}")
}