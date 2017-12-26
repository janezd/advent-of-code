import java.io.File

enum class OpCode { snd, set, add, mul, mod, rcv, jgz }

sealed class Value;
class Register(val n: Int) : Value()
class Constant(val n: Long) : Value()

data class Instruction(val instr: OpCode, val reg: Value, val value: Value?)

fun get_value(operand: Value?, registers: Array<Long>) : Long {
    return when (operand) {
        is Constant -> operand.n
        is Register -> registers[operand.n]
        else -> -1
    }
}

fun execute(ip: Int,
            instructions: List<Instruction>,
            registers: Array<Long>,
            my_queue: MutableList<Long>, other_queue: MutableList<Long>): Pair<Int, Boolean> {
    val inst = instructions[ip]
    val value = get_value(inst.value, registers)
    val reg = if (inst.reg is Register) inst.reg.n else -1
    when (inst.instr) {
        OpCode.snd -> other_queue.add(get_value(inst.reg, registers))
        OpCode.set -> registers[reg] = value
        OpCode.add -> registers[reg] += value
        OpCode.mul -> registers[reg] *= value
        OpCode.mod -> registers[reg] %= value
        OpCode.rcv -> if (my_queue.size == 0) { return Pair(ip, false) } else { registers[reg] = my_queue.removeAt(0) }
        OpCode.jgz -> if (get_value(inst.reg, registers) > 0L) { return Pair(ip + value.toInt(), true) }
    }
    return Pair(ip + 1, true)
}

fun get_op(s: String) : Value {
    val v = s.toLongOrNull()
    return if (v == null) Register(s[0] - 'a') else Constant(v)
}

fun main(args: Array<String>) {
    val instructions = File("input.txt")
    .readLines()
    .map {
        val parts = it.split(' ')
        Instruction(OpCode.valueOf(parts[0]), get_op(parts[1]),
                    if (parts.size == 3) get_op(parts[2]) else null)
    }

    val registers1 = Array(26) { 0L }
    val registers2 = Array(26) { 0L }
    val queue1 = mutableListOf<Long>()
    val queue2 = mutableListOf<Long>()
    var ip1 = 0
    var ip2 = 0

    registers1['p' - 'a'] = 1
    registers2['p' - 'a'] = 0
    var ok1 = true
    var ok2 = true
    var send1 = 0
    var steps = 0
    while(ok1 || ok2) {
        val prevsq2 = queue2.size
        val (nip1, nok1) = execute(ip1, instructions, registers1, queue1, queue2)
        ip1 = nip1
        ok1 = nok1
        if (queue2.size != prevsq2) { send1++ }
        val (nip2, nok2) = execute(ip2, instructions, registers2, queue2, queue1)
        ip2 = nip2
        ok2 = nok2
    }
    println(send1)
}

// 8128 too high