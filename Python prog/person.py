import random

class Person:
    def __init__(self, threshold, interested_in):
        self.threshold = threshold
        self.interested_in = interested_in
        self.friends_list = list()
        self.has_read = list()

    def is_interested_in(self, category):
        if category in self.interested_in:
            return True
        else:
            return False

    def has_read_news(self, news):
        if news in self.has_read:
            return True
        else:
            return False

    def make_friends(self, population, n):
        potential_friends = [person for person in population if person != self]
        n = min(n, len(potential_friends))
        self.friends_list = random.sample(potential_friends, n)

    def process_news(self, news, time_step): 
        people_to_forward = []
        
        if self.has_read_news(news):
            return people_to_forward
        
        if not self.is_interested_in(news.category):
            return people_to_forward
        
        # if news.get_surprise(time_step) < self.threshold:
        #     return people_to_forward
        
        self.has_read.append(news)
        
        for friend in self.friends_list:
            if friend.is_interested_in(news.category):
                people_to_forward.append(friend)
        
        return people_to_forward 


if __name__ == '__main__':
    # you can test the class here
    pass
