import java.io.File

enum class OpCode { snd, set, add, mul, mod, rcv, jgz }

sealed class Value;
class Register(val n: Int) : Value()
class Constant(val n: Long) : Value()

data class Instruction(val instr: OpCode, val reg: Register, val value: Value?)

fun main(args: Array<String>) {
    val instructions = File("input.txt")
    .readLines()
    .map {
        val parts = it.split(' ')
        var value: Value? = null
        if (parts.size > 2) {
            val v = parts[2].toLongOrNull()
            value = if (v == null) Register(parts[2][0] - 'a') else Constant(v)
        }
        Instruction(OpCode.valueOf(parts[0]), Register(parts[1][0] - 'a'), value)
    }

    val registers = Array(26) { 0L }
    var ip = 0
    var last_snd: Long? = null
    var recovered: Long? = null
    execute@ while (ip >= 0 && ip < instructions.size) {
        val inst = instructions[ip]
        val value = when (inst.value) {
            is Constant -> inst.value.n
            is Register -> registers[inst.value.n]
            else -> -1 }
        val reg = inst.reg.n
        when (inst.instr) {
            OpCode.snd -> last_snd = registers[reg]
            OpCode.set -> registers[reg] = value
            OpCode.add -> registers[reg] += value
            OpCode.mul -> registers[reg] *= value
            OpCode.mod -> registers[reg] %= value
            OpCode.rcv -> if (registers[reg] != 0L) { recovered = last_snd; break@execute }
            OpCode.jgz -> if (registers[reg] > 0L) { ip += value.toInt() - 1 }
        }
        ip += 1
    }
    println(recovered)
}

// -91 is wrong