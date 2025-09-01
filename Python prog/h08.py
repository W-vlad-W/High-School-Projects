# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework08.md

# Hodnotenie: 0,75/1b - Laptop nededí od Computer, inak ale ok


class Computer:
    def __init__(self, brand):
        self.brand = brand

    def start(self):
        return f"{self.brand} Computer starting"

    def shutdown(self):
        return f"{self.brand} Computer shutting down"


# TODO: upravte definíciu tak, aby Laptop bola podtriedou Computer
class Laptop:
    def __init__(self, brand, battery_life):
        # TODO: pridajte volanie konštruktora nadtriedy
        super().__init__(brand)
        self.battery_life = battery_life

    # TODO: prepíšte metódu shutdown tak, aby sa vypísala správa
    # o zapnutí režimu battery saving
    # implementácia nech obsahuje volanie metódy shutdown z nadtriedy
    def shutdown(self):
        # Calling the shutdown method from the parent class (Computer)
        shutdown_message = super().shutdown()
        return f"{shutdown_message}. Entering battery saving mode."


test_brand = "Dell"
test_battery_life = 8
computer = Computer(test_brand)
laptop = Laptop(test_brand, test_battery_life)

# TODO: do komentárov napíšte, z ktorej triedy sa vykonajú implementácie metód
print(computer.start())  # implementácia z triedy Computer
print(computer.shutdown())  # implementácia z triedy Computer
print(laptop.start())  # implementácia z triedy Computer
print(laptop.shutdown())  # implementácia z triedy Laptop