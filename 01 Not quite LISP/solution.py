def floor(s):
    return s.count("(") - s.count(")")

def first_basement(s):
    f = 0
    for i, e in enumerate(s):
        if e == "(":
            f += 1
        else:
            f -= 1
        if f < 0:
            return i + 1

seq = open("input.txt").read().strip()
print(floor(seq))
print(first_basement(seq))
