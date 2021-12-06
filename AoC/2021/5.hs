import           Control.Applicative
import           Control.Monad
import           Data.List
import           Data.Biapplicative
import           Data.Composition

data Line = (Int, Int) :-> (Int, Int)
    deriving (Show, Eq)

instance Read Line where
  readsPrec p s1 = do
    (x1, ',' : s2                  ) <- readsPrec p s1
    (y1, ' ' : '-' : '>' : ' ' : s3) <- readsPrec p s2
    (x2, ',' : s4                  ) <- readsPrec p s3
    (y2, s5                        ) <- readsPrec p s4
    return ((x1, y1) :-> (x2, y2), s5)

main :: IO ()
main =
  readFile "5-1.in"
    >>= print
    .   liftA2
          solve
          [\(x :-> y) -> uncurry (||) $ join (,) (==) <<*>> x <<*>> y, pure True]
    .   pure
    .   map read
    .   lines

solve :: (Line -> Bool) -> [Line] -> Int
solve f =
  length . filter ((> 1) . length) . group . sort . concatMap points . filter f

points :: Line -> [(Int, Int)]
points (x :-> y) =
  [ join (,) (\a b -> a + i * signum (b - a)) <<*>> x <<*>> y
  | i <- [0 .. uncurry max $ join (,) (abs .: (-)) <<*>> x <<*>> y]
  ]

instance (Num a, Num b) => Num (a, b) where
  (+)         = biliftA2 (+) (+)
  (*)         = biliftA2 (*) (*)
  (-)         = biliftA2 (-) (-)
  abs         = bimap abs abs
  signum      = bimap signum signum
  fromInteger = bimap fromInteger fromInteger . join (,)

points' :: Line -> [(Int, Int)]
points' (x :-> y) =
  [ x + join (,) i * signum (y - x) | i <- [0 .. uncurry max $ abs (x - y)] ]
