from functools import reduce
from operator import mul

number_set = set(map(int, open("input.txt").read().split()))
numbers = sorted(number_set, reverse=True)
tot_pack = len(numbers)

def to_sum(a, b, total_a, total_b, i, remaining):
    if i < len(remaining):
        e = remaining[i]
        if e <= total_a:
            yield from to_sum(a + [e], b, total_a - e, total_b, i + 1, remaining)
        if e <= total_b:
            yield from to_sum(a, b + [e], total_a, total_b - e, i + 1, remaining)
    else:
        yield a, b

total = sum(numbers)
total4 = total // 4
least_first = len(numbers)

print(total4)
for a, not_a in to_sum([], [], total4, total - total4, 0, numbers):
    for b, not_b in to_sum([], [], total4, total // 2, 0, not_a):
        for c, d in to_sum([], [], total4, total4, 0, not_b):
            alls = (a, b, c, d)
            first = min(map(len, alls))
            if first <= least_first:
                if first < least_first:
                    least_first = first
                    least_qe = reduce(mul, numbers)
                for ss in alls:
                    if len(ss) == first:
                        qe = reduce(mul, ss)
                        if qe < least_qe:
                            least_qe = qe
                            print(least_first, least_qe)

