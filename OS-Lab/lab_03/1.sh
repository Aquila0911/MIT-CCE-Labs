find ../ -ls -print0 | while read -d $'\0' file; do
    fileData=(${file// / })
    if [ ${fileData[2]:0:1} == 'd' ]; then
        echo "${fileData[-1]} is a folder"
    else
        echo "${fileData[-1]} is a file"
    fi
done
