import Data.Functor
import Text.Printf

f x y = fromEnum $ x > y

main = do
  [a,b,c] <- (map read . words) <$> getLine :: IO [Int]
  [aa,bb,cc] <- (map read . words) <$> getLine :: IO [Int]
  printf "%d %d\n" (f a aa + f b bb + f c cc) (f aa a + f bb b + f cc c)
