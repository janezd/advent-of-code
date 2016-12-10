import re

re_inst = re.compile(r"(\D+) (\d+),(\d+) through (\d+),(\d+)")

def range2d(x0, y0, x1, y1):
    return (x + 1000 * y for x in range(x0, x1) for y in range(y0, y1))

lights = [False] * 1000000
for instruction in open("input.txt"):
    mo = re_inst.match(instruction)
    action = mo.group(1)
    x0, y0, x1, y1 = map(int, mo.group(2, 3, 4, 5))
    region = range2d(x0, y0, x1 + 1, y1 + 1)
    if action == "turn on":
        for i in region:
            lights[i] = True
    elif action == "turn off":
        for i in region:
            lights[i] = False
    else:
        for i in region:
            lights[i] = not lights[i]
print(sum(lights))


# 2nd part

meaning = {"turn on": 1, "turn off": -1, "toggle": 2}

lights = np.zeros((1000, 1000), dtype=np.bool)
for instruction in open("input.txt"):
    mo = re_inst.match(instruction)
    action = mo.group(1)
    x0, y0, x1, y1 = map(int, mo.group(2, 3, 4, 5))
    lights[x0:x1+1, y0:y1+1] += meaning[action]
    lights = lights.clip(0)
print(lights.sum())
