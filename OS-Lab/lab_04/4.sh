if [ "$#" -lt 2 ]; then
    echo "Usage: $0 [-linecount | -wordcount | -charcount] <filename>"
    exit 1
fi
 
operation=""
filename=""
 
while [ "$#" -gt 0 ]; do
    case "$1" in
        -linecount)
            operation="linecount"
            shift
            ;;
        -wordcount)
            operation="wordcount"
            shift
            ;;
        -charcount)
            operation="charcount"
            shift
            ;;
        *)
            filename="$1"
            shift
            ;;
    esac
done
 
if [ -z "$filename" ]; then
    echo "Usage: $0 [-linecount | -wordcount | -charcount] <filename>"
    exit 1
fi
 
case "$operation" in
    linecount)
        lines=$(wc -l < "$filename")
        echo "Line count: $lines"
        ;;
    wordcount)
        words=$(wc -w < "$filename")
        echo "Word count: $words"
        ;;
    charcount)
        chars=$(wc -c < "$filename")
        echo "Character count: $chars"
        ;;
    *)
        echo "Invalid option. Please provide -linecount, -wordcount, or -charcount."
        exit 1
        ;;
esac