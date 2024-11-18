echo "Enter the first number"
read num1
echo "Enter the second number"
read num2
echo "Enter the third number"
read num3

if test $num1 -gt $num2 && test $num1 -gt $num3
then echo "$num1 is the greatest"
elif test $num2 -gt $num1 && test $num2 -gt $num3
then echo "$num2 is the greatest"
else echo "$num3 is the greatest"
fi