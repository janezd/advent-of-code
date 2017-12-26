import java.io.File

fun main(args: Array<String>) {
    val tubes = File("input.txt").readLines()
    var x = tubes[0].indexOf('|')
    var y = 0
    var dir = 'v'
    var letters = ""
    var count = 0
    while (tubes[y][x] != ' ') {
        count++
        when (dir) {
            'v' -> y += 1
            '^' -> y -= 1
            '<' -> x -= 1
            '>' -> x += 1
        }
        when (tubes[y][x]) {
            in 'A'..'Z' -> letters += tubes[y][x]
            '+' -> when (dir) {
                       'v', '^' -> if (x > 0 && tubes[y][x - 1] != ' ') dir = '<' else dir = '>'
                       '<', '>' -> if (y > 0 && tubes[y - 1][x] != ' ') dir = '^' else dir = 'v'
                 }
        }
    } 
    println(letters)
    println(count)
}