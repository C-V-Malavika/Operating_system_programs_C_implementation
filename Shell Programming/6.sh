echo "Enter a string"
read string

len=${#string}
rev=""

for ((i=$len-1; i>=0; i--))
do
rev="$rev${string:$i:1}"
done
echo "Reversed string is : $rev"