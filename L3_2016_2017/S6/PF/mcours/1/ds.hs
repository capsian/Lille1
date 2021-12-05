v1 = 'a' : "b"
v2 = 'a' : "abc"
--v3 = 1 : "a" : []
v4 = \x y -> x (x y)
v5 = \x y -> y (y x)
v6 = [id, \x->x+1]



--f1 = 'a'  ++ ('b','c')
f2 = 1 : [1+2]
--f3 = (1,2) : [(1,1),(2,2,2)]
--f4 = [(True,True),(1,1)]
f5 = (\x -> x+1) : []
f6 f = \a b -> f a


enumAX :: (Num a, Ord a)  => a -> a -> [a]
enumAX a b | b >= a =  a : enumAX (a+1) b
				-- | (b-a) == 1 =  []
					 | otherwise = []


enumAX' :: (Num a, Ord a) => a -> a -> [a]
enumAX' a b | a < b = enumAX a b
					  | a >= b  = a : enumAX' (a-1) b



g k [] = []
g k (x:xs) = x k : g k xs

pam' :: a -> [a->b] -> [b]
pam' _ [] = []
pam' k xs = map ((g k) xs)
