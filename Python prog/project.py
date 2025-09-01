import math
from employee import Manager, Developer, Tester
from order import Order

class Project:
    def __init__(self, company, order, started, employees):
        managers = [emp for emp in employees if isinstance(emp, Manager)]
        if len(managers) != 1:
            raise ValueError("The project should contain exactly one manager")
        
        self.company = company
        self.order = order
        self.started = started
        self.manager = managers[0]
        self.employees = [emp for emp in employees if not isinstance(emp, Manager)]
        
        orig_hours = self.order.total_hours
        if self.manager.level == 'junior':
            self.remaining_hours = math.ceil(orig_hours * 1.2)  
        elif self.manager.level == 'senior':
            self.remaining_hours = math.ceil(orig_hours * 0.8)   
        else:
            self.remaining_hours = orig_hours              
            
        self.manager.curr_project = self
        for emp in self.employees:
            emp.curr_project = self
            
        
    def update(self):
        if self.remaining_hours <= 0:
            return
        
        hours_worked = len(self.employees) * 8
        self.remaining_hours = max(0, self.remaining_hours - hours_worked)

    def is_finished(self):
        return self.remaining_hours <= 0

    def clear_project(self):
        self.finished = True 
        
        self.manager.curr_project = None
        for emp in self.employees:
            emp.curr_project = None
            
        if self in self.company.active_projects:
            self.company.active_projects.remove(self)

        if self not in self.company.finished_projects:
            self.company.finished_projects.append(self)


    def get_income(self):
        base_price = self.order.offer
        income = base_price  

        client_orders = len([p for p in self.company.finished_projects if p.order.client == self.order.client])
        if client_orders >= 3:
            income *= 1.5  

        real_hours = self.order.total_hours
        if self.manager.level == 'junior':
            real_hours = math.ceil(real_hours * 1.2)
        elif self.manager.level == 'senior':
            real_hours = math.ceil(real_hours * 0.8)

        dev_ratio = self.order.stages.get('development', 0) / self.order.total_hours
        test_ratio = self.order.stages.get('testing', 0) / self.order.total_hours

        dev_hours = math.ceil(real_hours * dev_ratio)
        test_hours = math.ceil(real_hours * test_ratio)

        devs = [emp for emp in self.employees if isinstance(emp, Developer)]
        dev_cost = 0
        if devs:
            hours_per_dev = dev_hours / len(devs) 
            dev_cost = sum(emp.wage * math.ceil(hours_per_dev) for emp in devs)

      
        testers = [emp for emp in self.employees if isinstance(emp, Tester)]
        tester_cost = 0
        if testers:
            hours_per_tester = test_hours / len(testers)
            tester_cost = sum(emp.wage * math.ceil(hours_per_tester) for emp in testers)

       
        total_workers = len(self.employees)  
        manager_hours = math.ceil(real_hours / total_workers)
        manager_cost = self.manager.wage * manager_hours

        costs = dev_cost + tester_cost + manager_cost

        return income - costs



if __name__ == '__main__':
    # you can do some independent testing here
    pass
