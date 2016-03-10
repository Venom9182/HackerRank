while IFS= read -r line; do
  a=("${a[@]}" "$line")
done
a=("${a[@]}" "${a[@]}" "${a[@]}")
printf '%s ' "${a[@]}"
