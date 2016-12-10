from string import ascii_lowercase

total = 0
for line in open("input.txt"):
    line = line.strip()
    common = line[-6:-1]
    letters, number = line[:-7].rsplit("-", 1)
    letters.replace("-", "")
    most_common = sorted(ascii_lowercase, key=lambda c: (-letters.count(c), c))
    if "".join(most_common[:5]) == common:
        total += int(number)
print(total)
