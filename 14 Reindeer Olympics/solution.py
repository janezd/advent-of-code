import re

time = 2503

re_line = re.compile("(\d+)\D+(\d+)\D+(\d+)")
times = []
horses = []
for line in open("input.txt"):
    speed, run, rest = map(int, re_line.search(line).groups())
    horses.append((speed, run, rest))
    times.append((time // (run + rest) * run + min(run, time % (run + rest))) * speed)
print(max(times))

dist = [0] * len(horses)
points = [0] * len(horses)

def running(t, run, rest):
    return t % (run + rest) < run

for t in range(time):
    for i, (speed, run, rest) in enumerate(horses):
        if running(t, run, rest):
            dist[i] += speed
    win = max(dist)
    for i, d in enumerate(dist):
        if d == win:
            points[i] += 1
print(points)
print(sum(points))
