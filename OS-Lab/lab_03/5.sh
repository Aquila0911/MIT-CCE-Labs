read -p "Enter pattern: " pattern
directory='./'
find ${directory} -maxdepth 1 -type f -print0 | while read -d $'\0' file; do
    if [[ $file == *$pattern* ]]; then
        echo "Placing ${file} in ${pattern^^}"
        mkdir -p ${directory}${pattern^^}
        cp ${file} ${directory}${pattern^^}
    fi
done
