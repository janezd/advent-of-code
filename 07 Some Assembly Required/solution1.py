from functools import reduce, lru_cache
import re

# Change expressions to Python expressions, store in dictionary
# For instances, `a AND b -> c` becomes declaratiion['c'] = 'a & b'
replacements = [("AND", "&"), ("OR", "|"), ("NOT", "~"), ("LSHIFT", "<<"), ("RSHIFT", ">>")]
declaration = {}
for v in open("input.txt"):
    expr, name = v.strip().split("->")
    declaration[name.strip()] = reduce(lambda o, s: o.replace(*s), replacements, expr)

# Find the number by recursively evaluating expressions, using regular expressions
# to replace variable names with values
@lru_cache(10000)  # This is important: do not compute the same thing twice!
def solve_for(name):
    with_numbers = re.sub("[a-z]+", lambda mo: solve_for(mo.group()), declaration[name])
    return str(eval(with_numbers))


# 1st part
a = solve_for("a")
print(a)

# 2nd part
declaration["b"] = a
solve_for.cache_clear()
a = solve_for("a")
print(a)
