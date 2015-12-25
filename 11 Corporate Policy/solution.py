import re

doubles = re.compile("(.)\\1.*(.)\\2")
illegal = re.compile("[ilo]")
value = list("hxbxwxba")
value = list("hxcaabcc")

while True:
    for i in range(7, -1, -1):
        if value[i] == 'z':
            value[i] = 'a'
        else:
            value[i] = chr(ord(value[i]) + 1)
            break
    vals = "".join(value)
    if doubles.search(vals) and not illegal.search(vals) and \
            any(ord(a) == ord(b) - 1 == ord(c) - 2
                for a, b, c in zip(value, value[1:], value[2:])):
        break
print("".join(value))
