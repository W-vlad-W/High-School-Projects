from config import SENIORITY, WAGES
import math

class Employee:
    def __init__(self, name, level, wage):
        if level not in SENIORITY:
            raise ValueError(f"Unknown seniority level {level}")
        
        self.level = level
        
        if not isinstance(wage, (int, float)):
            raise TypeError(f"Incorrect wage type: {type(wage)}")
        
        min_wage, max_wage = WAGES[level]
        
        if not (min_wage <= wage <= max_wage):
            raise ValueError(f"Incorrect wage for {level} worker: {wage}")
        
        self.name = name 
        self.wage = wage
        self.curr_project = None


class Tester(Employee):
    def __init__(self, name, level, wage):
        super().__init__(name, level, wage)


class Developer(Employee):
    def __init__(self, name, level, wage, languages):
        super().__init__(name, level, wage)
        self.languages = languages

    def can_program(self, language):
        return language in self.languages


class Manager(Employee):
    def __init__(self, name, level, wage):
        super().__init__(name, level, wage)

    def get_project_time(self, orig_time):
        if not isinstance(orig_time, int):
            raise TypeError("Project time must be an integer")
        
        if self.level == 'junior':
            return math.ceil(orig_time * 1.2)
        elif self.level == 'senior':
            return math.ceil(orig_time * 0.8)
        else:
            return orig_time


if __name__ == '__main__':
    # you can do some independent testing here
    pass
