intervals = sorted(tuple(map(int, v.split("-"))) for v in open("input.txt"))

prev = 0
first = None
allowed = 0
for fr, to in intervals:
    if fr > prev:
        if first is None:
            first = prev
        allowed += fr - prev
    prev = max(prev, to + 1)
print(first)
print(allowed)

print(max([(b - a) for b, a in intervals]))
