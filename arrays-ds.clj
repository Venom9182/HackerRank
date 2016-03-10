(require '[clojure.string :refer [join split]])

(println (join " " (reverse (split (second (line-seq (java.io.BufferedReader. *in*))) #" "))))
