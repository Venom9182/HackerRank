import Data.Array
import Data.Functor

main = do
  [n, k] <- (map read . words) <$> getLine
  a <- (listArray (0, n-1) . map read . words) <$> getLine :: IO (Array Int Int)
  print $ sum [if (a!i+a!j) `rem` k == 0 then 1 else 0 | i <- [0..n-1], j <- [i+1..n-1]]
