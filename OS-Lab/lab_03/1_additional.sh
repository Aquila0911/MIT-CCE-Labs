# Write a shell script to check whether the user entered number is prime or not. 
read -p "Enter a number: " num
if [ $num -lt 2 ]; then
    echo "Not a prime number"
    exit
fi
for (( i=2; i<$num; i++ )); do
    if [ $(($num % $i)) -eq 0 ]; then
        echo "Not a prime number"
        exit
    fi
done
echo "Prime number"
