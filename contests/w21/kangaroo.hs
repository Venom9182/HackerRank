import Data.Functor

main = do
  [x1,v1,x2,v2] <- (map read . words) <$> getLine
  putStrLn $ if v1 > v2 && (x2-x1) `mod` (v1-v2) == 0 then "YES" else "NO"
