import re

re_data = re.compile("(\w+): (\d+)")
re_filine = re.compile("Sue (\d+): (.+)")

def parse_sue(data):
    return {d: int(k) for d, k in (mo.group(1, 2) for mo in re_data.finditer(data))}

def match_sue(original, suspect):
    return all(original[k] == v for k, v in suspect.items())

def match_sue2(original, suspect):
    for k, v in suspect.items():
        ok = original[k]
        if k in ("cats", "trees"):
            if v <= ok:
                return False
        elif k in ("pomeranians", "goldfish"):
            if v >= ok:
                return False
        elif v != ok:
            return False
    return True

sue = parse_sue("""children: 3
cats: 7
samoyeds: 2
pomeranians: 3
akitas: 0
vizslas: 0
goldfish: 5
trees: 3
cars: 2
perfumes: 1""")

for line in open("input.txt"):
    no, data = re_filine.search(line).group(1, 2)
    if match_sue(sue, parse_sue(data)):
        print(no, data)

for line in open("input.txt"):
    no, data = re_filine.search(line).group(1, 2)
    if match_sue2(sue, parse_sue(data)):
        print(no, data)
