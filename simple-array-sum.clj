(import 'java.util.Scanner)

(def scan (Scanner. *in*))

(let [n (.nextInt scan)]
  (println (loop [i n sum 0]
             (if (= i 0)
               sum
               (recur (dec i) (+ sum (.nextInt scan)))))))
