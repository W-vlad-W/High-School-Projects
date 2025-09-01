class Order:
    def __init__(self, client, offer, active, total_hours):
        
        self.client = client
        self.offer = offer
        self.active = active
        self.total_hours = total_hours
        self.stages = {}
        self.required_technologies = []

    def set_tasks(self, development, testing):
        if development + testing != self.total_hours:
            raise ValueError("The sum of development and testing hours does not match the total project time")
        
        self.stages['development'] = development
        self.stages['testing'] = testing

    def add_required_technologies(self, technologies): 
        if isinstance(technologies, str):
            self.required_technologies.append(technologies)
        elif isinstance(technologies, list):
            self.required_technologies.extend(technologies)
        else:
            raise TypeError("Technologies must be a string or a list of strings")


if __name__ == '__main__':
    # you can do some independent testing here
    pass
