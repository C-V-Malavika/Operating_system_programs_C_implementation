echo "Enter the value of N"
read N

rev=0
num=$N

while test $num -gt 0
do 
val=$((num%10))
rev=$((rev*10+val))
num=$((num/10))
done

if test $rev -eq $N
then echo "The number $N is a palindrome"
else echo "The number $N is not a palindrome"
fi