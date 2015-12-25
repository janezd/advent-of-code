import numpy as np

a = np.array([list(map("#".__eq__, line.strip())) for line in open("input.txt")], dtype=np.int8)
a[0, 0] = a[-1, -1] = a[0, -1] = a[-1, 0] = 1
for _ in range(100):
    n = np.zeros(a.shape)
    a = a.astype(np.int8)
    print(a)
    print()
    n[:-1, :-1] += a[1:, 1:]
    n[:-1, :] += a[1:, :]
    n[:, :-1] += a[:, 1:]
    n[1:, :] += a[:-1, :]
    n[:, 1:] += a[:, :-1]
    n[:-1, 1:] += a[1:, :-1]
    n[1:, :-1] += a[:-1, 1:]
    n[1:, 1:] += a[:-1, :-1]
    a = np.logical_or(np.logical_and(a, 2 == n), n == 3)
    a[0, 0] = a[-1, -1] = a[0, -1] = a[-1, 0] = True
print(np.sum(a))
