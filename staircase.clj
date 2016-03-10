(import java.util.Scanner)

(def scan (Scanner. *in*))

(let [n (.nextInt scan)
      s (apply str (concat (repeat (dec n) \space) (repeat n \#)))
      fmt (str "%" n "c\n")]
  (dotimes [i n] (printf fmt \#)))
