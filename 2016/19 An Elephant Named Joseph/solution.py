N = 3014387

s = list(range(0, N))
while len(s) > 1:
    s = s[::2][len(s) % 2:]
print(s)

print(int("{:b}".format(N)[1:] + "0", 2))
