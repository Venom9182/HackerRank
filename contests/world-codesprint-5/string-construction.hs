import Control.Monad
import Data.Functor
import Data.List

main = do
  cases <- readLn
  replicateM_ cases $ (length . group . sort) <$> getLine >>= print
