import re
parre = re.compile(r"\((\d+)x(\d+)\)")

zipped = open("input.txt").read().strip()
def compute_length(s):
    length = 0
    pos = 0
    while True:
        mo = parre.search(s, pos)
        if not mo:
            break
        chars, times = map(int, mo.groups())
        newpos = mo.end() + chars
        length += mo.start() - pos + chars * times
#        length += mo.start() - pos + compute_length(s[mo.end():mo.end() + chars]) * times
        pos = newpos
    length += len(s) - pos
    return length

print(compute_length(zipped))
print(compute_length("(3x3)XYZ"))

