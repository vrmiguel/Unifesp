module Soma where

soma :: (Int, Int) -> Int -> (Int, Int)
soma (x1, x2) x3 = (x1 + x3, x2 + x3)

soma_teste :: (Int, Int) -> IO ()
soma_teste x = do
    print(x)
    print(soma x 2)