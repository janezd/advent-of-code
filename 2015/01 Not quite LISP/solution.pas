program not_quite_lisp;

var c : char;
var floor : integer = 0;
var first_basement : integer = -1;
var position : integer = 1;
begin
    while not eof() do begin
        read(c);
        if (c = '(') then
            floor := floor + 1;
        if (c = ')') then begin
            floor := floor - 1;
            if (floor < 0) and (first_basement < 0) then
                first_basement := position
        end;
        position := position + 1
    end;
    writeln('Last floor: ', floor);
    writeln('First basement: ', first_basement);
end.
