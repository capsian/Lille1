{-# LANGUAGE FlexibleInstances     #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Interprete where

import Parser
import Data.Char
import Data.Maybe
import Control.Monad (liftM, ap)


type Nom = String

data Expression = Lam Nom Expression
                | App Expression Expression
                | Var Nom
                | Lit Litteral
                deriving (Show,Eq)

data Litteral = Entier Integer
              | Bool   Bool
              deriving (Show,Eq)


--Q1
espacesP :: Parser()
espacesP = many (car ' ') >>= \_ -> pure()

--Q2
nomP :: Parser Nom
nomP = some (carQuand isLower) >>= \n -> espacesP >>= \_ -> return n

--Q3
varP :: Parser Expression
varP = nomP >>= \n -> return (Var n)

{--Q4
applique :: [Expression] -> Expression
applique [e] = e
applique xs  = App (applique' y) yy
             where y  = init xs
                   yy = last xs
--}
applique = foldl1 App

--Q5
exprP :: Parser Expression
--exprP = varP
--exprP = varP <|> lambdaP
--exprP = varP <|> lambdaP <|> exprParentheseeP
exprP = exprParentheseeP <|> varP <|> lambdaP <|> nombreP <|>  booleenP

exprsP :: Parser Expression
exprsP = some (exprP) >>= \x
         -> pure (applique x)

--Q6
lambdaP :: Parser Expression
lambdaP =   ( car 'λ' <|> car '\\') >>= \_
          -> espacesP >>= \_
          -> varP     >>= \x
          -> espacesP >>= \_
          -> car '-'  >>= \_
          -> car '>'  >>= \_
          -> espacesP >>= \_
          -> exprsP   >>= \expr
          -> espacesP >>= \_
          -> return (Lam (get x) expr)
   where get (Var v) = v
{--
lambdaP =   do car '\\'
              espacesP
              x <- varP
              espacesP
              car '-'
              car '>'
              espacesP
              expr <- exprsP
              espacesP
              return (Lam (get x) expr)
          where get (Var v) = v
--}

--Q8
exprParentheseeP :: Parser Expression
exprParentheseeP = do
                      car '('
                      espacesP
                      x <- exprsP
                      espacesP
                      car ')'
                      espacesP
                      return x

--Q9
chiffre :: Parser Char
chiffre = carQuand isDigit

nombre :: Parser String
nombre = some chiffre

entier :: Parser Integer
entier =    nombre >>= \n
         -> return (read n)

nombreP :: Parser Expression
nombreP =    entier   >>= \e
          -> espacesP >>= \_
          -> return (Lit (Entier e))

--Q10
booleenP :: Parser Expression
booleenP = do
              n <- (chaine "True" <|> chaine "False")
              espacesP
              return (Lit (Bool (n=="True")))

--Q11
expressionP :: Parser Expression
expressionP = espacesP                >>= \_ ->
              exprsP                  >>= \x ->
              pure x
--Q12
ras :: String -> Expression
ras str = case runParser expressionP str of
        Just (r, "") -> r 
        _            -> error "ras:Erreur d'analyse syntaxique"
              


data ValeurA = VLitteralA Litteral
             | VFonctionA (ValeurA -> ValeurA)


--Q13-14
instance Show ValeurA where
    show (VFonctionA _)          = "λ"
    show (VLitteralA (Entier n)) = show n
    show (VLitteralA (Bool n))   = show n

type Environnement a = [(Nom, a)]

--Q15
interpreteA :: Environnement ValeurA -> Expression -> ValeurA
interpreteA _   (Lit x)   = VLitteralA x
interpreteA env (Var x)   = fromJust (lookup x env)
interpreteA env (Lam x y) = VFonctionA (\v -> interpreteA ((x, v):env) y)
interpreteA env (App x y) = check_error (interpreteA env x) (interpreteA env y)
        where check_error (VFonctionA f) = f
              check_error e = error ("interpreteA:check_error:Erreur :" ++ show e)

--Q16
negA :: ValeurA
negA = VFonctionA f
       where f (VLitteralA (Entier v)) = VLitteralA (Entier (-v))
             f e = error ("negA:Erreur d'analyse syntaxique : " ++ show e)

--Q17
addA :: ValeurA
addA = VFonctionA g
       where g (VLitteralA (Entier x)) = VFonctionA gg
                    where gg (VLitteralA (Entier y)) = VLitteralA (Entier (x + y))
                          gg e = error ("addA:gg:Erreur d'analyse syntaxique* : " ++ show e)
             g e = error ("addA:g:Erreur d'analyse syntaxique : " ++ show e)


--Q19
envA :: Environnement ValeurA
envA = [ ("neg",   negA)
       , ("add",   releveBinOpEntierA (+))
       , ("soust", releveBinOpEntierA (-))
       , ("mult",  releveBinOpEntierA (*))
       , ("quot",  releveBinOpEntierA quot) ]

releveBinOpEntierA :: (Integer -> Integer -> Integer) -> ValeurA
releveBinOpEntierA opp = VFonctionA f
       where f (VLitteralA (Entier x)) = VFonctionA g
                    where g (VLitteralA (Entier y)) = VLitteralA (Entier (x `opp` y))
                          g e = error ("envA:g:Erreur d'analyse syntaxique : " ++ show e)
             f e = error ("envA:f:Erreur d'analyse syntaxique : " ++ show e)

--Q20
ifthenelseA :: ValeurA
ifthenelseA = VFonctionA f
            where f (VLitteralA (Bool x)) = VFonctionA g
                    where g (VLitteralA y) = VFonctionA h
                            where h (VLitteralA z) = VLitteralA (if x then y else z)
                                  h e = error ("ifthenelseA:g:Erreur d'analyse syntaxique : " ++ show e)
                          g e = error ("ifthenelseA:g:Erreur d'analyse syntaxique : " ++ show e)
                  f e = error ("ifthenelseA:f:Erreur d'analyse syntaxique : " ++ show e)


main :: IO()
main = do putStr "minilang> "
          cmd <- getLine
          print (interpreteA envA (ras cmd))
          main

{--
========================================
========================================
========================================
========================================
--}


--Q21
data ValeurB = VLitteralB Litteral
             | VFonctionB (ValeurB -> ErrValB)

type MsgErreur = String
type ErrValB   = Either MsgErreur ValeurB

instance Show ValeurB where
    show (VFonctionB _)          = "λ"
    show (VLitteralB (Entier n)) = show n
    show (VLitteralB (Bool n))   = show n


--Q22
interpreteB :: Environnement ValeurB -> Expression -> ErrValB
interpreteB _ (Lit x) = Right (VLitteralB x)
interpreteB env (Lam x y) = Right (VFonctionB (\v -> interpreteB ((x, v):env) y))
interpreteB env (Var x)   = 
  case lookup x env of
    Nothing -> Left ("interpreteB:Var:Erreur d'analyse syntaxique : variable >> " ++ show x ++ " << non définie")
    Just v  -> Right v

interpreteB env (App a b) = 
  case interpreteB env a of
    e@(Left _)           -> e
    Right (VFonctionB f) -> 
      case (interpreteB env b) of
        e@(Left _) -> e
        Right v    -> f v
    Right e              -> Left ("interpreteB:Var:Erreur d'analyse syntaxique : >> " ++ show e ++ " << n'est pas une fonction, application impossible")


--Q23
addB :: ValeurB
addB = VFonctionB g
       where g (VLitteralB (Entier x)) = Right (VFonctionB gg)
                    where gg (VLitteralB (Entier y)) = Right (VLitteralB (Entier (x + y)))
                          gg e = Left ("addB:gg:Erreur d'analyse syntaxique* : >> " ++ show e ++ " << n'est pas un entier*")
             g e = Left ("addB:g:Erreur d'analyse syntaxique : " ++ show e ++ " << n'est pas un entier**")


--Q24
quotB :: ValeurB
quotB = VFonctionB f
       where f (VLitteralB (Entier x)) = Right (VFonctionB g)
                    where g (VLitteralB (Entier 0)) = Left ("quotB:g:Erreur d'analyse syntaxique* : >> division par zero <<")
                          g (VLitteralB (Entier y)) = Right (VLitteralB (Entier (x `quot` y)))
                          g e                       = Left ("quotB:g:Erreur d'analyse syntaxique* : >> " ++ show e ++ " << n'est pas un entier*")
             f e = Left ("quotB:g:Erreur d'analyse syntaxique** : >> " ++ show e ++ " << n'est pas un entier*")




{--
========================================
========================================
            Interprète traçant
========================================
========================================
--}

data ValeurC = VLitteralC Litteral
             | VFonctionC (ValeurC -> OutValC)

type Trace   = String
type OutValC = (Trace, ValeurC)


--Q25
instance Show ValeurC where
    show (VFonctionC _)          = "λ"
    show (VLitteralC (Entier n)) = show n
    show (VLitteralC (Bool n))   = show n


--Q26
interpreteC :: Environnement ValeurC -> Expression -> OutValC
interpreteC _   (Lit n)   = ("", VLitteralC n)
interpreteC env (Var v)   = ("", fromJust (lookup v env))
interpreteC env (Lam x y) = ("", VFonctionC g)
  where   g v = interpreteC ((x,v) : env) y
interpreteC env (App x y) = (t1 ++ t2 ++ "." ++ t,vc)
                where   (t1,VFonctionC f) = interpreteC env x
                        (t2,v)            = interpreteC env y  
                        (t,vc)            = f v


--Q27
pingC :: ValeurC
pingC = VFonctionC (\x -> ("p", x))


{--
========================================
========================================
            Interprète monadique
========================================
========================================
--}


data ValeurM m = VLitteralM Litteral
               | VFonctionM (ValeurM m -> m (ValeurM m))

-- question 28
instance Show (ValeurM m) where
    show (VFonctionM _)          = "λ"
    show (VLitteralM (Entier n)) = show n
    show (VLitteralM (Bool n))   = show n

data SimpleM v = S v
               deriving Show


-- question 29
interpreteSimpleM :: Environnement (ValeurM SimpleM) -> Expression -> SimpleM (ValeurM SimpleM)
interpreteSimpleM _   (Lit x)   = S (VLitteralM x)
interpreteSimpleM env (Var x)   = S (fromJust (lookup x env))
interpreteSimpleM env (Lam x y) = S (VFonctionM (\v -> interpreteSimpleM ((x, v):env) y))
interpreteSimpleM env (App x y) = check_error' (interpreteSimpleM env x) (val (interpreteSimpleM env y))
        where 
              val (S v) = v
              check_error' (S (VFonctionM f)) = f
              check_error' e = error ("interpreteSimpleM:check_error:Erreur d'analyse syntaxique : " ++ show e)


--Q30              
instance Monad SimpleM where
    return      = S
    (S v) >>= f = f v
instance Applicative SimpleM where
    pure  = return
    (<*>) = ap
instance Functor SimpleM where
    fmap  = liftM

--Q31
interpreteM :: Monad m => Environnement (ValeurM m) -> Expression -> m (ValeurM m)
interpreteM _   (Lit x)   = return (VLitteralM x)
interpreteM env (Var x)   = return (fromJust (lookup x env))
interpreteM env (Lam x y) = return (VFonctionM (\v -> interpreteM ((x, v):env) y))
interpreteM env (App x y) = do    
                              app <- interpreteM env x
                              var <- interpreteM env y
                              case app of
                                    (VFonctionM f) -> (f var)
                                    e -> error ("interpreteM:app:Erreur d'analyse syntaxique : " ++ show e)


--Q32
type InterpreteM m = Environnement (ValeurM m) -> Expression -> m (ValeurM m)

interpreteS :: InterpreteM SimpleM
interpreteS = interpreteM

t1 = interpreteS [] (ras "1")
t2 = interpreteS [] (ras "(λx -> x) 1")
t3 = interpreteS [] (ras "(λx -> λy -> x) 1 2")


--Q33
data TraceM v = T (Trace, v)
              deriving Show

instance Monad TraceM where
    return x = T ("", x)
    (T (t, v)) >>= f = T (t ++ tt, y)
                       where (T (tt, y)) = f v
instance Applicative TraceM where
    pure  = return
    (<*>) = ap
instance Functor TraceM where
    fmap  = liftM


interpreteMT :: InterpreteM TraceM
interpreteMT = interpreteM

pingM :: ValeurM TraceM
pingM = VFonctionM (\v -> T ("p", v))


--Q34
interpreteMT' :: InterpreteM TraceM
interpreteMT' env (App e1 e2) =  (interpreteM env e1) >>= \f1
                              -> (interpreteM env e2) >>= \f2
                              -> T (".", f2)          >>= \g
                              -> case g of
                                    (VFonctionM k) -> (k f1)
                                    e -> error ("interpreteM':app:Erreur d'analyse syntaxique : " ++ show e)
interpreteMT' env x         = interpreteMT env x



--Q35
data ErreurM v = Succes v
               | Erreur String
               deriving Show

instance Monad ErreurM where
   return             = Succes
   fail               = Erreur
   (Succes v) >>= f   = f v
   (Erreur e) >>= _   = Erreur e

instance Applicative ErreurM where
   pure  = return
   (<*>) = ap

instance Functor ErreurM where
   fmap  = liftM


--Q36
interpreteE :: InterpreteM ErreurM
interpreteE _ (Lit l)      = return (VLitteralM l)
interpreteE env (Lam n e)  = return (VFonctionM (\v -> interpreteE ((n, v):env) e))
interpreteE env (Var x)    = maybe (fail ("interpreteE:Var:Erreur d'analyse syntaxique : la variable " ++ x ++ " n'est pas défini")) return (lookup x env)
interpreteE env (App e e') = do p  <- interpreteE env e'
                                f  <- interpreteE env e
                                case f of (VFonctionM fct) -> fct p
                                          (VLitteralM l)   -> fail ("interpreteE:App:Erreur d'analyse syntaxique : fonction  >> " ++ show l ++ " <<")



--Q37
class Monad m => Injectable m t where
  injecte :: t -> ValeurM m

instance Monad m => Injectable m Bool where
    injecte = VLitteralM . Bool

instance Monad m => Injectable m Integer where
    injecte = VLitteralM . Entier

instance (Monad m, Injectable m t) => Injectable m (Bool -> t) where
    injecte f = VFonctionM (\ (VLitteralM (Bool b)) -> return (injecte (f b)))

instance (Monad m, Injectable m t) => Injectable m (Integer -> t) where
    injecte f = VFonctionM (\ (VLitteralM (Entier b)) -> return (injecte (f b)))


envM :: Monad m => Environnement (ValeurM m)
envM = [ ("add",   injecte ((+) :: Integer -> Integer -> Integer))
       , ("soust", injecte ((-) :: Integer -> Integer -> Integer))
       , ("mult",  injecte ((*) :: Integer -> Integer -> Integer))
       , ("quot",  injecte (quot :: Integer -> Integer -> Integer))
       , ("et",    injecte (&&))
       , ("ou",    injecte (||))
       , ("non",   injecte not)
       , ("infst", injecte ((<) :: Bool -> Bool -> Bool))]


--Q40
{--
Comme haskell est un langage à évaluation non-stricten, 
on utilise \lazy pour forcer a calculer la valeur directement
--}


-- TESTS
e1=Lit (Entier 12)
e2=Lit (Entier 10)
e3=Lit (Entier 0)

b0=Bool False
b1=Bool True

v1= Var "v1"
v2= Var "v2"