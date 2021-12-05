module ArbreBinaire where

import Control.Concurrent (threadDelay)


--Q1
data Arbre c v = Noeud 	{ 
                            coul :: c,	
                            val :: v,	
                            gauche :: Arbre c v,	
                            droite :: Arbre c v }
                    	| Feuille
					deriving (Show)

a0 = Feuille
a1 = (Noeud coul val Feuille Feuille)
a2 = (Noeud coul val Feuille (Noeud coul val Feuille Feuille))
a3 = (Noeud coul val (Noeud coul val Feuille Feuille) (Noeud coul val Feuille Feuille))
a4 = (Noeud coul val Feuille (Noeud coul val (Noeud coul val Feuille Feuille) Feuille))
a5 = (Noeud coul val Feuille (Noeud coul val (Noeud coul val Feuille (Noeud coul val Feuille Feuille)) Feuille))

	
--Q2
mapArbre :: (c->c) -> (v->v) -> Arbre c v -> Arbre c v 
mapArbre _ _ Feuille 						= Feuille
mapArbre f1 f2 (Noeud c v g d)	= Noeud (f1 c) (f2 v) (mapArbre f1 f2 g) (mapArbre f1 f2 d)

--Q3
hauteur :: Arbre c v -> Int
hauteur Feuille 		= 0
hauteur (Noeud _ _ d g) = 1 + max (hauteur g) (hauteur d)
--
taille :: Arbre c v -> Int
taille Feuille 					= 0
taille (Noeud _ _ g d)	= 1 + taille(d) + taille(g)

--Q4
dimension :: (Arbre c v -> Int) -> Arbre c v -> Int
dimension f k = f k

--Q5
peigneGauche :: [(c,a)] -> Arbre c a
peigneGauche [] 		= Feuille
peigneGauche (x:xs) = Noeud (fst x) (snd x) (peigneGauche xs) Feuille
--peigneGauche' 			= foldr (\(c, v) x -> Noeud c v x Feuille) Feuille

--Q6
prop_hauteurPeigne xs = length xs == hauteur (peigneGauche xs)

--Q7
prop_taillePeigne  xs = length xs == taille (peigneGauche xs)

--Q8
estComplet :: Arbre c a -> Bool
estComplet Feuille = True
estComplet (Noeud _ _ g d) = taille(d) == taille(g)

--Q9
estComplet' (Noeud _ _ g d) = (dimension taille d) == (dimension taille g)

--Q10
--peigneGaucheComplet xs = estComplet (peigneGauche xs)
complet :: Int -> [(c, a)] -> Arbre c a
complet 0 _ = Feuille
complet n l = Noeud c v (complet (n-1) l1) (complet (n-1) l2)
         			where (l1, ((c,v):l2)) = splitAt (length l `quot` 2) l

--Q10
--nb feuille = 2 ^ (h-1)
nb_noeud_pour_AB_hauteur :: Int -> Int
nb_noeud_pour_AB_hauteur 0 = 0
nb_noeud_pour_AB_hauteur n = 1 + 2 * (nb_noeud_pour_AB_hauteur (n-1))

--Q12
repeat' :: a -> [a]
repeat' a = a : repeat' a
repeat'' :: a -> [a]
repeat'' a = iterate id a
repeat''' :: a -> [a]
repeat''' a = iterate (\ x -> x) a

--Q13
liste_alpha = [((),j) | j <- ['a'..]]
liste_alpha_pour_AB_hauteur n = take (nb_noeud_pour_AB_hauteur n) liste_alpha


--Q14
aplatit :: Arbre c a -> [(c,a)]
aplatit Feuille = []
aplatit (Noeud c v g d) = (aplatit g) ++ (c,v) : (aplatit d)

tmp = map snd (aplatit (complet 4 (take 15 ([((),j) | j <- ['a'..]]))))
test_aplatit = tmp == "abcdefghijklmno"
test_aplatit' xs = tmp == "abcdefghijklmno"

--Q15
element :: Eq a => a -> Arbre c a -> Bool
element _ Feuille = False
element a (Noeud _ k g d) | a == k = True 
						  | otherwise = element a g || element a d
