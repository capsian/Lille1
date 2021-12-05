module LSysteme where

type Symbole  = Char
type Mot      = [Symbole]
type Axiome   = Mot
type Regles   = Symbole -> Mot
type LSysteme = [Mot]

--motSuivant :: Char -> [Char] -> [Char] -> [Char]
motSuivant :: Regles -> Mot -> Mot
motSuivant _ [] = []
motSuivant r (x:xs) = r x ++ motSuivant r xs

motSuivant' :: Regles -> Mot -> Mot
motSuivant' = concatMap

-- regles
regle :: Axiome
regle = "F-F++F-F"

vonKoch :: Symbole -> Mot
vonKoch '+' = "+"
vonKoch '-' = "-"
vonKoch 'F' = regle
vonKoch _ = ""

lsysteme :: Axiome -> Regles -> LSysteme
lsysteme ax reg = iterate (motSuivant reg) ax
