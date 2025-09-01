# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 20 min

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/assignments/homeworks/homework03.md

# Hodnotenie: 1/1b
# super práca, len tak ďalej!

import random
import string

# --------------------
# Úloha 1

# 28. Máme zoznam reťazcov lst. Pomocou list comprehension vygenerujte zoznam lst2,
# ktorý bude obsahovať reťazce zo zoznamu lst s vymazaním prvým písmenom.
lst = [''.join(random.choices(string.ascii_lowercase, k=6)) for _ in range(20)]
print(lst)
lst2 = [strg[1:] for strg in lst]
print(lst2)


# 15. Máme zoznam reťazcov lst. Pomocou list comprehension vygenerujte zoznam lst2,
# ktorý bude obsahovať iba tie prvky zoznamu lst, ktoré obsahujú písmeno o
# ale neobsahujú písmeno u.
lst = [''.join(random.choices(string.ascii_lowercase, k=6)) for _ in range(20)]
print(lst)
lst2 = [strg for strg in lst if 'o' in strg and 'u' not in strg]
print(lst2)


# --------------------
# Úloha 2

# 31. Máme zoznam čísel lst. Upravte zoznam pomocou lambda výrazu tak,
# že z jednotlivých čísel vypočítate ich tretiu mocninu.
lst = [random.randint(1, 1000) for _ in range(20)]
print(lst)
edited_list = list(map(lambda num: num ** 3, lst))
print(edited_list)
