echo "Enter the value of N"
read N

if test $((N%2)) -eq 0
then echo "The number $N is even"
else echo "The number $N is odd"
fi