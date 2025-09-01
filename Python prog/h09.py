# Meno: Patskan, Vladyslav
# Spolupráca: 
# Použité zdroje: 
# Čas: 10 min

# Podrobný popis je dostupný na: https://github.com/ianmagyar/introduction-to-python/blob/master/homeworks/homework09.md

# Hodnotenie: 1/1b - inštancie nie sú ConcreteSubject, máme len jednu triedu, abstraktný Subject chýba


# Mediator
# Mediator - Mediator
# ConcreteMediator - ChatRoom
# Colleague - Colleague
# ConcreteColleague - Colleague (instances like John, Jane, Alice)

class Mediator:
    def send(self, message, colleague):
        pass

class ChatRoom(Mediator):
    def __init__(self):
        self.colleagues = []

    def add_colleague(self, colleague):
        self.colleagues.append(colleague)

    def send(self, message, colleague):
        for c in self.colleagues:
            if c != colleague:
                c.receive(message)

class Colleague:
    def __init__(self, mediator, name):
        self.mediator = mediator
        self.name = name
        mediator.add_colleague(self)

    def send(self, message):
        print(f"{self.name} sends: {message}")
        self.mediator.send(message, self)

    def receive(self, message):
        print(f"{self.name} receives: {message}")

if __name__ == "__main__":
    chatroom = ChatRoom()

    john = Colleague(chatroom, "John")
    jane = Colleague(chatroom, "Jane")
    alice = Colleague(chatroom, "Alice")

    john.send("Hi everyone!")
    jane.send("Hello John!")
    alice.send("Hey John and Jane!")
