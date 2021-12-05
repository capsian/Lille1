module TortueVolante where

import Graphics.Gloss
import LSysteme
import Tortue hiding (interpreteMot, interpreteSymbole,EtatDessin)

type EtatDessin = ([EtatTortue], [Path])

interpreteSymbole :: Config -> EtatDessin -> Symbole -> EtatDessin
interpreteSymbole c (et:ets,p:ps) s | s == '['  = (et:et:ets, p:p:ps)
                                    | s == ']'  = (ets, p:ps)
                                    | otherwise = (et':ets, (p ++ [fst et']):ps)
                                                where et' | s == 'F'  = avance c et
                                                          | s == '+'  = tourneAGauche c et
                                                          | s == '-'  = tourneADroite c et
                                                          | otherwise = error "wrong symbol"

-- Interprêtation des mots revisitée
interpreteMot :: Config -> Mot -> Picture
interpreteMot c m = line (head (snd (foldl (interpreteSymbole c) iE mF)))
    where iE = ([etatInitial c], [[fst (etatInitial c)]])
          mF = filtreSymbolesTortue c m
          
          
          
          
          
          
          
brindille :: LSysteme
brindille = lsysteme "F" regles
    where regles 'F' = "F[-F]F[+F]F"
          regles  s  = [s]

broussaille :: LSysteme
broussaille = lsysteme "F" regles
    where regles 'F' = "FF-[-F+F+F]+[+F-F-F]"
          regles  s  = [s]

brindilleAnime :: Float -> Picture
brindilleAnime = lsystemeAnime brindille (((0, -400), pi/2), 800, 1/3, 25*pi/180, "F+-[]")

broussailleAnime :: Float -> Picture
broussailleAnime = lsystemeAnime broussaille (((0, -400), pi/2), 500, 2/5, 25*pi/180, "F+-[]")          
          

