import re
from itertools import count

r = re.compile(r"Disc #(\d+) has (\d+) positions; at time=0, it is at position (\d+).")

conds = []
for line in open("input.txt"):
    delay, positions, initial = map(int, r.search(line).groups())
    conds.append((delay + initial, positions))

for t in count():
    if not any((t + pos) % positions for pos, positions in conds):
        print(t)
        break

conds.append((len(conds) + 1, 11))
print(conds)
for t in count():
    if not any((t + pos) % positions for pos, positions in conds):
        print(t)
        break
