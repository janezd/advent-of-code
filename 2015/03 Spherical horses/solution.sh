# Abuse file system as a set

if [ -d tmp ]; then rm -rf tmp; fi
mkdir tmp
x=0
y=0
touch tmp/$x.$y
while read -n 1 p; do
   if [ $p = "^" ]; then y=$((y - 1)); fi
   if [ $p = "v" ]; then y=$((y + 1)); fi
   if [ $p = "<" ]; then x=$((x - 1)); fi
   if [ $p = ">" ]; then x=$((x + 1)); fi
   touch tmp/$x.$y
done
echo `ls -1 tmp | wc -l`
rm -rf tmp
