from sys import exit
from itertools import count

N = 1364

checked = set()
queue = [(1, 1)]
checked = {(1, 1)}

for step in count(1):
    next_queue = []
    for x, y in queue:
        for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
            if (nx, ny) == (31, 39):
                print(step)
                exit()
            if (nx, ny) not in checked and nx >= 0 and ny >= 0 and sum(map(int, bin(nx * nx + 3 * nx + 2 * nx * ny + ny + ny * ny + N)[2:])) % 2 == 0:
                next_queue.append((nx, ny))
                checked.add((nx, ny))
    queue = next_queue
    if not queue:
        print("No.")
        break

