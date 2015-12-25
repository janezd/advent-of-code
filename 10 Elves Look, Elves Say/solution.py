from itertools import groupby
from functools import reduce

print(len(reduce(lambda t, _: "".join("{}{}".format(len(list(v)), k)
                                      for k, v in groupby(t)),
                 range(50), "1113222113")))
