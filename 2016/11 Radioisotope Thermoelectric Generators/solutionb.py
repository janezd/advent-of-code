# I could use sets, but I'm preparing for a solution in C ;)
from itertools import count

N = 14
N2 = 7
end = 16383
S, P, T, R, C, E, D, s, p, t, r, c, e, d = elements = [2 ** i for i in range(N)]
elements0 = [0, ] + elements
initial = [S + s + P + p + E + e + D + d, T + R + r + C + c, t, 0]
def is_invalid(state):
    return (state & 0x7f) and (state >> 7) & ~(state & 0x7f)


"""N = 10
end = 1023
S, P, T, R, C, s, p, t, r, c = elements = [2 ** i for i in range(N)]
elements0 = [0, ] + elements
initial = [S + s + P + p, T + R + r + C + c, t, 0]
def is_invalid(state):
    return (state & 0x1f) and (state >> 5) & ~(state & 0x1f)
"""

def compute_steps(queue):
    next_queue = []
    for floor, state in queue:
        this_floor = state[floor]
        for direction in (-1, 1):
            next_floor = floor + direction
            if not 0 <= next_floor <= 3 or direction == -1 and not any(state[:floor]):
                continue
            has_same = False
            for i, el1 in ((i, 1 << i) for i in range(N)):
                if not el1 & this_floor:
                    continue
                for el2 in [0] + [1 << j for j in range(i)]:
                    if el2 and not el2 & this_floor or has_same and el1 == el2 << N2:
                        continue
                    if el1 == el2 << N2:
                        has_same = True
                    this = state[floor] & ~(el1 | el2)
                    next = state[next_floor] | el1 | el2
                    if is_invalid(this) or is_invalid(next):
                        continue
                    if next_floor == 3 and next == end:
                        return None
                    new_state = state[:]
                    new_state[floor] = this
                    new_state[next_floor] = next
                    if (next_floor, tuple(new_state)) in checked:
                        continue
                    checked.add((next_floor, tuple(new_state)))
                    next_queue.append((next_floor, new_state))
    return next_queue


queue = [(0, initial)]
checked = set()

for step in count(1):
    print(step)
    queue = compute_steps(queue)
    if queue is None:
        print("Solution: ", step)
        break

print(len(checked))


# 60 is too low part 2
