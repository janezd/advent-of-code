<?php
$f = fopen("input.txt", "rt");
$l = $i = 0;
$b = -1;
while (!feof($f)) {
    $i++;
    $c = fgetc($f);
    if ($c == '(') $l++;
    if (($c == ')') && (--$l < 0) && ($b < 0)) {
        $b = $i;
    }
}
echo 'Floor: ', $l, ', underground: ', $b;
?>
