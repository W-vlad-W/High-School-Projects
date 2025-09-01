# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas potrebný na vypracovanie riešenia: 
#10-15 minút
# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/assignments/homeworks/homework02.md

# Hodnotenie: 1/1b
# pekné riešenie

# 12. Napíšte funkciu, ktorá má jeden parameter - kladné celé číslo n
# a vráti sumu (ako integer) druhých mocnín všetkých celých čísel
# od 1 po n (vrátane).

def sum_powered_nums(n: int) -> int: #via loop
    total = 0
    for i in range(1, n + 1):
        total += i ** 2
    return total

def sum_powered_nums2(n: int) -> int: #via formula
    return (n * (n + 1) * (2 * n + 1)) // 6

print(sum_powered_nums(3)) 
print(sum_powered_nums2(3)) 

