declare -a a
i=0
while IFS= read -r line || [[ -n "$line" ]]; do
    a[i]=$line
    ((i++))
done
printf '%s ' "${a[@]}"
