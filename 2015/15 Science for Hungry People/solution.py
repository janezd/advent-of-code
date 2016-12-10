import numpy
import re

ing = """Sugar: capacity 3, durability 0, flavor 0, texture -3, calories 2
Sprinkles: capacity -3, durability 3, flavor 0, texture 0, calories 9
Candy: capacity -1, durability 0, flavor 4, texture 0, calories 1
Chocolate: capacity 0, durability 0, flavor -2, texture 2, calories 8""".splitlines()

re_number = re.compile(r"-?\d+")
a = numpy.array([[int(x) for x in re_number.findall(v)] for v in ing]).T

ac = a[:-1,:]
cal = a[-1]
print(max((ac * [a, b, c, 100 - a - b - c]).sum(axis=1).clip(min=0).prod()
          for a in range(101) for b in range(101 - a) for c in range(101 - a - b)
          if (cal * [a, b, c, 100 - a - b - c]).sum() == 500))
