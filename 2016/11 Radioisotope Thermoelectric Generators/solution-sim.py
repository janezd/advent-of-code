# I could use sets, but I'm preparing for a solution in C ;)
import heapq

if True:
    N = 7
    end = 16383
    S, P, T, R, C, E, D, s, p, t, r, c, e, d = elements = [2 ** i for i in range(2 * N)]
    elements0 = [0, ] + elements
    initial = [S + s + P + p + E + e + D + d, T + R + r + C + c, t, 0]

    def is_invalid(state):
        return (state & 0x7f) and (state >> N) & ~(state & 0x7f)
else:
    N = 5
    end = 1023
    S, P, T, R, C, s, p, t, r, c = elements = [2 ** i for i in range(2 * N)]
    elements0 = [0, ] + elements
    initial = [S + s + P + p, T + R + r + C + c, t, 0]

    def is_invalid(state):
        return (state & 0x1f) and (state >> N) & ~(state & 0x1f)

def min_moves(state):
    moves = 0
    state = state[:]
    for floor in range(3):
        in_floor = state[floor]
        bits = 0
        while in_floor:
            bits += in_floor % 2
            in_floor >>= 1
        if bits > 2:
            moves += 2 * (bits - 2)
        if bits:
            moves += 1
        state[floor + 1] |= state[floor]
    return moves

queue = [(min_moves(initial), 0, 0, initial)]
checked = set()


def compute_path():
    while queue:
        _, floor, steps, state = heapq.heappop(queue)
        this_floor = state[floor]
        for direction in (1, -1):
            next_floor = floor + direction
            if not 0 <= next_floor <= 3:
                continue
            if direction == -1 and not any(state[:floor]):
                continue
            for i, el1 in ((i, 1 << i) for i in range(2 * N)):
                if not el1 & this_floor:
                    continue
                brought2 = False
                for el2 in [1 << j for j in range(i)] + [0]:
                    if not el2 and brought2:
                        continue
                    if el2 and not el2 & this_floor:
                        continue
                    if el1 and el2 and direction == -1:
                        continue
                    this = state[floor] & ~(el1 | el2)
                    next = state[next_floor] | el1 | el2
                    if is_invalid(this) or is_invalid(next):
                        continue
                    if next_floor == 3 and next == end:
                        return steps + 1
                    new_state = state[:]
                    new_state[floor] = this
                    new_state[next_floor] = next
                    encoded = []
                    for gen, el in zip(elements[:N], elements[N:]):
                        for fle, stf in enumerate(new_state):
                            if stf & el:
                                break
                        for flg, stf in enumerate(new_state):
                            if stf & gen:
                                break
                        encoded.append(flg << 4 | fle)
                    encoded = tuple(sorted(encoded))
                    if (next_floor, encoded) in checked:
                        continue
                    checked.add((next_floor, encoded))
                    heapq.heappush(queue, (min_moves(new_state), next_floor, steps + 1, new_state))
                    brought2 = True

print(compute_path())
print(len(checked))
