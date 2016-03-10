while IFS= read -r line; do
  a=("${a[@]}" "$line")
done
echo ${#a[@]}
