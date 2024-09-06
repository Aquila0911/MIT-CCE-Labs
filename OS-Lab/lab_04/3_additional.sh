# Write a shell script that accepts a file name starting and ending line numbers as arguments and displays all the lines between the given line numbe
read -p "Enter a file name: " file

if [ ! -f $file ]; then
    echo "File not found"
    exit
fi

read -p "Enter the starting line number: " start
read -p "Enter the ending line number: " end

if [ $start -gt $end ]; then
    echo "Invalid range"
    exit
fi

i=1
while read line; do
    if [ $i -ge $start -a $i -le $end ]; then
        echo $line
    fi
    i=$(($i + 1))
done < $file

# add the last line to the file
if [ $i -ge $start -a $i -le $end ]; then
    echo $line
fi
