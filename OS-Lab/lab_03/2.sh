read -p "Enter pattern: " pattern
find ../ -type f -print0 | while read -d $'\0' file; do
    if [[ $file == *$pattern* ]]; then
        echo "${file} matches"
    fi
done
