import Data.List
import qualified Data.Map as M

main = do
  a <- getLine
  let m = M.toList $ foldl' (\m c -> M.insertWith (+) c 1 m) M.empty a :: [(Char, Int)]
  putStrLn $ if length (filter (odd . snd) m) <= 1 then "YES" else "NO"
