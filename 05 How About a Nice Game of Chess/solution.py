from hashlib import md5
from itertools import count

door_id = b"ugkcyxxp"
key = ""
c = count()
while len(key) < 8:
    h = ""
    while not h.startswith("00000"):
        h = md5(door_id + str(next(c)).encode("ascii")).hexdigest()
    key += h[5]
    print(key)
