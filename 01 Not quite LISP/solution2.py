s = open("input.txt").read().strip()
print(len(s) - 2 * s.count(")"))
print(min(i for i in range(len(s)) if s[:i].count("(") < i / 2))
