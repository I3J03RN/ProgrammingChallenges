import System.IO

counting :: [Integer]
counting = 2 : 5 : 13 : zipWith3 (\a b c -> a + b + 2 * c) counting (tail counting) (tail (tail counting))

getCount n = counting!!(n - 1)

main :: IO ()
main = do
  hSetBuffering stdout LineBuffering
  interact $ (unlines . fmap (show . (getCount) . read) . lines)
