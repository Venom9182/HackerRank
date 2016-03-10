(import java.util.Scanner)

(def scan (Scanner. *in*))

(let [n (.nextInt scan)
      nn (float n)
      a (repeatedly n #(.nextInt scan))]
  (printf "%f\n%f\n%f\n" (/ (count (filter #(> % 0) a)) nn) (/ (count (filter #(< % 0) a)) nn) (/ (count (filter zero? a)) nn)))
