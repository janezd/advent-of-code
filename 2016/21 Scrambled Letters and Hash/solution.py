import re

s = list("abcdefgh")

def scramble(s):
    s = list(s)
    for line in open("input.txt"):
        terms = line.split()
        op = terms[0]
        x, y, *_ = [int(x) for x in re.findall("\d+", line)] + [0, 0]
        if op == "swap":
            if terms[1] == "letter":
                x, y = s.index(terms[2]), s.index(terms[5])
            s[x], s[y] = s[y], s[x]
        if op == "rotate":
            if terms[1] == "left":
                s = s[x:] + s[:x]
            else:
                if terms[1] == "based":
                    x = s.index(terms[6]) + 1
                    if x > 4:
                        x += 1
                    x %= len(s)
                s = s[-x:] + s[:-x]
        if op == "reverse":
            s = s[:x] + s[x:y+1][::-1] + s[y+1:]
        if op == "move":
            s.insert(y, s.pop(x))
        print("".join(s))
    return "".join(s)

print(scramble(s))
exit()
from itertools import permutations
for x in permutations("abcdefgh"):
    if scramble(x) == "fbgdceah":
        print(x)
        break
