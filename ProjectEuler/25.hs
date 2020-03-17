fibs :: [Integer]
fibs = let g f s = f : g s (f + s) in g 0 1

hui25 :: Int
hui25 = length $ takeWhile (\n -> 1000 > length (show n)) fibs
