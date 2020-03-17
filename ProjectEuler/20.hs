import           Data.Char

fac :: Integer -> Integer
fac 0 = 1
fac n = n * (fac $ n - 1)

hui20 = sum $ map (digitToInt) $ show $ fac 100
