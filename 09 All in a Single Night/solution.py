from itertools import permutations

dist = {(x, y): int(d) for x, _1, y, _2, d in (v.split() for v in open("input.txt"))}
dist.update({(y, x): d for (x, y), d in dist.items()})
places = {x[0] for x in dist}
print(min(sum(dist[x, y] for x, y in zip(path, path[1:])) for path in permutations(places)))
print(max(sum(dist[x, y] for x, y in zip(path, path[1:])) for path in permutations(places)))
