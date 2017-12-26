import re

rev = re.compile(r"(\w)(?!\1)(\w)\2\1")
revnb = re.compile(r"\[\w*(\w)(?!\1)(\w)\2\1\w*\]")
print(sum(not revnb.search(v) and bool(rev.search(v)) for v in open("input.txt")))
print("".join(v for v in open("input.txt") if not revnb.search(v) and bool(rev.search(v))))

aba1 = re.compile(r"(\w)(?!\1)(\w)\1.*\[\w*\2\1\2\w*\]")
aba2 = re.compile(r"\[\w*(\w)(?!\1)(?!\])(\w)\1\w*\].*\2\1\2")
print(sum(bool(aba1.search(v) or aba2.search(v)) for v in open("input.txt")))

# 163 too low
# 245 too high
