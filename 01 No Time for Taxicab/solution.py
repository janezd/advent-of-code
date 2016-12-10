dirs = [1j, 1, -1j, -1]
rots = {"R": 1, "L": -1}

dir = 0
coords = 0
directions = open("input1.txt").read().replace(" ", "").split(",")
for where in directions:
    dir = (dir + rots[where[0]]) % 4
    coords += dirs[dir] * int(where[1:])
    print(coords)
print(abs(coords.real) + abs(coords.imag))

visited = {0}
coords = 0
dir = 0
directions = open("input1.txt").read().replace(" ", "").split(",")
twc = False
for where in directions:
    dir = (dir + rots[where[0]]) % 4
    for i in range(int(where[1:])):
        coords += dirs[dir]
        #print(where, coords)
        if coords in visited and not twc:
            print(coords)
            twc = True
        visited.add(coords)
print(abs(coords.real) + abs(coords.imag))

# 191 --- too high
