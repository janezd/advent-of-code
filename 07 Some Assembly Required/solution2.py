# Transform expressions to Python, e.g.  "a AND b -> c" to "c = a & b"
from functools import reduce
import keyword
replacements = [("AND", "&"), ("OR", "|"), ("NOT", "~"), ("LSHIFT", "<<"), ("RSHIFT", ">>")] + \
               [(x, x + "_") for x in keyword.kwlist]
definitions = []
for v in open("input.txt"):
    expr, name = v.strip().split("->")
    definitions.append(reduce(lambda o, s: o.replace(*s), replacements, "{}={}".format(name, expr).strip()))


# Now the real work
while True:
    for expr in definitions:
        try: exec(expr)  # If it fails, don't mind
        except: pass
    try: print(a); break  # If this works, we're done
    except: pass
