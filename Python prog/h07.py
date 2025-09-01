# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework07.md

# Hodnotenie: 0,75/1b - abbreviation má byť privátna: __abbreviation

# TODO: add your definition of the class

class Course:
    level: str = "string"

    def __init__(self, name: str, abbreviation: str):
        self.name: str = name
        self.abbreviation: str = abbreviation

    def get_abbreviation(self) -> str:
        return self.abbreviation

    def __eq__(self, other: "Course") -> bool:
        return isinstance(other, Course) and self.name == other.name