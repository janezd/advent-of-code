# Collatz :)

prog = [[y.strip(",") for y in x.strip().split()] for x in open("input.txt")]

reg = {"a": 1, "b": 0}
ip = 0
while 0 <= ip < len(prog):
    instr = prog[ip][0]
    print(reg, ip, prog[ip])
    arg = prog[ip][1]
    if instr == "jmp" or \
            instr == "jie" and reg[arg] % 2 == 0 or \
            instr == "jio" and reg[arg] == 1:
        ip += int(prog[ip][-1])
        continue
    elif instr == "hlf":
        reg[arg] //= 2
    elif instr == "tpl":
        reg[arg] *= 3
    elif instr == "inc":
        reg[arg] += 1
    ip += 1
print(reg)

