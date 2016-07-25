import Data.Functor
import Data.List
import qualified Data.Map as M

main = do
  n <- readLn :: IO Int
  a <- (zip [0..] . map read . words) <$> getLine :: IO [(Int, Int)]
  case fst $ foldl' (\(ans,m) (i,x) ->
               let f (Just u) (Just v) = Just $ min u v
                   f Nothing v = v
                   f u Nothing = u
               in
               (f ans $ (i-) <$> M.lookup x m, M.insert x i m)) (Nothing,M.empty) a of
    Nothing -> putStrLn "-1"
    Just ans -> print ans