test_elem = element 'b' (complet 4 (take 15 ([((),j) | j <- ['a'..]])))
test_elem' = element 8 (complet 4 (take 15 ([((),j) | j <- [1..]])))

--Q16
noeud :: (c -> String) -> (a -> String) -> (c,a) -> String
noeud cl vl (c,a) = vl a ++ " [color=" ++ cl c ++ ", fontcolor=" ++ cl c ++ "]"

--Q17
{--
valr :: Arbre c a -> a
valr Feuille = error "valr feuille"
valr (Noeud _ a _ _) = a
arcs :: Arbre c a -> [(a,a)]
arcs Feuille = []
arcs (Noeud _ _ Feuille Feuille) = []
arcs (Noeud _ a g d) = (a,(valr g)) : (a,(valr d)) : (arcs g) ++ (arcs d)
--}
arcs :: Arbre c a -> [(a,a)]
arcs Feuille                                           = []
arcs (Noeud _ _ Feuille Feuille)                       = []
arcs (Noeud _ v Feuille d@(Noeud _ vd _ _))            = (v,vd):arcs d
arcs (Noeud _ v g@(Noeud _ vg _ _) Feuille)            = (v,vg):arcs g
arcs (Noeud _ v g@(Noeud _ vg _ _) d@(Noeud _ vd _ _)) = (v,vg):(v,vd):arcs g ++ arcs d



test_arcs = arcs (complet 3 (take 7 ([((),j) | j <- ['a'..]])))

--Q18
arc :: (a -> String) -> (a,a) -> String
arc f (x, y) = (f x) ++ " -> " ++ (f y)

--Q19
dotise :: String -> (c -> String) -> (a -> String) -> Arbre c a -> String
dotise t fc fv a = unlines (
                    ["digraph \"" ++ t ++ "\" {","node [shape=circle]"]
                    ++ (map (noeud fc fv) (aplatit a))
                    ++ (map (arc fv) (arcs a))
                    ++ ["}"]
                )


-- Arbre coul int
gen_coul :: Int -> String
gen_coul v 	| even v 	= "r"
			| otherwise = "g"

liste_num = [(c,v) | v <- [1..] ,c <- (gen_coul v)]
liste_num_pour_AB_hauteur n = take (nb_noeud_pour_AB_hauteur n) liste_num

fonc_coul :: Char -> String
fonc_coul c | c == 'r' = "red"
			| c == 'g' = "green"
			| otherwise = ""

test_AB_num :: IO ()
test_AB_num = do
        writeFile "arbre_num.dot" (
        	dotise 
        		"arbre_num" 
        		fonc_coul 
        		(\a -> show a)
        		(complet 5 (liste_num_pour_AB_hauteur 5))
        		)


--Q20
elementR :: (Eq a, Ord a) => a -> Arbre c a -> Bool
elementR a Feuille 			= False
elementR a (Noeud _ v g d)  | a == v = True
                            | a < v  = elementR a g
                            | a > v  = elementR a d

--Q21
data Couleur = Rouge | Noir deriving (Show,Eq)
couleurToString :: Couleur -> String
couleurToString Rouge	= "red"
couleurToString Noir	= "black"

type ArbreRN a = Arbre Couleur a

--Q22
equilibre :: ArbreRN a -> ArbreRN a
equilibre Feuille = Feuille
equilibre (Noeud _ z (Noeud Rouge y (Noeud Rouge x a b) c) d) = Noeud Rouge y (Noeud Noir x a b) (Noeud Noir z c d)
equilibre (Noeud _ z (Noeud Rouge x a (Noeud Rouge y b c)) d) = Noeud Rouge y (Noeud Noir x a b) (Noeud Noir z c d)
equilibre (Noeud _ x a (Noeud Rouge z (Noeud Rouge y b c) d)) = Noeud Rouge y (Noeud Noir x a b) (Noeud Noir z c d)
equilibre (Noeud _ x a (Noeud Rouge y b (Noeud Rouge z c d))) = Noeud Rouge y (Noeud Noir x a b) (Noeud Noir z c d)
equilibre a = a

