code = 0
n = 5

for line in open("input.txt"):
    if not line.strip():
        continue
    for char in line:
        if char == "U":
            if n >= 4:
                n -= 3
        if char == "D":
            if n <= 6:
                n += 3
        if char == "L":
            if n % 3 != 1:
                n -= 1
        if char == "R":
            if n % 3 != 0:
                n += 1
    code = 10 * code + n
print(code)
