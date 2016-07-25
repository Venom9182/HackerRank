import Data.Array
import Data.List hiding (foldl1', sum)
import Data.Foldable
import Data.Functor
import Data.Maybe
import Prelude hiding (sum)
import qualified Data.ByteString.Char8 as B

main = do
  [n, k] <- (map read . words) <$> getLine
  a <- (accumArray (+) 0 (0, k-1) . map ((\x -> (x `rem` k, 1)) . fst . fromJust . B.readInt) . B.words) <$> B.getLine :: IO (Array Int Int)
  print $ sum [if (2*i) `rem` k == 0 then min (a!i) 1 else max (a!i) (a!(k-i)) | i <- [0..k `quot` 2]]
