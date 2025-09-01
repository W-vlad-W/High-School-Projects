# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework08.md

# Hodnotenie: 1/1b

class ClassA:
    def __init__(self, value):
        self.value = value

    def foo(self):
        return self.value

    def bar(self):
        return "something"


# TODO: upravte definíciu tak, aby ClassB bola podtriedou ClassA
class ClassB(ClassA):
    def __init__(self, value):
        # TODO: pridajte volanie konštruktora nadtriedy
        super().__init__(value)

    # TODO: prepíšte metódu bar tak, aby vrátila otočenú hodnotu
    # návratovej hodnoty implementácie z nadtriedy
    def bar(self):
        return super().bar()[::-1]


test_value = 25
testA = ClassA(test_value)
testB = ClassB(test_value)

# TODO: do komentárov napíšte, z ktorej triedy sa vykonajú implementácie metód
print(testA.foo())  # implementácia z triedy ClassA
print(testA.bar())  # implementácia z triedy ClassA
print(testB.foo())  # implementácia z triedy ClassA (zdedená)
print(testB.bar())  # implementácia z triedy ClassB (prepísaná)
