import hashlib
from itertools import count
import sys

s = sys.argv[1]
for i in count():
    if hashlib.md5((s + str(i)).encode("ascii")).hexdigest().startswith("000000"):
        break
print(i)
