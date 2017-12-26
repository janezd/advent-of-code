import java.io.File
import kotlin.text.Regex

fun main(args: Array<String>) {
    val registers = HashMap<String, Int>()
    var max_seen = 0

    File("input.txt")
    .readLines()
    .forEach {
        val terms = it.split(' ')
        val (reg, op, by, foo, cond_reg) = terms
        val cond = terms[5]
        val cond_value = registers[cond_reg] ?: 0
        val thresh = terms[6].toInt()
        if (when (cond) {
            ">" -> cond_value > thresh
            "<" -> cond_value < thresh
            ">=" -> cond_value >= thresh
            "<=" -> cond_value <= thresh
            "==" -> cond_value == thresh
            "!=" -> cond_value != thresh
            else -> false
        }) {
            var diff = if (op == "inc") by.toInt() else -by.toInt()
            val new_val = (registers[reg] ?: 0) + diff
            registers[reg] = new_val
            if (new_val > max_seen) {
                max_seen = new_val
            }
        }
    }
    println(registers.values.max())
    println(max_seen)
}