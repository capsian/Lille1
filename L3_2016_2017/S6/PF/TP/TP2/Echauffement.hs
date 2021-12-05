module Echauffement where

alterne :: [t] -> [t]
alterne [] = []
alterne (x:_:y:z) = x : alterne(y:z)
alterne (x:_) = [x]

combine :: (a -> b -> c) -> [a] -> [b] -> [c]
combine f [] (y:ys) = []
combine f (x:xs) [] = []
combine f (x:xs) (y:ys) = f x y : combine f xs ys
