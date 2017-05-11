#!/usr/bin/env stack
-- stack runghc --resolver lts-8.0 --install-ghc

--{-# LANGUAGE TypeApplications #-}

-- http://stackoverflow.com/questions/37505725/standard-queue-package-for-haskell

import Control.Monad -- forM_

getMultipleLines :: Int -> IO [[Int]]
getMultipleLines n = case n of
    0 -> return [] -- ? why [[]] compiles and returns [] as last element
    otherwise -> do          
        ln <- getLine         
        let li = map (read :: String -> Int) $ words ln
        xs <- getMultipleLines (n-1)    
        let ret = (li:xs)    
        return ret          

main = do
    ln <- getLine
    let n = read ln :: Int
    --
    ops <- getMultipleLines n
    forM_ ops printOp
       where printOp = \op -> print $
		case head op of 
		1 -> "push " ++ show (op!!1)
		2 -> "pop"
		3 -> "front"
		otherwise -> error "invalid op"  

-- Following function can be used in any context - no type eror
-- TODO try to create own function
-- error :: forall (r :: RuntimeRep) . forall (a :: TYPE r) . HasCallStack => [Char] -> a

data Queue a = Queue [a] [a] deriving Show
-- front list /1st list/ can be empty only if the back list is also empty
-- The constructor of a newtype must have exactly one field but ‘Queue’ has two

push (Queue outs ins) x = Queue outs (x:ins) 
-- | pop method - remove head from 2nd list/stack, if empty first transfer left stack to right stack
-- >>> pop (Queue [3,2,1] [4] )
-- Queue [2,1] [4] 
-- >>> pop (Queue [3,2,1] [] )
-- Queue [2,1] [] 
-- >>> pop (Queue [] [] )
-- Queue [] []
-- >>> pop (Queue [] [1] )
-- *** Exception: Invariant violation
pop (Queue [] (h:ins)) = error "Invariant violation"
pop (Queue (x:outs) ins) = fixInvariant $ Queue outs ins 
   where 
      fixInvariant (Queue [] ins) = Queue (reverse ins) []
      fixInvariant (Queue outs ins) = Queue outs ins
pop (Queue [] []) = Queue [] []
-- | top method - peek head from 2nd list/stack, if empty first transfel left stack to right stack
-- >>> front (Queue [4] [3,2,1])
-- Just 4
-- >>> front (Queue [3,2,1] [])
-- Just 3
-- >>> front (Queue [] [])
-- Nothing
front (Queue (x:outs) _) = Just x
front (Queue [] []) = Nothing
