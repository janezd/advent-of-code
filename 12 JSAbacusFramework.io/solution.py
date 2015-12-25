input = eval(open("input.txt").read())

def sum_up(input):
    if isinstance(input, int):
        return input
    elif isinstance(input, list):
        return sum(map(sum_up, input))
    elif isinstance(input, dict): # and "red" not in input.values():
        return sum(map(sum_up, input)) + sum(map(sum_up, input.values()))
    else:
        return 0

print(sum_up(input))
