import           Data.List
hui28 = length $ nub [ a ^ b | a <- [2 .. 100], b <- [2 .. 100] ]
