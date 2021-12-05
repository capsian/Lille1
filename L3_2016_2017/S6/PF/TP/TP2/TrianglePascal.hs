module TrianglePascal where

pasPascal :: [Integer] -> [Integer]
pasPascal [] = [1]
pasPascal l = 1 : zipWith (+) (init l) (tail l) ++ [1]

pascal :: [[Integer]]
pascal = iterate pasPascal []
