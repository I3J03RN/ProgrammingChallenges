{-# LANGUAGE LambdaCase #-}

import           Control.Applicative
import           Data.List

main :: IO ()
main = readFile "10-1.in" >>= print . ([solve, solve2] <*>) . pure . lines

sc :: Char -> Integer
sc = \case
  ')' -> 3
  ']' -> 57
  '}' -> 1197
  '>' -> 25137
  _   -> 0

sc2 :: Char -> Integer
sc2 = \case
  ')' -> 1
  ']' -> 2
  '}' -> 3
  '>' -> 4
  _   -> 0

o :: Char -> Char
o = \case
  '(' -> ')'
  '[' -> ']'
  '{' -> '}'
  '<' -> '>'
  _   -> '?'

solve :: [String] -> Integer
solve = sum . map (snd . (trav []))

solve2 :: [String] -> Integer
solve2 =
  (\xs -> head $ drop (div (length xs) 2) xs)
    . sort
    . map (calc 0)
    . filter (not . null)
    . map (fst . trav [])

trav :: String -> String -> (String, Integer)
trav xs "" = (xs, 0)
trav s (c : cs) | sc c == 0   = trav (o c : s) cs
                | head s == c = trav (tail s) cs
                | otherwise   = ([], sc c)

calc :: Integer -> String -> Integer
calc n ""       = n
calc n (c : cs) = calc (5 * n + sc2 c) cs

test :: [String]
test =
  [ "[({(<(())[]>[[{[]{<()<>>"
  , "[(()[<>])]({[<{<<[]>>("
  , "{([(<{}[<>[]}>{[]{[(<()>"
  , "(((({<>}<{<{<>}{[]{[]{}"
  , "[[<[([]))<([[{}[[()]]]"
  , "[{[{({}]{}}([{[{{{}}([]"
  , "{<[[]]>}<{[{[{[]{()[[[]"
  , "[<(<(<(<{}))><([]([]()"
  , "<{([([[(<>()){}]>(<<{{"
  , "<{([{{}}[<[[[<>{}]]]>[]]"
  ]
