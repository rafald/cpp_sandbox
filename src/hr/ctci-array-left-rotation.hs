#!/usr/bin/env stack
-- stack runghc --resolver lts-8.0 --install-ghc

import Control.Applicative
import Control.Monad
import System.IO


rotate n xs = bs ++ as where (as, bs) = splitAt n xs

main :: IO ()
main = do
    n_temp <- getLine
    let n_t = words n_temp
    let n = read $ n_t!!0 :: Int
    let k = read $ n_t!!1 :: Int
    a_temp <- getLine
    let xsi = map read $ words a_temp :: [Int]
    -- let (,) l1 l2 = splitAt k xsi
    print $ rotate ( mod k n ) xsi

getMultipleLines :: Int -> IO [String]

getMultipleLines n
    | n <= 0 = return []
    | otherwise = do          
        x <- getLine         
        xs <- getMultipleLines (n-1)    
        let ret = (x:xs)    
        return ret  


