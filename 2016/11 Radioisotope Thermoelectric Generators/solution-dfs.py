# I could use sets, but I'm preparing for a solution in C ;)
from itertools import count, chain

N = 7
end = 16383
S, P, T, R, C, E, D, s, p, t, r, c, e, d = elements = [2 ** i for i in range(2 * N)]
elements0 = [0, ] + elements
initial = [S + s + P + p + E + e + D + d, T + R + r + C + c, t, 0]
#initial = [T + t + P + S + E + e + D + d, p + s, C + c + R + r, 0]
def is_invalid(state):
    return (state & 0x7f) and (state >> 7) & ~(state & 0x7f)


"""
N = 5
end = 1023
S, P, T, R, C, s, p, t, r, c = elements = [2 ** i for i in range(2 * N)]
elements0 = [0, ] + elements
initial = [S + s + P + p, T + R + r + C + c, t, 0]
initial = [T + t + P + S, p + s, C + c + R + r, 0]
def is_invalid(state):
    return (state & 0x1f) and (state >> 5) & ~(state & 0x1f)
"""

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

def encode(state):
    encoded = []
    for gen, el in zip(elements[:N], elements[N:]):
        for fle, stf in enumerate(state):
            if stf & el:
                break
        for flg, stf in enumerate(state):
            if stf & gen:
                break
        encoded.append(flg << 4 | fle)
    return tuple(sorted(encoded))


stack = [(0, initial, encode(initial))]

def compute_path(stack):
    if len(stack) > max_steps:
        return
    floor, state, _ = stack[-1]
    this_floor = state[floor]
    best = None
    try_next = []
    for direction in (1, -1):
        if direction == -1 and not any(state[:floor]):
            continue
        next_floor = floor + direction
        if not 0 <= next_floor <= 3:
            continue
        for i, el1 in ((i, 1 << i) for i in range(2 * N)):
            if not el1 & this_floor:
                continue
            for el2 in [1 << j for j in range(i)] + [0]:
                if el2 and not el2 & this_floor:
                    continue
                if el1 and el2 and direction == -1:
                    continue
                this = state[floor] & ~(el1 | el2)
                next = state[next_floor] | el1 | el2
                if is_invalid(this) or is_invalid(next):
                    continue
                if next_floor == 3 and next == end:
                    return stack
                new_state = state[:]
                new_state[floor] = this
                new_state[next_floor] = next
                encoded = encode(new_state)
                if any(x[-1] == encoded for x in chain(stack, try_next)):
                    continue
                try_next.append((next_floor, new_state, encoded))
        for next in sorted(try_next, key=lambda x: min_moves(x[1])):
            res = compute_path(stack + [next])
            if res and len(res) == max_steps:
                return res
    return best

for max_steps in count(min_moves(initial)):
    print(max_steps)
    res = compute_path(stack)
    if res:
        break
