{-# LANGUAGE ScopedTypeVariables #-}
import Data.Functor
import Data.List
import Data.Ratio
import Text.Printf

fac = scanl (*) 1 [1..] :: [Integer]

main = do
  n <- readLn :: IO Int
  b <- (map read . words) <$> getLine :: IO [Int]
  let a = group $ sort b
      ans = (realToFrac (fac!!n) /) . realToFrac . product $ map ((fac!!) . length) a :: Rational
  printf "%.6f\n" (if b == sort b then 0 else fromRational ans :: Double)
