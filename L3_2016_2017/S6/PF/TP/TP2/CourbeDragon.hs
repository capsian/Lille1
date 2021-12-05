module Main where
import Graphics.Gloss

pointAintercaler :: Point -> Point -> Point
pointAintercaler (xA,yA)  (xB,yB) = ((xA+xB)/2 + (yB-yA)/2, (yA+yB)/2 + (xA-xB)/2)


pasDragon :: Path -> Path
pasDragon [] = []
pasDragon [a] = [a]
pasDragon [a,b] = a : pointAintercaler a b : pasDragon[b]
pasDragon (x:y:z:xs) = x : pointAintercaler x y : y : pointAintercaler z y : pasDragon(z:xs)


dragon :: Point -> Point -> [Path]
dragon a b = iterate pasDragon [a,b]


main :: IO ()
main = animate (InWindow "Dragon" (500, 500) (0, 0)) white (dragonAnime (50,250) (450,250))

dragonAnime a b t = Line (dragon a b !! (round t `mod` 20))


