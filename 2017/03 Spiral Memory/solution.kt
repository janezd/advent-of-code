import kotlin.coroutines.experimental.buildSequence

fun part1() {
    fun square(n: Int) = (Math.floor(Math.sqrt(3.0 + 4 * (n - 1)) / 4 - 0.5) + 1).toInt()
    fun first_in(s: Int) = 1 + 1 + 4 * (s - 1) * s
    fun pos_in(n: Int) : Int {
        val s = square(n)
        return Math.abs(s - (n - first_in(s) + 1) % (2 * s))
    } 

    val n = 368078
    println("n = $n, square=${square(n)}, pos=${pos_in(n)}, dist=${square(n) + pos_in(n)}")
}

typealias Coords = Pair<Int, Int>

fun part2() {
    val fields = buildSequence {
        var s = 0;
        while(true) {
            if (s == 0) {
                yield(Coords(0, 0))
            }
            else {
                for(i in -s+1..s) { yield(Coords(s, i)); }
                for(i in s-1 downTo -s) { yield(Coords(i, s)); }
                for(i in s-1 downTo -s) { yield(Coords(-s, i)); }
                for(i in -s+1..s) { yield(Coords(i, -s)); }
            }
            s++;
        }
    }

    var i = 0;
    for ((x, y) in fields) {
        i++;
        if (i == 368078) {
            println("$x, $y -> ${Math.abs(x + y)}")
            break
        }
    }

    var values = HashMap<Coords, Int>();
    values[Coords(0, 0)] = 1
    for ((x, y) in fields) {
        var nv = 0
        for(dx in -1..1) {
            for(dy in -1..1) {
                nv += values[Coords(x + dx, y + dy)] ?: 0;
            }
        }
        values[Coords(x, y)] = nv;
        if (nv > 368078) {
            println("$x, $y -> $nv");
            break;
        }
    }

}

fun main(args: Array<String>) {
    part1()
    part2()
}