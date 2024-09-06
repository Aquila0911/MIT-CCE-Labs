check='y'
while [ ${check} == 'y' ]; do
    read -p "Enter basics: " basics
    read -p "Enter TA: " ta
    ga=$(($basics + $ta + 10 * $basics / 100))
    echo "GA = ${ga}"
    read -p "continue (y/n): " check
done
