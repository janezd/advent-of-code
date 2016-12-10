import numpy as np

def count(a):
    return np.sum(np.sum(a, axis=1) > 2 * np.max(a, axis=1))

a = np.loadtxt("input.txt")
print(count(a))
print(count(np.vstack([a[i::3].flatten() for i in range(3)]).T))
