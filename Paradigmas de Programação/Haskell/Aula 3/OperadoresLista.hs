module OperadoresLista where

teste :: IO ()

teste = do
  print (replicate 2 3) -- Replica 3 duas vezes

  print ("Haskell" ++ " " ++ "teste") -- Concatena listas

  print ([2, 3] ++ [4, 4]) -- Concatena listas

  print( [[2, 3]] ++ [[4, 4]] ) -- Concatena

  print( concat ([[2,3], [4,4]])) -- Concatena listas de listas

  print ( head [2, 3, 4] ) -- primeiro elemento
  print ( last [2, 3, 4] ) -- último elemento
  
  print ( init [2, 3, 4] ) -- Todos os elementos menos o último
  print ( tail [2, 3, 4] ) -- Todos os elementos menos o primeiro

  print ( take 20 [1,3 ..] ) -- Pega os primeiros 20 ímpares

  print ( drop 3 [1..10] ) -- Ignora os primeiros 3 naturais até 10

  print ( reverse "Paradigmas de programacao" )

  print ( zip ['1'..'3'] [1..3])

  print ( unzip [('1',1),('2',2),('3',3)] )

  print ( or ( [False] ++ [True | _ <- [1..]] ) )