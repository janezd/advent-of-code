(* Pascal *)

program wrapping;
uses sysutils;

procedure sort(var a, b : integer);
var t : integer;
begin
    if (a > b) then begin
        t := a; a := b; b := t
    end
end;

var line: string;
var a, b, c: integer;
var paper: longint = 0;
var ribbon: longint = 0;
var x1, x2 : SizeInt;
begin
    while not eof() do begin
        readLn(line);
        x1 := pos('x', line);
        a := strToInt(leftStr(line, x1 - 1));
        line := rightStr(line, length(line) - x1);
        x1 := pos('x', line);
        b := strToInt(leftStr(line, x1 - 1));
        c := strToInt(rightStr(line, length(line) - x1));
        sort(a, b); sort(b, c); sort(a, b);
        paper := paper + 3 * a * b + 2 * c * (a + b);
        ribbon := ribbon + 2 * (a + b) + a * b * c;
    end;
    writeln('Paper: ', paper);
    writeln('Ribbon: ', ribbon);
end.
