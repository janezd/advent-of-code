import re
print(sum(bool(re.search("(..).*\\1", s) and re.search("(.).\\1", s)) for s in open("input.txt")))
print(sum(bool(re.search("(..).*\\1", s)) for s in open("input.txt")))
