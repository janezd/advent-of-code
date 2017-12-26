val n = 12656374

data class State(val state: Char, val value: Byte);
data class Rule(val newValue: Byte, val move: Int, val newState: Char);

val rules = hashMapOf(
    State('A', 0) to Rule(1, 1, 'B'),
    State('A', 1) to Rule(0, -1, 'C'),
    State('B', 0) to Rule(1, -1, 'A'),
    State('B', 1) to Rule(1, -1, 'D'),
    State('C', 0) to Rule(1, 1, 'D'),
    State('C', 1) to Rule(0, 1, 'C'),
    State('D', 0) to Rule(0, -1, 'B'),
    State('D', 1) to Rule(0, 1, 'E'),
    State('E', 0) to Rule(1, 1, 'C'),
    State('E', 1) to Rule(1, -1, 'F'),
    State('F', 0) to Rule(1, -1, 'E'),
    State('F', 1) to Rule(1, 1, 'X')
    )

fun main(args: Array<String>) {
    val tape = Array<Byte>(2 * n, { 0 })
    var pos = n
    var state = 'A'
    for (i in 1..n) {
        val rule = rules[State(state, tape[pos])]!!
        tape[pos] = rule.newValue
        pos += rule.move
        state = rule.newState
    }
    println(tape.sum())
}
