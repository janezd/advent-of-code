import java.io.File

enum class OpCode { set, add, mul, mod, jgz, jnz, sub }

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

fun execute(ip: Int, instructions: List<Instruction>, registers: Array<Long>): Int {
    val inst = instructions[ip]
    val value = get_value(inst.value, registers)
    val reg = if (inst.reg is Register) inst.reg.n else -1
    when (inst.instr) {
        OpCode.set -> registers[reg] = value
        OpCode.add -> registers[reg] += value
        OpCode.sub -> registers[reg] -= value
        OpCode.mul -> registers[reg] *= value
        OpCode.mod -> registers[reg] %= value
        OpCode.jgz -> if (get_value(inst.reg, registers) > 0L) { return ip + value.toInt() }
        OpCode.jnz -> if (get_value(inst.reg, registers) != 0L) { return ip + value.toInt() }
    }
    return ip + 1
}

fun get_op(s: String) : Value {
    val v = s.toLongOrNull()
    return if (v == null) Register(s[0] - 'a') else Constant(v)
}

fun main(args: Array<String>) {
    val instructions = File("input.1.txt")
    .readLines()
    .map {
        val parts = it.split(' ')
        Instruction(OpCode.valueOf(parts[0]), get_op(parts[1]), get_op(parts[2]))
    }

    val registers = Array(26) { 0L }
    var ip = 0
    var muls = 0
    while (ip >= 0 && ip < instructions.size) {
        if (instructions[ip].instr == OpCode.mul) { muls++ }
        ip = execute(ip, instructions, registers)
    }
    println(registers['h' - 'a'])
    println(muls)
}
