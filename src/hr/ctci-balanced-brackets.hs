#!/usr/bin/env stack
-- stack runghc --resolver lts-8.0 --install-ghc

import Control.Applicative
import Control.Monad
import System.IO

isBalanced :: String -> Bool
isBalanced expr = reduce expr [] 
  where 
    reduce :: String -> [Char] -> Bool
    reduce (ch:xs) ostack@(o:open) = -- regular case, both inputs not empty: consume ch /can terminate recursion/
       case ch of
       '{' -> reduce xs (ch:ostack)
       '[' -> reduce xs (ch:ostack)
       '(' -> reduce xs (ch:ostack)
       otherwise -> if (scopeBrackets o ch) then reduce xs open else False
    reduce [] stack = null stack -- final step, all input consumed
    reduce (x:xs) [] = reduce xs [x] -- start case or not nested top level scopes
    scopeBrackets :: Char -> Char -> Bool
    scopeBrackets o c = -- query: which pairs constitute a scope
           case (o,c) of 
           ('{','}') -> True
           ('[',']') -> True
           ('(',')') -> True
           otherwise -> False


main :: IO ()
main = do
    t_temp <- getLine
    let t = read t_temp :: Int
    forM_ [1..t] $ \a0  -> do
       expression <- getLine
       putStrLn $ if isBalanced expression then "YES" else "NO"


getMultipleLines :: Int -> IO [String]

getMultipleLines n
    | n <= 0 = return []
    | otherwise = do          
        x <- getLine         
        xs <- getMultipleLines (n-1)    
        let ret = (x:xs)    
        return ret          
