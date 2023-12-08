{-
 * Five of a kind   [5]          (prod 5)
 * Four of a kind   [1 4]        (prod 4)
 * Full house       [2 3]        (prod 6)
 * Three of a kind  [1 1 3]      (prod 3)
 * Two pair         [1 2 2]      (prod 4)
 * One pair         [1 1 1 2]    (prod 2)
 * High card        [1 1 1 1 1]  (prod 1)
-}

import Data.List (group, sort, sortBy)
import Data.Functor.Classes (liftCompare)

classify :: String -> Int
classify s = let es = length <$> group (sort s)
             in 10 * (6 - length es) - product es

classify' :: String -> Int
classify' s = maximum [ classify [ if c == 'J' then r else c | c <- s ] | r <- "23456789TQKA" ]

cmp :: String -> Char -> Char -> Ordering
cmp ord a b = compare (lookup a as) (lookup b as)
  where as = zip ord [1..]

solve :: String -> (String -> Int) -> [(String, Integer)] -> Integer
solve ord clas xs = sum $ zipWith (*) [1..] $ snd <$> sortBy g xs
  where
    g (a, _) (b, _) = liftCompare (liftCompare $ cmp ord) (clas a, a) (clas b, b)

main :: IO ()
main = do
  input <- readFile "7-1.in"
  let readHand s = (take 5 s, read $ drop 6 s)
      hands = map readHand $ lines input
  print $ solve "23456789TJQKA" classify hands
  print $ solve "J23456789TQKA" classify' hands

