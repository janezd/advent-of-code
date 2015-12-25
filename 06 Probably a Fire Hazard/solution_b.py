import re
import numpy as np

re_inst = re.compile(r"(\D+) (\d+),(\d+) through (\d+),(\d+)")
meaning = {"turn on": 1, "turn off": -1, "toggle": 2}

lights = np.zeros((1000, 1000), dtype=np.bool)
for instruction in open("input.txt"):
    mo = re_inst.match(instruction)
    action = mo.group(1)
    x0, y0, x1, y1 = map(int, mo.group(2, 3, 4, 5))
    lights[x0:x1+1, y0:y1+1] += meaning[action]
    lights = lights.clip(0)

print(lights.sum())
