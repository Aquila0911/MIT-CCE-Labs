# Write a shell script that, given a file name as the argument will write the even numbered line to a file with name evenfile and odd numbered lines to a file called oddfile.
read -p "Enter a file name: " file
if [ ! -f $file ]; then
    echo "File not found"
    exit
fi
rm -f evenfile oddfile

i=1
while read line; do
    if [ $(($i % 2)) -eq 0 ]; then
        echo $line >> evenfile
    else
        echo $line >> oddfile
    fi
    i=$(($i + 1))
done < $file

# add the last line to the file
if [ $(($i % 2)) -eq 0 ]; then
    echo $line >> evenfile
else
    echo $line >> oddfile
fi
