import Data.Char

main :: IO()
main = do
  s <- getLine
  t <- getLine
  if s == "Y"
    then putStrLn $ map toUpper t 
    else putStrLn t
