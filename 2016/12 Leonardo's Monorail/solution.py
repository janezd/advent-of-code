regs = dict.fromkeys("abcd", 0)
#regs["c"] = 1
print(regs)
prog = [c.strip().split() + [None,] for c in open("input.txt")]
ip = 0

steps = 0
while 0 <= ip < len(prog):
    steps += 1
    instr, arg0, arg1, *_ = prog[ip]
    val0 = regs[arg0] if arg0 in "abcd" else int(arg0)
    if instr == "jnz":
        if val0:
            ip += int(arg1)
            continue
    elif instr == "cpy":
        regs[arg1] = val0
    elif instr == "inc":
        regs[arg0] += 1
    elif instr == "dec":
        regs[arg0] -= 1
    print(regs)
    ip += 1
print(regs)
print(steps)
