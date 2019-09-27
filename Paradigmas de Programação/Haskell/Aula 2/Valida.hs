module Valida where

ehAnoBissexto :: Integer -> Bool
ehAnoBissexto ano
  | ano `rem` 400 == 0 = True
  | ano `rem` 100 == 0 = False
  | ano `rem`   4 == 0 = True
  | otherwise          = False

valida :: (Integer, Integer, Integer) -> Bool
valida (dia, mes, ano)
    | mes > 12 || mes < 1                             = False
    | dia > 31 || dia < 1                             = False
    | mes == 2 && (not (ehAnoBissexto(ano)))          = dia <= 28
    | mes == 2 && ehAnoBissexto(ano)                  = dia <= 29
    | mes == 4 || mes == 6 || mes == 9 || mes == 11   = dia <= 30
    | otherwise                                       = True