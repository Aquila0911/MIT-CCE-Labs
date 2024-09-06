pattern=".txt"
find ../ -type f -print0 | while read -d $'\0' file; do
    name=(${file//${pattern}/ })
    if [[ $file == *$pattern* ]]; then
        echo "Renaming ${file} to ${name[0]}.text"
        mv ${file} ${name}.text
    fi
done
