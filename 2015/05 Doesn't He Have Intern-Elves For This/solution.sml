val vowels = foldr (fn (x, acc) => acc + (if Char.contains "aeiou" x then 1 else 0)) 0;

fun repeat [] = false
    | repeat (x::nil) = false
    | repeat (x::y::rest) = (x = y) orelse repeat (y::rest);

(* fun forbidden x = exists (fn y => y = x) ["ab", "cd", "pq", "xy"]; *)
fun not_forb [] = true
    | not_forb (x::nil) = true
    | not_forb (x::y::rest) =
         let val xy = implode (x::[y]) in
             not (List.exists (fn f => f = xy) ["ab", "cd", "pq", "xy"]) andalso not_forb (y::rest)
         end;

fun str_ok s = vowels s >= 3 andalso repeat s andalso not_forb s;

fun count_ok f =
    let val lne = TextIO.inputLine f in
        if lne = NONE then 0
        else (if str_ok (explode (valOf lne)) then 1 else 0) + count_ok f
    end;

count_ok TextIO.stdIn;
