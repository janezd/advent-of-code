import java.io.File

fun main(args: Array<String>) {
    var open = 0
    var total = 0
    var garbage = 0
    var in_garbage = false
    var cancel_next = false

    File("input.txt")
    .readText()
    .forEach {
        if (cancel_next) { cancel_next = false }
        else if (it == '!') { cancel_next = true }
        else if (in_garbage) {
            if (it == '>') { in_garbage = false}
            else { garbage++ }
        }
        else {
            when (it) {
                '<' -> in_garbage = true
                '}' -> open--
                '{' -> { open++; total += open; }
            }
        }
    }
    println(total)
    println(garbage)
}