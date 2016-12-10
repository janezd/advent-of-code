from hashlib import md5
from itertools import count

door_id = b"ugkcyxxp"
key = [None] * 8
c = count()
while not all(key):
    h = "asdfg"
    while not h.startswith("00000"):
        h = md5(door_id + str(next(c)).encode("ascii")).hexdigest()
    pos = int(h[5], 16)
    if pos < 8 and key[pos] is None:
        key[pos] = h[6]
    print("".join(c or "." for c in key))


# Not 2c730e5f
