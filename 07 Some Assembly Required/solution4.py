# Like solution3, but with functions

# Transform expressions to Python, e.g.  "a AND b -> c" to "c = a & b"
def read(filename):
    from functools import reduce
    import keyword
    replacements = [("AND", "&"), ("OR", "|"), ("NOT", "~"), ("LSHIFT", "<<"),
                    ("RSHIFT", ">>")] + \
                   [(x, x + "_") for x in keyword.kwlist]
    definitions = []
    for v in open(filename):
        expr, name = v.strip().split("->")
        definitions.append(reduce(lambda o, s: o.replace(*s), replacements,
                                  "{}={}".format(name, expr).strip()))
    return definitions


def compute(var, definitions):
    while True:
        for expr in definitions:
            try:
                exec(expr)
                return eval(var)
            except:
                pass

definitions = read("input.txt")
print(compute("a", definitions))
