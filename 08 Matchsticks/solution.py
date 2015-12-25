print(sum(len(s.strip()) - len(eval(s.strip())) for s in open("input.txt")))
print(sum(s.count("\\") + s.count('"') + 2 for s in open("input.txt")))
