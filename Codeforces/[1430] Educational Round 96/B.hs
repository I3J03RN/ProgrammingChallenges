import Control.Monad
import Data.List
import Data.Int

main :: IO()
main = do
  t <- readLn
  replicateM_ t $ do
    inputs <- map (read) <$> words <$> getLine
    line <- getLine
    print $ sum $ take ((inputs!!1) + 1) $ reverse $ (sort $ map (read) $ words line :: [Int64])
