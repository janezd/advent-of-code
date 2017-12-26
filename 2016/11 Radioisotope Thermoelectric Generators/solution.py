# I could use sets, but I'm preparing for a solution in C ;)
S, P, T, R, C, s, p, t, r, c = elements = [2 ** i for i in range(10)]
elements0 = [0, ] + elements
initial = [S + s + P + p + E + e + D + d, T + R + r + C + c, t, 0]

queue = [(0, 0, initial)]
checked = set()

def is_invalid(state):
    return (state & 0x1f) and (state >> 5) & ~(state & 0x1f)

for floor, steps, state in queue:
    this_floor = state[floor]
    for direction in (-1, 1):
        next_floor = floor + direction
        if not 0 <= next_floor <= 3:
            continue
        for i, el1 in ((i, 1 << i) for i in range(10)):
            if not el1 & this_floor:
                continue
            for el2 in [0] + [1 << j for j in range(i)]:
                if el2 and not el2 & this_floor:
                    continue
                this = state[floor] & ~(el1 | el2)
                next = state[next_floor] | el1 | el2
                if is_invalid(this) or is_invalid(next):
                    continue
                if next_floor == 3 and next == 1023:
                    print(steps + 1)
                    break
                new_state = state[:]
                new_state[floor] = this
                new_state[next_floor] = next
                if (next_floor, tuple(new_state)) in checked:
                    continue
                checked.add((next_floor, tuple(new_state)))
                queue.append((next_floor, steps + 1, new_state))

