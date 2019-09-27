module Pessoa where

pessoa:: Float -> (String, Float, Char)
pessoa rg
    | rg == 1 = ("Joao Silva", 12, 'm') 
    | rg == 2 = ("Maria Santos", 30, 'f')
    | rg == 3 = ("Jonas Souza", 51, 'm')
    | rg == 4 = ("Silvia Cardoso", 15, 'f')
    | rg == 5 = ("Jose Coelho", 64, 'm')
    | rg == 6 = ("Manoel Pontes", 19, 'm')
    | rg == 7 = ("Joao Carvalho", 13, 'm')
    | rg == 8 = ("Marcia Santana", 37, 'f')
    | rg == 9 = ("Cassia Martinez", 21, 'f')
    | rg == 10 = ("Cassino Silva", 43, 'm')

idade (_, n, _) = n -- Função para obter idade de uma pessoa

sexo (_, _, s) = s -- -- Função para obter o sexo de uma pessoa

idadeMedia :: Float -> Float
idadeMedia n = (sum [idade (pessoa i) | i <- [1.0 .. n] ]) / n

quantHomens :: Float -> Float
quantHomens n = sum [1 | i <- [1.0 .. n], sexo(pessoa i) == 'm']

dadosMaiorIdade :: Float -> (String, Float, Char)
dadosMaiorIdade 0
    | (idade (pessoa 0)) >= 18.0 = pessoa 0
dadosMaiorIdade n
    | (idade (pessoa n)) >= 18.0 = pessoa n
    | otherwise = dadosMaiorIdade (n-1)

dadosMenorIdade :: Float -> (String, Float, Char)
dadosMenorIdade 0
    | (idade (pessoa 0)) < 18.0 = pessoa 0
dadosMenorIdade n
    | (idade (pessoa n)) < 18.0 = pessoa n
    | otherwise = dadosMenorIdade (n-1)