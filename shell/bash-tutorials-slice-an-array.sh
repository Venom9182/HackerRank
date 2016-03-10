while IFS= read -r line; do
  a=("${a[@]}" "$line")
done
printf '%s ' "${a[@]:3:5}"
