c="y"
for file in "$@"
do 
    read -p "Remove file ${file} (y/n): " check
    if [ $check == $c ]; then
        rm $file
        echo "Removed $file"
    else
        echo "Continued..."
    fi
done