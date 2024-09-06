#  Write a shell script to input a file and display permissions of the owner group and others. 
read -p "Enter a file name: " file
if [ ! -f $file ]; then
    echo "File not found"
    exit
fi
echo "Owner permissions: $(ls -l $file | cut -c 2-4)"
echo "Group permissions: $(ls -l $file | cut -c 5-7)"
echo "Others permissions: $(ls -l $file | cut -c 8-10)"