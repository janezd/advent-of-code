import java.io.File
import kotlin.system.measureTimeMillis

sealed class Instruction;

data class Spin(val n: Int) : Instruction()
data class Exchange(val i1: Int, val i2: Int) : Instruction()
data class Partner(val c1: Char, val c2: Char) : Instruction()

val size = 16
val fname = "input.txt"

fun run(instructions: List<Instruction>, init: Array<Char>? = null) : Array<Char> {
    var order = init?.copyOf() ?: Array(size) { (it + 97).toChar() }
    instructions    
    .forEach {
        when (it) {
            is Spin -> order = Array(size) {i -> order[(i + it.n) % size] }
            is Exchange -> { var t = order[it.i1]; order[it.i1] = order[it.i2]; order[it.i2] = t }
            is Partner -> { var i1 = order.indexOf(it.c1); var i2 = order.indexOf(it.c2);
                            var t = order[i1]; order[i1] = order[i2]; order[i2] = t }
        }
    }
    return order
}

fun main(args: Array<String>) {
    var instructions = File(fname)
        .readText()
        .split(',')
        .map (fun (it: String) : Instruction {
            val rest = it.drop(1)
            if (it[0] == 's') { return Spin(size - rest.toInt()) }
            else {
                val ft = rest.split('/')
                if (it[0] == 'p') { return Partner(ft[0][0], ft[1][0]) }
                else { return Exchange(ft[0].toInt(), ft[1].toInt()) }
            }
        })

    val init = Array(size) { (it + 97).toChar() }

    var order = run(instructions, init)
    println(order.joinToString(""))

    order = init.copyOf();
    var cycle = (1..1000000000).first {
        order = run(instructions, order)
        order.contentEquals(init)
    }
    println(cycle)

    println(order.joinToString(""))
    println(init.joinToString(""))

    (1..(1000000000 % cycle)).forEach {
        order = run(instructions, order)
        val sorder = order.joinToString("")
        println("$it  $sorder")
    }
    println(order.joinToString(""))
}

// incorrect: fkmcgdnjabpioelh
// incorrect: fcakgjlnohmpebid
// incorrect: igjlbdpmnafcokhe