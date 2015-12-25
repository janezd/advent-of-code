import collections
import itertools
import re
re_sent = re.compile("(?P<who>\w+) would (?P<sign>((gain)|(lose))) (?P<points>\d+) happiness units by sitting next to (?P<whom>\w+).")

gains = collections.defaultdict(int)
knights = set()
for line in open("input.txt"):
    who, sign, points, whom = re_sent.search(line).group("who", "sign", "points", "whom")
    points = int(points) * [1, -1][sign == "lose"]
    gains[(who, whom)] += points
    gains[(whom, who)] += points
    knights |= {who, whom}

# Second part
print(max(sum(gains[(a, b)] for a, b in zip(order, order[1:]))
          for order in itertools.permutations(knights)))

# First part
first = knights.pop()
print(max(sum(gains[(a, b)] for a, b in zip(order, order[1:])) +
          gains[(first, order[0])] + gains[(first, order[-1])]
          for order in itertools.permutations(knights)))
