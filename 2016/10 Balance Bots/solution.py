import re
from collections import defaultdict

def sign(s):
    return 1000 if s == "output" else 0

def put(chip, where):
    print("{} -> {}".format(chip, where))
    if where >= 1000:
        outputs[where - 1000] = chip
    else:
        bots[where].append(chip)

botbotline = re.compile(r"bot (\d+) gives low to (.*) (\d+) and high to (.*) (\d+)")
instructions = {}
bots = defaultdict(list)
outputs = {}

for line in open("input.txt"):
    if line.startswith("."):
        break
    mo = botbotline.match(line)
    if mo:
        bot, low_w, low, high_w, high = mo.groups()
        instructions[int(bot)] = (int(low) + sign(low_w), int(high) + sign(high_w))
    else:
        num, bot = map(int, re.findall("\d+", line))
        bots[bot].append(num)

while True:
    for bot, chips in sorted(bots.items()):
        if len(chips) == 2:
            break
    else:
        break
    low, high = sorted(chips)
    low_w, high_w = instructions[bot]
    if (low, high) == (17, 61):
        print(bot)
    print("Bot: ", bot)
    put(low, low_w)
    put(high, high_w)
    bots[bot] = ()

print(outputs)
print(bots)
print(outputs[0] * outputs[1] * outputs[2])
