code = ""
coords = 1 + 3j

dx = {"L": -1, "R": 1}
dy = {"U": -1, "D": 1}

square = ["       ",
          "   1   ",
          "  234  ",
          " 56789 ",
          "  ABC  ",
          "   D   ",
          "       "]

x, y = 1, 3
for line in open("input.txt"):
    line = line.strip()
    if not line:
        continue
    for char in line:
        nx, ny = x + dx.get(char, 0), y + dy.get(char, 0)
        if square[ny][nx] != " ":
            x, y = nx, ny
    code += square[y][x]
print(code)
