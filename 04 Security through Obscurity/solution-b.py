from string import ascii_lowercase

for line in open("input.txt"):
    line = line.strip()
    common = line[-6:-1]
    letters, number = line[:-7].rsplit("-", 1)
    most_common = sorted(ascii_lowercase, key=lambda c: (-letters.count(c), c))
    if "".join(most_common[:5]) == common:
        decyphered = "".join(chr(97 + (ord(c) - 97 + int(number)) % 26) if c in ascii_lowercase else " " for  c in line[:-7])
        if "north" in decyphered:
            print(decyphered)
            print(number)
