{-# LANGUAGE LambdaCase #-}
import Control.Monad
import Control.Monad.State
import Data.Char
import Data.Functor
import Data.Maybe
import qualified Data.Set as S
import qualified Data.ByteString.Char8 as B

int = state $ fromJust . B.readInt . B.dropWhile isSpace

data Op = Add !Int | Del !Int | Min

parse = do
  q <- int
  replicateM q $ do
    t <- int
    case t of
      1 -> Add <$> int
      2 -> Del <$> int
      3 -> return Min

main = do
  qs <- evalState parse <$> B.getContents
  foldM (\s -> \case
        Add x -> return $ S.insert x s
        Del x -> return $ S.delete x s
        Min -> print (fst . fromJust $ S.minView s) $> s
        ) S.empty qs
