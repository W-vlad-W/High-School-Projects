from population import Population, HomogeneousPopulation
from news import News


def simulate_spread(all_news, population):
    reads_over_time = dict()
    for news in all_news:
        reads_over_time[news] = list()

    time_step = 1
    prev_readers = {}

    for news in all_news:
        news_readers = population.introduce_news(news)
        prev_readers[news] = news_readers

    while len(population.get_active_news()) != 0:
        next_readers = dict()
        for news in all_news:
            reads_over_time[news].append(population.count_readers(news))
            next_readers[news] = []
            for person in prev_readers[news]:
                next_readers[news] += person.process_news(news, time_step)
            next_readers[news] = set(next_readers[news])

        prev_readers = next_readers
        population.update_news(time_step)
        time_step += 1

    return reads_over_time


if __name__ == '__main__':
    news = News("culture", 0.9, 10, 1)
    news2 = News("politics", 0.5, 10, 1)
    news3 = News("tech", 0.99, 10, 1)
    population = Population(1000, 10)

    print(simulate_spread([news, news2], population))
