from order import Order
from employee import Manager, Tester
import random
import math
from operator import attrgetter
from project import Project

class Scheduler:
    def __init__(self, list_of_orders):
        self.offers = list_of_orders
        self.company = None

    def set_company(self, company):
        self.company = company

    def get_active_offers(self, day_no):
        active = []
        for order in self.offers:
            if not self.company.solving(order):
                if order.active <= day_no <= order.active + 2:
                    active.append(order)
        return active



    def get_new_project(self, day_no):
        if not self.company:
            return None
            
        active_offers = self.get_active_offers(day_no)
        selected_order, employees = self.select_offer(active_offers)
        
        if not selected_order:
            return None
            
        return Project(self.company, selected_order, day_no, employees)

    def select_employees(self, order):
        raise RuntimeError("Method not implemented here")

    def select_offer(self, offers):
        raise RuntimeError("Method not implemented here")


class FirstScheduler(Scheduler):
    def __init__(self, list_of_orders):
        super().__init__(list_of_orders)

    def select_employees(self, order):
        managers = self.company.get_available_employees(Manager)
        if not managers:
            return []
        manager = managers[0]
        
        used_devs = set()
        devs = []
        for tech in order.required_technologies:
            tech_devs = [d for d in self.company.get_lang_developers(tech) 
                        if d not in used_devs]
            if not tech_devs:
                return []
            dev = random.choice(tech_devs)
            used_devs.add(dev)
            devs.append(dev)
        
        testers = []
        if 'testing' in order.stages and order.stages['testing'] > 0:
            available_testers = self.company.get_available_employees(Tester)
            needed_testers = min(math.ceil(order.stages['testing'] / 8), len(available_testers))
            testers = random.sample(available_testers, k=needed_testers) if available_testers else []
        
        return [manager] + devs + testers

    def select_offer(self, offers):
        for order in offers: 
            employees = self.select_employees(order)
            if employees:
                return order, employees 
        return None, None


class RandomScheduler(Scheduler):
    def __init__(self, list_of_orders):
        super().__init__(list_of_orders)

    def select_employees(self, order):
        managers = self.company.get_available_employees(Manager)
        if not managers:
            return []
        manager = random.choice(managers)
        
        used_devs = set()
        devs = []
        for tech in order.required_technologies:
            tech_devs = [d for d in self.company.get_lang_developers(tech) 
                        if d not in used_devs]
            if not tech_devs:
                return []
            dev = random.choice(tech_devs)
            used_devs.add(dev)
            devs.append(dev)
        
        testers = []
        if 'testing' in order.stages and order.stages['testing'] > 0:
            available_testers = self.company.get_available_employees(Tester)
            needed_testers = min(math.ceil(order.stages['testing'] / 8), len(available_testers))
            testers = random.sample(available_testers, k=needed_testers) if available_testers else []
        
        return [manager] + devs + testers

    def select_offer(self, offers):
        eligible = []
        for order in offers:
            employees = self.select_employees(order)
            if employees:
                eligible.append((order, employees))
        
        return random.choice(eligible) if eligible else (None, None)


class GreedyScheduler(Scheduler):
    def __init__(self, list_of_orders):
        super().__init__(list_of_orders)

    def select_employees(self, order):
        managers = self.company.get_available_employees(Manager)
        if not managers:
            return []
        manager = random.choice(managers)
        
        used_devs = set()
        devs = []
        for tech in order.required_technologies:
            tech_devs = [d for d in self.company.get_lang_developers(tech) 
                        if d not in used_devs]
            if not tech_devs:
                return []
            dev = random.choice(tech_devs)
            used_devs.add(dev)
            devs.append(dev)
        
        testers = []
        if 'testing' in order.stages and order.stages['testing'] > 0:
            available_testers = self.company.get_available_employees(Tester)
            needed_testers = min(math.ceil(order.stages['testing'] / 8), len(available_testers))
            testers = random.sample(available_testers, k=needed_testers) if available_testers else []
        
        return [manager] + devs + testers

    def select_offer(self, offers):
        eligible = []
        for order in offers:
            employees = self.select_employees(order)
            if employees:
                eligible.append((order, employees))
        
        if not eligible:
            return None, None
        
        selected = max(eligible, key=lambda x: x[0].offer)
        return selected


class CheapestEmployeeScheduler(Scheduler):
    def __init__(self, list_of_orders):
        super().__init__(list_of_orders)

    def select_employees(self, order):
        managers = sorted(self.company.get_available_employees(Manager), key=attrgetter('wage'))
        if not managers:
            return []
        manager = managers[0] 
        
        devs = []
        used_devs = set()
        for tech in order.required_technologies:
            tech_devs = sorted(
                [d for d in self.company.get_lang_developers(tech) if d not in used_devs],
                key=attrgetter('wage')
            )
            if not tech_devs:
                return []
            dev = tech_devs[0]
            used_devs.add(dev)
            devs.append(dev)
        
        testers = []
        if 'testing' in order.stages and order.stages['testing'] > 0:
            available_testers = sorted(self.company.get_available_employees(Tester), key=attrgetter('wage'))
            needed_testers = min(math.ceil(order.stages['testing'] / 8), len(available_testers))
            testers = available_testers[:needed_testers]
        
        return [manager] + devs + testers
    
    def select_offer(self, offers):
        eligible = []
        for order in offers:
            employees = self.select_employees(order)
            if employees:
                eligible.append((order, employees))
        
        if not eligible:
            return None, None
        
        selected = min(eligible, key=lambda x: sum(emp.wage for emp in x[1]))  
        return selected


if __name__ == '__main__':
    # you can do some independent testing here
    pass
