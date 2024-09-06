ord() {
  ascii_value=$(printf "%d" "'$1")
  return $ascii_value
}

sum_string() {
    local string="$@"
    length=${#string}
    sum=0
    for ((i = 0; i < length; i++)); do
        char="${string:i:1}"
        ord "${char}"
        value=$?
        sum=$(($sum+$value))
    done
    echo "$sum"
}

sort_list() {
    local arr=("$@")
    length=${#@}
    for ((i = 1; i < length + 1; i++)); do
        for ((j = 1; j < length + 1 - i; j++)); do
            a="${@:j:1}"-i -e
            b="${@:j+1:1}"
            total_a=$(sum_string "${a}")
            total_b=$(sum_string "${b}")
            if [[ $total_a -gt $total_b ]]; then
                tmp=${arr[j]}
                arr[j]=${arr[j-1]}
                arr[j-1]=$tmp
            fi
        done
    done
    echo "${arr[@]}"
}

arr=("$@")
# echo "${arr[@]}"
sort_list "${arr[@]}"