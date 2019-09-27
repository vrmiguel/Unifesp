module ExerciciosLista where

headtail :: [Int] -> (Int, Int)
headtail [] = (0, 0)
headtail x = (head x, last x)

meio :: String -> String -- Retorna string sem primeiro e último elemento
meio s = drop 1 (reverse (drop 1 (reverse s)))

k_elemento :: [a] -> Int -> a
k_elemento e n
    | n >= length(e) = last e
    | n < 0 = head e 
    | otherwise = e !! n

pertence :: Eq a => [a] -> a -> Bool -- -- Verifica se um elemento pertence a uma lista
pertence e s = or [True | x <- e, x == s]

insere :: Eq a => a -> [a] -> [a]
insere i e
    | not (pertence e i) = e ++ [i] -- Se i não está na lista, insira-o.
    | otherwise = e -- Se já está, então ignoraremos

palindromo :: Eq a => [a] -> Bool
palindromo s = s == reverse (s)

teste :: IO ()
teste = do
    print (headtail [2..10])
    print (meio "Paradigmas")
    print (k_elemento [2, 3, 4] 2)
    print (k_elemento "paradigmas" 10)
    print (insere 2 [1, 2, 3])
    print (insere 4 [1, 2, 3])
    print (palindromo "arara")