echo "Enter the value of N"
read N
i=0
sum=0

echo "Enter $N numbers : "
while test $i -lt $N
do
read num
sum=$((sum+num))
i=$((i+1))
done
echo "Sum of the $N numbers is $sum"