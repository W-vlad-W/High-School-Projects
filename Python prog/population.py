import random
from person import Person
from news import CATEGORIES
allowed_categories = CATEGORIES


class Population:
    def __init__(self, n, friends_count):
        self.people = list()
        self.active_news = list()

        self.generate_population(n, friends_count)

    def generate_population(self, n, friends_count):
        allowed_categories = CATEGORIES
        for _ in range(n):
            threshold = random.random()
            
            interested_in = random.sample(allowed_categories, 4)
            
            self.people.append(Person(threshold, interested_in))
        
        for person in self.people:
            person.make_friends(self.people, friends_count)

    def introduce_news(self, news):
        self.active_news.append(news)
        
        interested_people = [person for person in self.people 
                           if person.is_interested_in(news.category)]
        
        first_recipients = random.sample(interested_people, min(5, len(interested_people)))
        return first_recipients

    def update_news(self, time_step):
        self.active_news = [news for news in self.active_news 
                           if news.get_surprise_factor(time_step) > 0]

    def count_readers(self, news):
        return sum(1 for person in self.people if person.has_read_news(news))

    def get_number_of_interested(self, category):
        return sum(1 for person in self.people if person.is_interested_in(category))


class HomogeneousPopulation(Population):
    def __init__(self, n, friends_count, category):
        self.category = category
        super().__init__(n, friends_count)

    def generate_population(self, n, friends_count):
        for _ in range(n):
            threshold = random.random()
            interested_in = [self.category]
            person = Person(threshold, interested_in)
            self.people.append(person)
        
        for person in self.people:
            person.make_friends(self.people, friends_count)


if __name__ == '__main__':
    # you can test the class here
    pass
