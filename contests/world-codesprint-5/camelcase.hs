import Data.Char
import Data.Functor
import Data.ByteString.Char8 as B

main = (succ . B.length . B.filter isUpper) <$> B.getLine >>= print
