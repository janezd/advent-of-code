def path(s):
    x = y = 0
    yield x, y
    for e in s:
        if e == "^":
            y -= 1
        elif e == "v":
            y += 1
        elif e == "<":
            x -= 1
        elif e == ">":
            x += 1
        yield x, y

inst = open("input.txt").read().strip()
print("Prvi del:", len(set(path(inst))))
print("Drugi del:", len(set(path(inst[::2])) | set(path(inst[1::2]))))

from functools import reduce
inst = open("input.txt").read().strip()
print(len(set(reduce(lambda s, e: s + [s[-1] + {'<': -1, '>': 1, '^': 1j, 'v': -1j}[e]], inst, [0]))))
print(len(set(reduce(lambda s, e: s + [s[-1] + {'<': -1, '>': 1, '^': 1j, 'v': -1j}[e]], inst[::2], [0])) | set(reduce(lambda s, e: s + [s[-1] + {'<': -1, '>': 1, '^': 1j, 'v': -1j}[e]], inst[1::2], [0]))))
