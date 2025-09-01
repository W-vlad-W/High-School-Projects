import csv
from collections import defaultdict
from datetime import datetime, timedelta
import math

def load_line_infos(path):  # 2 points            
    # loads timetables from the specified path and returns them in a dictionary
    # dictionary structure:
    #  - keys are line numbers (as integers)
    #  - each value is a list of tuples describing information on a stop
    #  - for the first stop, the tuple contains the name of the city
    #    and a list of all start times
    #  - start times are tuples with hour and minutes as integers
    #  - for all other stops, the tuple contains the city name
    #    and the number of minutes it takes to get there from the previous stop
    dict = {}
    with open(path, mode="r", encoding="utf-8") as file:
        reader = csv.reader(file, delimiter=';')

        for row in reader:
            if not row or row == ['']:  
                continue
            
            line_number = int(row[0])  
            stops = [] 
            
            first_stop_info = row[1].split(',')
            first_stop_name = first_stop_info[0]
            start_times = [(int(time.split(':')[0]), int(time.split(':')[1])) for time in first_stop_info[1:]]
            stops.append((first_stop_name, start_times))

            for stop_info in row[2:]:
                stop_name, minutes_from_prev = stop_info.split(',')
                stops.append((stop_name, int(minutes_from_prev)))

            dict[line_number] = stops
            
    return dict



def find_next_train(line_infos, line, hour, minute=0):  # 1
    # the function generates the scheduled timetable for the next train
    # on a given line
    # inputs:
    #  - line_infos: dictionary with line information (as loaded by load_line_infos)
    #  - line: the number of the line we are interested in (integer)
    #  - hour: the hour when we start our search (integer)
    #  - minute: the minute when we start our search (integer, by default 0)
    # the function returns a list of tuples where each tuple has two values:
    #  - city name (string)
    #  - a tuple representing the time when the train is scheduled to arrive
    #  - the train stands for a minute at each stop (if it arrives at 10:15,
    #    it leaves at 10:16, if the next stop is 5 minute away, it will arrive
    #    there at 10:21, not 10:20)
    
    if line not in line_infos:
        return []
    
    route_info = line_infos[line] 
    schedule = []

    first_stop, departure_times = route_info[0]  

    next_time = None
    for h, m in departure_times:
        if h > hour or (h == hour and m >= minute):
            next_time = (h, m)
            break

    if next_time is None:
        return [] 
    
    schedule.append((first_stop, next_time))

    current_hour, current_minute = next_time
    for stop_name, travel_time in route_info[1:]:
        current_minute += travel_time

        if current_minute >= 60:
            current_hour += current_minute // 60
            current_minute %= 60
        
        schedule.append((stop_name, (current_hour, current_minute)))

        current_minute += 1

    return schedule


def get_city_timetable(line_infos, city):  # 2
    
    # the function generates the timetable for an arbitrary city
    # for each line with regards to the end station
    # inputs:
    #  - line_infos: dictionary with timetable (as loaded by load_line_infos)
    #  - city: the city for which we want to generate the timetable (string)
    # the function returns a timetable for the given city as a dictionary
    #  - keys are names of possible end stations
    #  - values are lists of departure times as tuples (hour, minute)
    #    regardless of the concrete line that goes there
    
    city_timetable = {}
    departure_times = []
    for line_id, stops_list in line_infos.items():
        station_index = next((i for i, stop in enumerate(stops_list) if stop[0] == city), None)
        if station_index is None:
            continue
        
        first_stop_times = stops_list[0][1]
        
        if station_index == 0:
            departure_times = first_stop_times
        else:
            travel_time = sum(stops_list[i][1] + 1 for i in range(1, station_index + 1))
            for h, m in first_stop_times:
                total_minutes = h * 60 + m + travel_time
                new_h, new_m = divmod(total_minutes, 60)
                departure_times.append((new_h, new_m))

        final_destination = stops_list[-1][0]
        
        if final_destination not in city_timetable:
            city_timetable[final_destination] = []
        
        city_timetable[final_destination].extend(departure_times)

    for destination in city_timetable:
        city_timetable[destination].sort()
    
    return city_timetable

