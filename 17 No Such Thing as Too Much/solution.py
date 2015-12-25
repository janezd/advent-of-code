def choose(n, available):
    c = not n
    for i, next in enumerate(available):
        if next <= n:
            c += choose(n - next, available[i + 1:])
    return c

def choose2(n, available):
    if not n:
        return [[]]
    ways = []
    for i, next in enumerate(available):
        if next <= n:
            subways = choose2(n - next, available[i + 1:])
            ways += [[next] + x for x in subways]
    return ways

containers = list(map(int, "50 44 11 49 42 46 18 32 26 40 21 7 18 43 10 47 36 24 22 40".split()))
n = 150
print(choose(n, containers))
ways = choose2(n, containers)
mins = min((len(way) for way in ways))
print(mins)
print(len([m for m in ways if len(m) == mins]))
