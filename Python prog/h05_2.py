# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework05.md

# Hodnotenie: 1/1b

# 4
def get_smaller_number(number1, number2):
    if not isinstance(number1, (int, float)):
        raise TypeError(f"Invalid input: {number1} is not a number.")
    if not isinstance(number2, (int, float)):
        raise TypeError(f"Invalid input: {number2} is not a number.")

    return min(number1, number2)
