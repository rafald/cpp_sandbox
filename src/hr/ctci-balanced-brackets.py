def is_matched(expression):
    """
    >>> is_matched("{}{[]}()")
    True
    >>> is_matched("{}{[](})")
    False
    """
    pairs = {'{' : '}', '[' : ']', '(' : ')'}
    sk = []
    for c in expression:
        if c in pairs:
            sk.append(pairs[c])
        elif not sk or c != sk.pop():
            return False
    return not sk
    
if __name__ == "__main__":
    import doctest
    doctest.testmod()
