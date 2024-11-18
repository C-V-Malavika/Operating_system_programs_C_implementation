echo "Enter the value of N"
read N

cnt=0
num=$N

while test $num -gt 0
do
num=$((num/10))
cnt=$((cnt+1))
done

num=$N
arm=0

while test $num -gt 0
do
val=$((num%10))
arm=$((arm+val**cnt))
num=$((num/10))
done

if test $N -eq $arm
then echo "The number $N is an armstrong number"
else echo "The number $N is not an armstrong number"
fi