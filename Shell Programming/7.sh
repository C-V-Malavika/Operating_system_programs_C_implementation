echo "Enter a string"
read string

echo "Enter the character to be replace"
read char

echo "Enter the replacing character"
read rep

len=${#string}
replaced_string=""

for ((i=0; i<$len; i++))
do
if test "$char" = "${string:$i:1}"
then replaced_string="$replaced_string$rep"
else replaced_string="$replaced_string${string:$i:1}"
fi
done
echo "Replaced string is : $replaced_string"