--Q23
check_racine :: Arbre Couleur a -> Arbre Couleur a
check_racine Feuille         = Feuille
check_racine (Noeud _ r g d) = Noeud Noir r g d

insertAB :: Ord a => a -> Arbre Couleur a -> Arbre Couleur a
insertAB valeur arbre = check_racine (ins valeur arbre)
  where ins v Feuille                              = Noeud Rouge v Feuille Feuille
        ins v abr@(Noeud c r g d) | elementR v abr = abr
                                  | v < r          = equilibre (Noeud c r (ins v g) d)
                                  | otherwise      = equilibre (Noeud c r g (ins v d))

--Q24


--Q25
tmp_arb :: ArbreRN a
tmp_arb = Feuille
arbresDot :: String -> [String]
arbresDot l = func l tmp_arb
				where	
					func [] _ = []
					func (x:xs) tmp = dotise "Arbre" couleurToString (\a -> [a]) new_tmp : func xs new_tmp
										where 
											new_tmp = insertAB x tmp


main = mapM_ ecrit arbres
    where ecrit a = do writeFile "arbre.dot" a
                       threadDelay 100000
          arbres  = arbresDot "gcfxieqzrujlmdoywnbakhpvst" {--['a'..'z']--}





-- TESTS
test1 :: ArbreRN Int
test1 = Feuille
test1_r = estComplet test1

remplire n abr = insertAB n abr 

test2 = insertAB 0 test1

test3 = insertAB 1 test2

test4 = insertAB 2 test2

desq1 = Noeud Noir 'z' (Noeud Rouge 'y' (Noeud Rouge 'x' (Noeud Noir 'a' Feuille Feuille) (Noeud Noir 'b' Feuille Feuille)) (Noeud Noir 'c' Feuille Feuille)) (Noeud Noir 'd' Feuille Feuille)
desq1_r = putStr (dotise "desq1" couleurToString (\a -> show a) desq1)
desq1_equi = equilibre(desq1)
desq1_equi_r =  putStr (dotise "desq4" couleurToString (\a -> show a) desq1_equi)

desq2 = Noeud Noir 'z' (Noeud Rouge 'y' (Noeud Rouge 'x' (Noeud Noir 'a' Feuille Feuille) (Noeud Noir 'b' Feuille Feuille)) (Noeud Noir 'c' Feuille Feuille)) (Noeud Noir 'd' Feuille Feuille)
desq2_r = putStr (dotise "desq2" couleurToString (\a -> show a) desq2)
desq2_equi = equilibre(desq2)
desq2_equi_r =  putStr (dotise "desq4" couleurToString (\a -> show a) desq2_equi)

desq3 = Noeud Noir 'x' (Noeud Noir 'a' Feuille Feuille) (Noeud Rouge 'z' (Noeud Rouge 'y' (Noeud Noir 'b' Feuille Feuille) (Noeud Noir 'c' Feuille Feuille)) (Noeud Noir 'd' Feuille Feuille))
desq3_r = putStr (dotise "desq2" couleurToString (\a -> show a) desq3)
desq3_equi = equilibre(desq3)
desq3_equi_r =  putStr (dotise "desq4" couleurToString (\a -> show a) desq3_equi)

desq4 = Noeud Noir 'x' (Noeud Noir 'a' Feuille Feuille) (Noeud Rouge 'y' (Noeud Noir 'b'  Feuille Feuille) (Noeud Rouge 'z' (Noeud Noir 'c' Feuille Feuille) (Noeud Noir 'd' Feuille Feuille)))
desq4_r = putStr (dotise "desq2" couleurToString (\a -> show a) desq4)
desq4_equi = equilibre(desq4)
desq4_equi_r =  putStr (dotise "desq4" couleurToString (\a -> show a) desq4_equi)


gen_complet = [((Rouge),v) | v <- [1..] ]
take_gen_complet n = take (nb_noeud_pour_AB_hauteur n) gen_complet

peigne_equi = equilibre (peigneGauche (take_gen_complet 5))
peigne_equi_r =  putStr (dotise "peigne_equi_r" (\a -> show a) (\a -> show a) peigne_equi)