def load_arrival_times(path, line_infos):
    # the function loads real arrival data from a file
    # inputs:
    #  - path: path to a csv file with real arrival and departure times
    #  - line_infos: dictionary with timetable (as loaded by load_line_infos)
    # the function returns a dictionary with the following structure:
    #  - keys are line numbers (integers)
    #  - values are dictionaries:
    #     - keys are scheduled departure times (tuple of two ints)
    #     - values are dictionaries:
    #         - values are dates (string format: YYYY-MM-DD)
    #         - values are lists with tuples
    #           each tuple has four values:
    #            - city name (string - one tuple for each stop)
    #            - scheduled arrival (tuple (hour, minute))
    #            - real arrival (tuple (hour, minute))
    #            - delay in minutes (int - always round down)
    
    # {
    # 12: { 
    #     (6, 30): { 
    #         "2025-02-24": [ 
    #             ("Trnava", (7, 05), (7, 08), 3), 
    #       ("Nitra", (8, 00), (8, 12), 12), 
    #       ("Zvolen", (9, 15), (9, 45), 30) 
    #   ] 
    #     } 
    # } 
    # } 
    
    arrival_data = {}
    
    with open(path, newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        
        for row in reader:
            line_no, city, datetime_str, event_type = row
            line_no = int(line_no)
            event_time = datetime.strptime(datetime_str, "%Y-%m-%d %H:%M:%S")
            date_str = datetime_str.split(" ")[0]  
            
            if line_no not in line_infos or (event_type == 'D' and city != line_infos[line_no][0][0]):
                continue
            
            planned_departures = sorted(line_infos[line_no][0][1])  
            
            planned_departure = None
            for departure in planned_departures:
                if event_time.hour * 60 + event_time.minute >= departure[0] * 60 + departure[1]:
                    planned_departure = departure
            
            if planned_departure is None:
                planned_departure = planned_departures[0] 
            
            if line_no not in arrival_data:
                arrival_data[line_no] = {}
            
            if planned_departure not in arrival_data[line_no]:
                arrival_data[line_no][planned_departure] = {}
            
            if date_str not in arrival_data[line_no][planned_departure]:
                arrival_data[line_no][planned_departure][date_str] = []
            
            stops = line_infos[line_no]
            expected_time = planned_departure
            elapsed_minutes = 0
            i = 0
            for stop in stops:
                stop_city = stop[0]
                if isinstance(stop[1], list):  
                    expected_departure = planned_departure
                    elapsed_minutes = 0 
                else:  
                    if i > 1:
                        elapsed_minutes += stop[1]
                    else:
                        elapsed_minutes += stop[1] + 1  
                    expected_departure = ((planned_departure[0] * 60 + planned_departure[1] + elapsed_minutes) // 60,
                                          (planned_departure[0] * 60 + planned_departure[1] + elapsed_minutes) % 60)
                
                if stop_city == city:
                    actual_time = (event_time.hour, event_time.minute)
                    delay = (actual_time[0] * 60 + actual_time[1]) - (expected_departure[0] * 60 + expected_departure[1])
                    delay = max(0, delay)  
                    arrival_data[line_no][planned_departure][date_str].append((city, expected_departure, actual_time, delay))
                    break  
                i+=1
    
    return arrival_data



def get_most_delayed_line(loaded_arrivals):  # 1
    # finds the line that accrued the most delays on average on the final stop
    # input:
    #  - loaded_arrivals: dictionary with arrival information
    #    (as loaded by load_arrival_times)
    # output:
    #  - tuple of two values:
    #    - line number (int)
    #    - average delay in minutes (float)
    
    max_avg_delay = 0
    most_delayed_line = None

    for line_id, departures in loaded_arrivals.items():
        total_delay = 0
        count = 0

        for schedules in departures.values():
            for stops in schedules.values():
                if stops:
                    last_stop = max(stops, key=lambda stop: stop[1])
                    total_delay += last_stop[3]  
                    count += 1

        if count > 0:
            avg_delay = total_delay / count
            if avg_delay > max_avg_delay:
                max_avg_delay = avg_delay
                most_delayed_line = line_id

    return (most_delayed_line, round(max_avg_delay, 3)) if most_delayed_line is not None else (None, 0.0)

def get_most_delayed_city(loaded_arrivals):  # 1
    # finds the city where trains arrive with the most delay on average
    # input:
    #  - loaded_arrivals: dictionary with arrival information
    #    (as loaded by load_arrival_times)
    # output:
    #  - tuple of two values:
    #    - city name (string)
    #    - average delay in minutes (float)
    city_delays = {}

    for line_data in loaded_arrivals.values():
        for schedules in line_data.values():
            for stops in schedules.values():
                for city, planned_arrival, actual_time, delay in stops:
                    if city not in city_delays:
                        city_delays[city] = [0, 0]  
                    city_delays[city][0] += delay
                    city_delays[city][1] += 1

    most_delayed_city = None
    max_avg_delay = 0

    for city, (total_delay, count) in city_delays.items():
        if count > 0:
            avg_delay = total_delay / count
            if avg_delay > max_avg_delay:
                max_avg_delay = avg_delay
                most_delayed_city = city

    return (most_delayed_city, round(max_avg_delay, 3)) if most_delayed_city else (None, 0.0)


if __name__ == '__main__':
    # test your functions here
    # lines = load_line_infos('timetable.csv')
    # train_finded = find_next_train(lines, 398, 5, 20)
    # print(train_finded)
    # city_timetable = get_city_timetable(lines, "FEA")
    # print(city_timetable)
    
    # arrival_times = load_arrival_times('arrivals.csv', lines)
    # for time, afaf in arrival_times.items():
    #     print(time, ':', afaf, '\n') 
    
    # most_delay_line = get_most_delayed_line(arrival_times)
    # print(most_delay_line)
    
    # most_delay_city = get_most_delayed_city(arrival_times)
    # print(most_delay_city)
    pass
        