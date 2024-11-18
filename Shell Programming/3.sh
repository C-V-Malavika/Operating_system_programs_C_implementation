echo "Enter the value of N"
read N
num=N
fact=1

while test $N -gt 1
do
fact=$((fact*N))
N=$((N-1))
done
echo "THe factorial of $num is $fact"