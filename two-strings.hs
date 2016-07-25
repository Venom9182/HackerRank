import Control.Monad
import qualified Data.Set as S

main = do
  n <- readLn
  replicateM_ n $ do
    a <- getLine
    b <- getLine
    putStrLn $ if S.null $ S.intersection (S.fromList a) (S.fromList b) then "NO" else "YES"
