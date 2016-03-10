(import 'java.util.Scanner)

(def scan (Scanner. *in*))

(defn turan [N R]
  (let [sz0 (quot N R)
        sz1 (inc sz0)
        c1 (rem N R)
        c0 (- R c1)]
    (+ (* c0 sz0 c1 sz1)
       (quot (* c0 (dec c0) sz0 sz0) 2)
       (quot (* c1 (dec c1) sz1 sz1) 2))))

(dotimes [_ (.nextInt scan)]
  (let [N (.nextInt scan)
        M (.nextInt scan)]
    (println
     (loop [l 1 r N]
       (if (= l r)
         l
         (let [mi (quot (+ l r) 2)
               x (turan N mi)]
           (if (< x M)
             (recur (inc mi) r)
             (recur l mi))))))))
