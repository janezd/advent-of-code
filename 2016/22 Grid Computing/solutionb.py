import numpy as np
import re

from hashlib import sha1
class Hashable:
    def __init__(self, a):
        self.a = a
        self._hash = int(sha1(np.ascontiguousarray(self.a)).hexdigest(), 16)
        print(self._hash)

    def __hash__(self):
        return self._hash

    def __eq__(self, other):
        return np.array_equal(self.a, other)

data = []
x_prev = -1
re_node = re.compile("/dev/grid/node-x(\d+)-y(\d+) +(\d+)T +(\d+)T +(\d+)T")
for line in open("input.txt"):
    mo = re_node.search(line)
    if mo:
        x, y, *c = [int(x) for x in mo.groups()]
        if x != x_prev:
            data.append([])
            x_prev = x
        data[-1].append(c)

for x in data:
    print([t for t in x][:7])

sizex, sizey = len(data), len(data[0])
check_next = [(np.array(data, dtype=np.uint16), len(data) - 1, 0)]
steps = 0
seen = set()
while check_next:
    steps += 1
    print(steps, len(check_next))
    to_check = check_next
    check_next = []
    while to_check:
        data, xpos, ypos = to_check.pop()
        for x in range(sizex):
            for y in range(sizey):
                for nx, ny in (x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1):
                    if 0 <= nx < sizex and 0 <= ny < sizey and \
                            data[x, y, 1] <= data[nx, ny, 2]:
                        print("{}, {} -> {}, {}".format(x, y, nx, ny))
                        exit()
                        new = data.copy()
                        new[nx, ny, 2] -= new[x, y, 1]
                        new[nx, ny, 1] += new[x, y, 1]
                        new[x, y, 1] = 0
                        new[x, y, 2] = new[x, y, 0]
                        nposx = nx if x == xpos else xpos
                        nposy = ny if y == ypos else ypos
                        if nposx == nposy == 0:
                            print(steps)
                            exit()
                        mat = (Hashable(new), nposx, nposy)
                        if mat not in seen:
                            check_next.append((new, nposx, nposy))
                            seen.add(mat)
