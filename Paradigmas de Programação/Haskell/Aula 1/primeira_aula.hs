module Main where

vol :: Int -> Int -- Calcula o volume de um cubo dado o comprimento de seu lado
vol l = l*l*l

potencia_2 :: Int -> Int
potencia_2 x = x*x 
potencia_4 = potencia_2 . potencia_2 

menor :: Int -> Int -> Int
menor x y
    | x < y = x
    | otherwise = y

iguais :: Int -> Int -> Int-> String
iguais x y z 
    | x == y && y == z = "Iguais"
    | (x == y && y /= z) || (x == z && x /= y) || (y == z && y /= x)  = "Dois iguais"
    | otherwise = "Nada iguais"

fatorial :: Integer -> Integer
fatorial 0 = 1
fatorial n = n * fatorial(n-1)

fibonacci :: Integer -> Integer
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n = fibonacci (n-1) + fibonacci (n-2)

combinacoes :: Integer -> Integer -> Integer
combinacoes m n
    | m < n = -1
    | otherwise = fatorial(m) `div` (fatorial(n) * fatorial(m-n))

main = do 
    print(fatorial 8)
    print(iguais 2 3 4)