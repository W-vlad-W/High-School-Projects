# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework05.md

# Hodnotenie: /1b

# 19
def get_interesting_data(number1, number2):
    
    if not isinstance(number1, int) or not isinstance(number2, int):
        raise TypeError("Both inputs must be integers")
    
    if number1 <= 0 or number2 <= 0:
        raise ValueError("Both numbers must be positive integers")
    
    product = number1 * number2
    
    bigger = max(number1, number2)
    smaller = min(number1, number2)
    
    fraction = bigger / smaller
    return product / fraction
