from math import log

N = 3014387

print(int("{:b}".format(N)[1:] + "0", 2))

m = 1
while m < N:
    m *= 3
m //= 3
if N <= 2 * m:
    print(N - m)
else:
    print(2 * N - 3 * m)
