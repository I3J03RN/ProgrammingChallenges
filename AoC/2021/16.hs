{-# LANGUAGE TupleSections, LambdaCase #-}

import           Text.Parsec
import           Text.Parsec.Char
import           Text.Parsec.String

import           Control.Arrow                  ( (&&&) )

import           Data.Bifunctor
import           Data.Bool
import           Data.Char
import           Data.Either.Extra

class Bifunctor f => Bicotraversable f where
    bicollect :: Functor g => (a -> f b c) -> g a -> f (g b) (g c)
    bicollect f = bicosequence . fmap f

    bicosequence :: Functor g => g (f a b) -> f (g a) (g b)
    bicosequence = bicotraverse id id

    bicotraverse :: Functor g => (g a -> b) -> (g c -> d) -> g (f a c) -> f b d
    bicotraverse f g = bimap f g . bicosequence

instance Bicotraversable (,) where
  bicotraverse f g = f . fmap fst &&& g . fmap snd

main :: IO ()
main = readFile "16-1.in" >>= print . solve

solve :: String -> (Integer, Integer)
solve = fromRight (-1, -1) . parse node "input" . hexToBin

hexToBin :: String -> String
hexToBin =
  (>>= (\case
         '0' -> "0000"
         '1' -> "0001"
         '2' -> "0010"
         '3' -> "0011"
         '4' -> "0100"
         '5' -> "0101"
         '6' -> "0110"
         '7' -> "0111"
         '8' -> "1000"
         '9' -> "1001"
         'A' -> "1010"
         'B' -> "1011"
         'C' -> "1100"
         'D' -> "1101"
         'E' -> "1110"
         'F' -> "1111"
         _   -> ""
       )
  )

-- | len
binString :: Int -> Parser Integer
binString = flip binString' 0
 where
  binString' :: Int -> Integer -> Parser Integer
  binString' 0 n = pure n
  binString' l n =
    (\c -> 2 * n + ordInteger c - ordInteger '0') <$> anyChar >>= binString'
      (l - 1)

  ordInteger :: Char -> Integer
  ordInteger = toInteger . ord

-- | version length, type length
node :: Parser (Integer, Integer)
node = do
  v <- binString 3
  t <- binString 3
  if t == 4 then (v, ) <$> literal else first (v +) <$> operator t

literal :: Parser Integer
literal = literal' 0
 where
  literal' :: Integer -> Parser Integer
  literal' n =
    binString 5 >>= \x -> bool literal' pure (x < 16) (16 * n + x `mod` 16)

operator :: Integer -> Parser (Integer, Integer)
operator t = do
  i  <- binString 1
  ps <- bool lengthOperator numOperator (i /= 0)
  pure $ bicotraverse sum (work t) ps
 where
  work :: Integer -> [Integer] -> (Integer)
  work 0 = sum
  work 1 = product
  work 2 = minimum
  work 3 = maximum
  work 5 = \ls -> boolToInteger $ ls !! 0 > ls !! 1
  work 6 = \ls -> boolToInteger $ ls !! 0 < ls !! 1
  work 7 = \ls -> boolToInteger $ ls !! 0 == ls !! 1

  boolToInteger :: Bool -> Integer
  boolToInteger = bool 0 1

lengthOperator :: Parser [(Integer, Integer)]
lengthOperator = do
  l <- binString 15
  s <- sequence $ replicate (fromInteger l) anyChar
  pure $ fromRight [] $ parse (many node) "lengthOperator" s

numOperator :: Parser [(Integer, Integer)]
numOperator = binString 11 >>= sequence . (flip replicate node) . fromInteger






