module TP1 where

--Q3
sommeDeXaY :: Int -> Int -> Int
sommeDeXaY x y = sum [x..y]

--Q4
somme :: [Int] -> Int
somme [] = 0
somme (x:xs) = x + somme(xs)

--Q5
--last
last_new :: [a] -> a
last_new (x:xs) = head(reverse(xs))
--init
init_new :: [a] -> [a]
init_new a = (take ((length a) - 1) a)

--Q6
-- !!
get :: (Num t, Ord t, Num a, Ord a) => [a] -> t -> a
get [] k = -1
get (x:xs) k = if k > 0 then ( get xs (k-1)) else x
-- ++
(+++) :: [a] -> [a] -> [a]
(+++) [] [] = []
(+++) [] [a] = [a]
(+++) [a1] a2 = a1 : a2 
-- concat
concat_new :: a -> [a] -> [a]
concat_new a [] = [a]
concat_new a l = a:l
-- map
map' :: (a -> b) -> [a] -> [b]
map' f [] = []
map' f (x:xs) = f x : map' f xs

--Q8
-- replace an elem with 1 ( applied with map)
myfunc :: (Num a) => a -> a
myfunc _ = 1

long :: [Int] -> Int
long [] = 0
long l = somme(map' myfunc l)

--Q9
myfunc2 :: (Num a) => a -> a
myfunc2 x = x*2

fn :: (a -> a) -> a -> Int -> [a]
fn f x 0 = [x]
fn f x n = x:(fn f (f x) (n-1))

--Q10
q10 n = [1..n]


