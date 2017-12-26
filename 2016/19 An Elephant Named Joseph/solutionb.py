from math import log

N = 3014387

for N in range(1, 1000):
    s = list(range(1, N + 1))
    i = 0
    while len(s) > 1:
        r = (i + len(s) // 2) % len(s)
        del s[r]
        if i < r:
            i += 1
        elif i >= len(s):
            i = 0
    print(N, s)
