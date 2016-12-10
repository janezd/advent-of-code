from functools import reduce, lru_cache
import re
import keyword

# Change expressions to Python expressions, store in dictionary
replacements = [("AND", "&"), ("OR", "|"), ("NOT", "~"), ("LSHIFT", "<<"),
                ("RSHIFT", ">>")] + \
               [(x, x + "_") for x in keyword.kwlist]
declarations = []
for v in open("input.txt"):
    expr, name = reduce(lambda o, s: o.replace(*s), replacements, v).split("->")
    declarations.append((name.strip(), expr.strip(), set(re.findall("[a-z_]+", expr))))

known = {}
knowns = set()
# For 2nd part
# known = {"b": 46065}
# knowns = {"b"}
while "a" not in known:
    for name, expr, deps in declarations:
        if name not in knowns and deps <= knowns:
            known[name] = eval(expr, known)
            knowns.add(name)

print(known["a"])
