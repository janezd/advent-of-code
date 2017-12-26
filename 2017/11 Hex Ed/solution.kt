import java.io.File
import kotlin.math.abs

fun main(args: Array<String>) {
    var x = 0.0
    var y = 0.0
    var furthest = 0.0
    var dist = 0.0
    File("input.txt")
    .readText()
    .split(',')
    .forEach {
        y += (if (it.length == 2) 0.5 else 1.0) * (if (it[0] == 'n') 1 else -1)
        if (it.length == 2) { x += if (it[1] == 'e') 1 else -1 }
        dist = abs(x) + abs(x / 2 - y)
        if (dist > furthest) {
            furthest = dist
        }
    }
    println("Final distance: $dist")
    println("Furthest: $furthest")
}