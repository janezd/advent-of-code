from hashlib import md5
from itertools import count
import re

salt = "cuanljph"
#salt = "abc"

hexs = "01234566789abcdef"

cache3 = {h: set() for h in hexs}
re3 = re.compile(r"(.)\1\1")

keys = set()
key_at_64 = 0
for i in count():
    if len(keys) >= 64:
        key_at_64 = max(keys)
    if len(keys) >= 64 and i > key_at_64 + 1000:
        break
    h = md5((salt + str(i)).encode("ascii")).hexdigest()
    mo = re3.search(h)
    if mo:
        cache3[mo.group(1)].add(i)
    if i == 7986:
        print(mo.group(1))
    for c in "0123456789abcdef":
        if 5 * c in h:
            print(i, h)
            keys |= set(range(max(0, i - 1000), i)) & cache3[c]
print(sorted(keys)[63])
print("\n".join("{}. {}".format(i + 1, k) for i, k in enumerate(sorted(keys))))


# 24398 too high
