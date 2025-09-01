from employee import Manager, Developer, Tester
from project import Project
from scheduler import Scheduler  
from order import Order

class Company:
    def __init__(self, employees, scheduler):
        self.employees = employees
        self.active_projects = []
        self.finished_projects = []
        self.scheduler = scheduler
        self.scheduler.set_company(self)
        self.day = 0

    def calculate_total_income(self):
       return sum(project.get_income() for project in self.finished_projects)

    def get_available_employees(self, emp_type):
        return [emp for emp in self.employees if isinstance(emp, emp_type) and emp.curr_project is None]

    def get_lang_developers(self, language):
        return [dev for dev in self.employees if isinstance(dev, Developer) and dev.can_program(language) and dev.curr_project is None]
    
    def is_frequent_client(self, client_name):
        client_projects = [p for p in self.finished_projects if p.order.client == client_name]
        return len(client_projects) >= 3

    def close_project(self, project):
        if project in self.active_projects:
            self.active_projects.remove(project)
            self.finished_projects.append(project)
            project.clear_project()

    def solving(self, order):
        all_projects = self.active_projects + self.finished_projects
        return any(p.order == order for p in all_projects)

    def can_solve_order(self, order):
        available_managers = self.get_available_employees(Manager)
        if not available_managers:
            return False
        
        required_techs = order.required_technologies
        available_devs = []
        
        for tech in required_techs:
            tech_devs = self.get_lang_developers(tech)
            if not tech_devs:
                return False
            available_devs.append(tech_devs[0]) 
        
        if len(set(available_devs)) < len(required_techs):
            return False
        
        if 'testing' in order.stages and order.stages['testing'] > 0:
            available_testers = self.get_available_employees(Tester)
            if not available_testers:
                return False
        
        return True

    def simulate_day(self, day_no):
        for project in self.active_projects[:]:
            project.update()  
            if project.is_finished():
                self.close_project(project)  

        while True:
            offers = self.scheduler.get_active_offers(day_no)
            
            order, employees = self.scheduler.select_offer(offers)
            
            if order is None or not self.can_solve_order(order):
                break
            
            manager = self.get_available_employees(Manager)[0]

            devs = []
            for tech in order.required_technologies:
                tech_dev = self.get_lang_developers(tech)[0]  
                devs.append(tech_dev)
            
            testers = []
            if 'testing' in order.stages and order.stages['testing'] > 0:
                testers = [self.get_available_employees(Tester)[0]]  
            
            employees = [manager] + devs + testers
            
            project = Project(self, order, day_no, employees)
            self.active_projects.append(project)


if __name__ == '__main__':
    # you can do some independent testing here
    pass
