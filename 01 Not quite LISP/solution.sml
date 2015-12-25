val floor = foldr (op +) 0;

fun base [] floor = 0
  | base (s::r) floor = if floor < 0 then 0 else 1 + base r (floor + s);

fun dir s = if s = #"(" then 1 else if s = #")" then ~1 else 0;
val inp = map dir (explode (valOf (TextIO.inputLine TextIO.stdIn)));
floor inp;
base inp 0;
