find ./ -maxdepth 1 -type f -print0 | while read -d $'\0' file; do
    text=`cat ${file} | grep -Pz '^ex:|\.ex:\s?' | sed 's/ex:/Example:/g'`
    if [[ $text != "" ]] && [[ $file == *.text* ]]; then
        echo "matched ${file}"
        echo "${text}" > test.text
    fi
done
