import           Text.Parsec
import           Text.Parsec.String
import           Text.Parsec.Char

import           Control.Monad.Except

import           Data.Bool
import           Data.Char
import           Data.Either.Combinators
import           Data.List
import           Data.Tuple.Extra

data N a = L a | V (N a) (N a)

instance Show a => Show (N a) where
  show (L x  ) = show x
  show (V l r) = '[' : show l ++ ',' : show r ++ "]"

node :: Parser (N Integer)
node =
  between (char '[') (char ']') (V <$> node <* char ',' <*> node)
    <|> L
    <$> natural

natural :: Parser Integer
natural = nat 0
 where
  nat :: Integer -> Parser Integer
  nat n =
    ((\c -> 10 * n + toInteger (ord c) - toInteger (ord '0')) <$> digit >>= nat)
      <|> pure n

explode :: N Integer -> Maybe (N Integer)
explode = fmap thd3 . ex' 0
 where
  ex' :: Int -> N Integer -> Maybe (Integer, Integer, N Integer)
  ex' _ (L x          ) = Nothing
  ex' 4 (V (L l) (L r)) = Just (l, r, L 0)
  ex' n (V l     r    ) = catchError
    ((\(x, y, nl) -> (x, 0, V nl (inc True y r))) <$> ex' (n + 1) l)
    $ pure $ (\(x, y, nr) -> (0, y, V (inc False x l) nr)) <$> ex' (n + 1) r

  inc :: Bool -> Integer -> N Integer -> N Integer
  inc _  0 x     = x
  inc go n (L x) = L $ x + n
  inc go n (V l r) | go        = V (inc go n l) r
                   | otherwise = V l $ inc go n r

split :: N Integer -> Maybe (N Integer)
split (L x) | x >= 10   = pure $ V (L $ x `div` 2) (L $ (x + 1) `div` 2)
            | otherwise = Nothing
split (V l r) =
  catchError ((\c -> (V c r)) <$> split l) (pure $ V l <$> split r)

reduce :: N Integer -> N Integer
reduce n = case catchError (explode n) (pure $ split n) of
  Just n' -> reduce n'
  Nothing -> n

add :: N Integer -> N Integer -> N Integer
add a b = reduce (V a b)

mag :: Num a => N a -> a
mag (L x  ) = x
mag (V l r) = 3 * mag l + 2 * mag r

main :: IO ()
main = readFile "18-1.in" >>= print . ([solve1, solve2] <*>) . pure . lines

solve1 :: [String] -> Integer
solve1 = mag . foldl1' add . map (fromRight' . parse node "hui")

solve2 :: [String] -> Integer
solve2 ns =
  let input = map (fromRight' . parse node "hui") ns
  in  maximum [ mag $ add a b | a <- input, b <- input ]
