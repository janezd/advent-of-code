row = ".^^.^.^^^^"
row = "^^.^..^.....^..^..^^...^^.^....^^^.^.^^....^.^^^...^^^^.^^^^.^..^^^^.^^.^.^.^.^.^^...^^..^^^..^.^^^^"
safe = 0
for i in range(400000):
    #print(row)
    safe += row.count(".")
    row = "".join(".^"[l != r] for l, r in zip("." + row, row[1:] + "."))
print(safe)
