# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework06.md

# Hodnotenie: 1/1b
# testovanie na neplatných vstupoch je dosť optimistické, ale v princípe okay

# 11
def get_first_letters(words):
    # Returns a list of the first letters of each word in the input list.
    # Input is a list of strings.
    first_letters = []
    for word in words:
        first_letters.append(word[1])
    return first_letters


def test_get_first_letters():
    assert get_first_letters(["apple", "banana", "cherry"]) == ["a", "b", "c"]
    assert get_first_letters(["Hello", "World"]) == ["H", "W"]
    assert get_first_letters(["a", "b", "c"]) == ["a", "b", "c"]
    assert get_first_letters(["Python", "is", "fun"]) == ["P", "i", "f"]
    assert get_first_letters(["One", "Two", "Three"]) == ["O", "T", "T"]
    assert get_first_letters(["test", "Test", "TEST"]) == ["t", "T", "T"]
    assert get_first_letters(["single"]) == ["s"]
    assert get_first_letters([" ", "abc", "xyz"]) == [" ", "a", "x"]
    assert get_first_letters(["", "word"]) is None  
    assert get_first_letters(["hello", ""]) is None  

    assert get_first_letters([]) == [] 
    assert get_first_letters(["A"]) == ["A"] 
    assert get_first_letters(["a" * 1000, "b" * 2000]) == ["a", "b"]  
    
    
    assert get_first_letters(123) is None
    assert get_first_letters("hello") is None  
    assert get_first_letters(None) is None
    assert get_first_letters([123, "valid", 456]) is None
    assert get_first_letters([[], {}, ()]) is None

test_get_first_letters()
print("All tests passed!")