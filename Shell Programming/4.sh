echo "Enter the value of N"
read N
a=0
b=1

for ((i=0; i<$N; i++))
do
echo -n "$a "
fn=$((a+b))
a=$b
b=$fn
done