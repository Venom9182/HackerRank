import Data.Functor

modulus = 1000000007

powMod a n
  | n == 0 = 1
  | even n = x*x `rem` modulus
  | otherwise = x*x `rem` modulus*a `rem` modulus
  where
    x = powMod a (n `quot` 2)

main = do
  [a,b,t] <- (map read . words) <$> getLine
  print $ powMod ((a+b) `quot` 2) t
