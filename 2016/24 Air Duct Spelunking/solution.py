from itertools import permutations

maze = open("input.txt").readlines()

def shortest_path(x0, y0, x1, y1):
    check_next = [(x0, y0)]
    seen = {(x0, y0)}
    steps = 0
    while check_next:
        to_check = check_next
        check_next = []
        steps += 1
        while to_check:
            x, y = to_check.pop()
            for nx, ny in ((x + 1, y), (x - 1, y), (x, y - 1), (x, y + 1)):
                if (nx, ny) == (x1, y1):
                    return steps
                if (nx, ny) not in seen and maze[ny][nx] != "#":
                    seen.add((nx, ny))
                    check_next.append((nx, ny))

to_visit = sorted((c, s.find(c), y) for y, s in enumerate(maze) for c in "0123456789" if c in s)

lengths = {}
for i, (c0, x0, y0) in enumerate(to_visit):
    for c1, x1, y1 in to_visit[:i]:
        lengths[(c0, c1)] = lengths[(c1, c0)] = shortest_path(x0, y0, x1, y1)

for i in range(8):
    for j in range(i):
        print("{:5}".format(lengths[(str(i), str(j))]), end="")
    print()

points = tuple({p[0] for p in lengths} - {"0"})
print(min(sum(lengths[(c0, c1)] for c0, c1 in zip(("0",) + path, path))
      for path in permutations(points)))

points = tuple({p[0] for p in lengths} - {"0"})
print(min(sum(lengths[(c0, c1)] for c0, c1 in zip(("0",) + path, path + ("0",)))
      for path in permutations(points)))
