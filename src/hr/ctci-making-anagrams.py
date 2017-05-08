from collections import Counter

def number_needed(a, b):
    """
    >>> number_needed("abc", "bcaa")
    1
    """
    multimap_a = Counter(a)
    multimap_a.subtract(Counter(b))
    return sum([abs(c) for c in multimap_a.values()])

if __name__ == "__main__":
    import doctest
    doctest.testmod()

