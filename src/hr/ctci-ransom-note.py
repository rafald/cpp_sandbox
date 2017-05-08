#!/usr/bin/env python3 

from collections import Counter 

def ransom_note(magazine, ransom):
	"""
	>>> ransom_note(["give", "me", "one", "grand", "today", "night"], ["give", "one", "grand", "today"])
	True
	>>> ransom_note(["give", "me", "one", "grand", "Today", "night"], ["give", "one", "grand", "today"])
	False
	>>> ransom_note(["give", "me", "one", "grand", "Today", "night"], ["give", "give"])
	False
	>>> ransom_note([], ["give"])
	False
	>>> ransom_note([], [])
	True
	"""
	return not(Counter(ransom) - Counter(magazine))
    
import doctest
doctest.testmod()

if __name__ == "__main__":
	m, n = map(int, input().strip().split(' '))
	magazine = input().strip().split(' ')
	ransom = input().strip().split(' ')
	answer = ransom_note(magazine, ransom)
	if(answer):
		print("Yes")
	else:
		print("No")
