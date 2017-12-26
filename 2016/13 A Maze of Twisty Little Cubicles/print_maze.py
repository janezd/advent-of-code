N = 1364

for y in range(50):
    for x in range(50):
        if (x, y) == (31, 39):
            print("O", end="")
        else:
            print(" X"[sum(map(int, bin(x * x + 3 * x + 2 * x * y + y + y * y + N)[2:])) % 2], end="")
    print()
