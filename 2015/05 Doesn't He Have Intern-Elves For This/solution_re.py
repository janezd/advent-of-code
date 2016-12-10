import re
print(sum(re.search(".*([aeiou].*){3}", s) and re.search("(.)\\1", s) and
          not re.search("(ab)|(cd)|(pq)|(xy)", s) or 0 for s in input()))
