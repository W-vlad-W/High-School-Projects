# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework07.md

# Hodnotenie: 1/1b

# TODO: add your definition of the class

class QuarterBack:
    position_code: int = 1  

    def __init__(self, name: str, team: str):
        self.name: str = name         
        self.__team: str = team        

    def change_name(self, name: str):
        self.name = name

    def get_team(self) -> str:
        return self.__team