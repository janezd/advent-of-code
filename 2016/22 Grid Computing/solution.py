f = open("input.txt")
f.readline()
f.readline()
data = [[int(t[:-1]) for t in line.split()[1:4]] for line in f]

viable = 0
for i, (size1, used1, available1) in enumerate(data):
    for size2, used2, available2 in data[:i]:
        viable += (used1 and used1 <= available2) + (used2 and used2 <= available1)
print(viable)
