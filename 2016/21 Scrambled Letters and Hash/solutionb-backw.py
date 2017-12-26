
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
                    print(x)
                s = s[-x:] + s[:-x]
        if op == "reverse":
            s = s[:x] + s[x:y+1][::-1] + s[y+1:]
        if op == "move":
            s.insert(y, s.pop(x))
    return "".join(s)

def unscramble(s):
    s = list(s)
    for line in reversed(list(open("input.txt"))):
        terms = line.split()
        op = terms[0]
        x, y, *_ = [int(x) for x in re.findall("\d+", line)] + [0, 0]
        if op == "swap":
            if terms[1] == "letter":
                x, y = s.index(terms[2]), s.index(terms[5])
            s[x], s[y] = s[y], s[x]
        if op == "rotate":
            if terms[1] == "left":
                s = s[-x:] + s[:-x]
            else:
                if terms[1] == "based":
                    x = s.index(terms[6])
                    print("n", x)
                    x = [1, 1, 6, 2, 7, 3, 0, 4][x]
                    print(x)
                s = s[x:] + s[:x]
        if op == "reverse":
            s = s[:x] + s[x:y+1][::-1] + s[y+1:]
        if op == "move":
            s.insert(x, s.pop(y))
    return "".join(s)

s = scramble(s)
print(s)
print(unscramble(list(s)))
