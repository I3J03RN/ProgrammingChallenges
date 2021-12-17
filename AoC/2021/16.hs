{-# LANGUAGE LambdaCase #-}

import Text.Parsec
import Text.Parsec.Char
import Text.Parsec.String

main :: IO ()
main = readFile "10-1.in" >>= print . solve

solve :: String -> Integer
solve = undefined

hexToBin :: String -> String
hexToBin = (>>=(\case '0' -> "0000"
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
                      'F' -> "1111"))

-- len -> cur
binString :: Int -> Integer -> Parser Integer
binString 0 n = pure n
binString l n = (\c -> 2 * n + if c == '1' then 1 else 0) <$> anyChar >>= binString (l - 1)

-- version length, type length
node :: Int -> Int -> Parser Integer
node vl tl = do
  v <- binString vl 0
  t <- binString tl 0
  pure (v + t)

