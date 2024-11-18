echo "Enter a string"
read string

cnt=0
len=${#string}

for ((i=0; i<$len; i++))
do
current="${string:$i:1}"
if [[ "$current" =~ [aAeEiIoOuU] ]]
then cnt=$((cnt+1))
fi
done
echo "Number of vowels in the string $string is : $cnt"