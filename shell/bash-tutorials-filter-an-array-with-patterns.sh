while read -r line; do
  a=(${a[@]} $line)
done
printf %s\\n ${a[@]/*[aA]*/}
