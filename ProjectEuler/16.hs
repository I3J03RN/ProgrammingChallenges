import           Data.Char

hui16 = sum [ digitToInt c | c <- show $ 2 ^ 1000 ]
