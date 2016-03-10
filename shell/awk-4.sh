awk '{ORS = NR%2 ? ";" : "\n"}1'
