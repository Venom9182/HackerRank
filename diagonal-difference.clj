(import java.util.Scanner)

(def scan (Scanner. *in*))

(let [n (.nextInt scan)
      m (* n n)
      a (repeatedly m #(.nextInt scan))]
  (println (Math/abs (- (reduce #(+ %1 (nth a %2)) 0 (range 0 m (inc n)))
                        (reduce #(+ %1 (nth a %2)) 0 (range (dec n) (dec m) (dec n)))))))
