data = [sorted(map(int, x.split("x"))) for x in open("input.txt")]
print(sum(3 * a * b + 2 * b * c + 2 * a * c for a, b, c in data))
print(sum(2 * (a + b) + a * b * c for a, b, c in data))
