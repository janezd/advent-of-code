from math import ceil
from itertools import combinations

def sim(pl_hit, pl_damage, pl_armor, bo_hit, bo_damage, bo_armor):
    return ceil(pl_hit / max(1, bo_damage - pl_armor)) >= \
           ceil(bo_hit / max(1, pl_damage - bo_armor))

bo_hit, bo_damage, bo_armor = 100, 8, 2

weapons = (8, 4, 0), (10, 5, 0), (25, 6, 0), (40, 7, 0), (74, 8, 0)
armor = (0, 0, 0), (13, 0, 1), (31, 0, 2), (53, 0, 3), (75, 0, 4), (102, 0, 5)
rings = (25, 1, 0), (50, 2, 0), (100, 3, 0), (20, 0, 1), (40, 0, 2), (80, 0, 3)


mincost = 100000000
maxcost = 0
for w_cost, w_damage, w_armor in weapons:
    for a_cost, a_damage, a_armor in armor:
        for r in range(3):
            for wrings in combinations(rings, r):
                cost = w_cost + a_cost + sum(ring[0] for ring in wrings)
                damage = w_damage + a_damage + sum(ring[1] for ring in wrings)
                pl_armor = w_armor + a_armor + sum(ring[2] for ring in wrings)
                res = sim(100, damage, pl_armor, bo_hit, bo_damage, bo_armor)
                if res:
                    if cost < mincost:
                        mincost = cost
                else:
                    if cost > maxcost:
                        maxcost = cost

print(mincost)
print(maxcost)
