file=$1
args=("$@")
patterns=("${args[@]:1}")

while true; do
    echo "1. Display all occurrences"
    echo "2. Delete all occurrences"
    echo "3. Exit"
    read -p "Enter option: " check
    if [ $check == "1" ]; then
        for pattern in "$patterns"; do
            cat $file | grep -E --color $pattern
        done
    elif [ $check == "2" ]; then
        for pattern in "$patterns"; do
            p="s/${pattern}//g"
            sed -i -e $p $file
        done
    elif [ $check == "3" ]; then  
        echo "Exitting..."
        exit 1
    fi
done

echo "${patterns[@]} $file"