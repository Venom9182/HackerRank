import Control.Monad
import Data.Functor
import Data.List

main = do
  [n, k] <- (map read . words) <$> getLine
  (b, a) <- partition ((/=0).snd) <$> replicateM n (((\[x,y] -> (x,y)) . map read . words) <$> getLine) :: IO ([(Int,Int)], [(Int,Int)])
  let (c, d) = splitAt k . reverse $ sort b
  print $ sum (map fst c) - sum (map fst d) + sum (map fst a)
