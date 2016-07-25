import Control.Monad.State
import Data.Char
import Data.Functor
import Data.List
import Data.Maybe
import Text.Printf
import qualified Data.ByteString.Char8 as B

int = state $ fromJust . B.readInt . B.dropWhile isSpace

parse = do
  n <- int
  d <- int
  a <- replicateM n int
  return (n, d, a)

main = do
  (n, d, a) <- evalState parse <$> B.getContents
  let (b, c) = splitAt d a
  forM_ c (printf "%d ")
  forM_ b (printf "%d ")
  putChar '\n'
