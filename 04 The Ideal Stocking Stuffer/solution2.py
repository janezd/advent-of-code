from hashlib import md5
from itertools import count, takewhile

s = "bgvyzdsv"
print(1 + max(takewhile(lambda i: not md5((s + str(i)).encode("ascii")).hexdigest().startswith("000000"), count())))
