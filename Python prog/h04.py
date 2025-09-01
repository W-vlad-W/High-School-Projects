# -*- coding: utf-8 -*-

# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 20min

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework04.md

# Hodnotenie: 1/1b - pre rozptyl sa dá použiť funkcia ptp

import numpy
import pandas

# --------------------
# Úloha 1
# Načítajte dataset uložený v súbore h04.csv ako pandas DataFrame
# a určte pomocou metód pandas dataframe (alebo cez použitie numpy poľa):
#  - najvyššiu váhu pre ženy v datasete

df = pandas.read_csv("h04.csv")
max_weight_female_numpy = numpy.max(df[df["gender"] == "F"]["weight"].values)
print("Max female weight:", max_weight_female_numpy)

# --------------------
# Úloha 2
# V kóde nižšie sa vygeneruje dvojrozmerné numpy pole s náhodnými číselnými
# hodnotami. Vypočítajte:
#  - rozptyl (rozdiel maximálnej a minimálnej hodnoty) po stĺpcoch
array = numpy.random.rand(5, 5)
print(array)

column_range = numpy.max(array, axis=0) - numpy.min(array, axis=0)
print("Column range:", column_range)
