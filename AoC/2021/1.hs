import Control.Applicative

main :: IO ()
main = readFile "1-1.in" >>= print . liftA2 solve [1, 3] . pure . map read . lines

solve :: Int -> [Int] -> Int
solve n xs = length $ filter id $ zipWith (<) xs (drop n xs)
