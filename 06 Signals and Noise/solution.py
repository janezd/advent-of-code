import numpy as np
a = np.loadtxt("input.txt", dtype='S').view("b").reshape((-1, 8))
for f in (np.argmax, np.argmin):
    print("".join([chr(97 + f(np.bincount(a[:, i])[97:])) for i in range(8)]))
