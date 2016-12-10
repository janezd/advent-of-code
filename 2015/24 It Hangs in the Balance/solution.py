from functools import reduce
from operator import mul

number_set = set(map(int, open("input.txt").read().split()))
numbers = sorted(number_set, reverse=True)
tot_pack = len(numbers)

def to_sum(total, taken, remaining):
    if total == 0:
        yield taken
    for i, e in enumerate(remaining):
        if e <= total:
            yield from to_sum(total - e, taken + [e], remaining[i + 1:])
        yield from to_sum(total, taken, remaining[i + 1:])

total3 = sum(numbers) / 3
a0 = numbers[0]
least_first = len(numbers)

for a in to_sum(total3 - a0, [a0], numbers[1:]):
    remaining = sorted(number_set - set(a), reverse=True)
    b0 = remaining[0]
    for b in to_sum(total3 - b0, [b0], remaining[1:]):
        first = min(len(a), len(b), tot_pack - len(a) - len(b))
        if first <= least_first:
            if first < least_first:
                least_first = first
                least_qe = reduce(mul, numbers)
            c = set(remaining) - set(b)
            for ss in (a, b, c):
                if len(ss) == first:
                    qe = reduce(mul, ss)
                    if qe < least_qe:
                        least_qe = qe
                        print(least_first, least_qe)
