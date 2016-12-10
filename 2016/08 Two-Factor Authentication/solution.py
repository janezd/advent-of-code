import re
import numpy as np

display = np.zeros((6, 50), dtype=bool)
for line in open("input.txt"):
    d1, d2 = map(int, re.findall(r"\d+", line))
    if line.startswith("rect"):
        display[:d2, :d1] = True
    elif line.startswith("rotate row"):
        display[d1] = np.roll(display[d1], d2)
    else:
        display[:, d1] = np.roll(display[:, d1], d2)
    print(line)
    print("\n".join("".join(" X"[x] for x in r) for r in display))
    print()
print(np.sum(display))
