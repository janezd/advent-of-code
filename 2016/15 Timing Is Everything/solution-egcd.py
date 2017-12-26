def egcd(a, b):
    #a, b = max(a, b), min(a, b)
    sp, tp = 1, 0
    s, t = 0, 1
    while b:
        k = a // b
        a, b = b, a % b
        sp, s = s, sp - k * s
        tp, t = t, tp - k * t
    return a, sp, tp

def chinese(conds):
    a1, n1 = 0, 1
    for a2, n2 in conds:
        print(a1, n1)
        _, m1, m2 = egcd(n1, n2)
        print(m1, m2)
        a1 = a1 * m2 * n2 + a2 * m1 * n1
        n1 *= n2
        a1 %= n1
    return a1

import re
r = re.compile(r"Disc #(\d+) has (\d+) positions; at time=0, it is at position (\d+).")

conds = []
for i, line in enumerate(open("input.txt")):
    delay, positions, initial = map(int, r.search(line).groups())
    conds.append(((positions - (delay + initial)) % positions, positions))
print(conds)
print(chinese(conds))
conds.append((11 - len(conds) - 1, 11))
print(chinese(conds))
