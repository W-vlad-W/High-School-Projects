CATEGORIES = ["politics", "world", "culture", "tech", "local", "sport"]


class News:
    def __init__(self, category, excitement_rate, validity_length, created):
        self.check_data(category, excitement_rate, validity_length, created)

        self.category = category
        self.excitement_rate = excitement_rate
        self.validity_length = validity_length
        self.created = created

    def check_data(self, category, excitement_rate, validity_length, created):
        
        if not isinstance(category, str):
            raise TypeError("Category must be a string")
        if category not in CATEGORIES:
            raise ValueError(f"Category must be one of: {', '.join(CATEGORIES)}")
        
        if not isinstance(excitement_rate, float):
            raise TypeError("Excitement rate must be a float")
        if not 0 <= excitement_rate <= 1:
            raise ValueError("Excitement rate must be between 0 and 1 (inclusive)")
        
        if not isinstance(validity_length, int):
            raise TypeError("Validity length must be an integer")
        if not 1 <= validity_length <= 10:
            raise ValueError("Validity length must be between 1 and 10 (inclusive)")
        
        if not isinstance(created, int):
            raise TypeError("Created must be an integer")
        if created < 1:
            raise ValueError("Created must be at least 1")

    def get_excitement(self, time_step):
        time_elapsed = float(time_step) - float(self.created)
        
        if time_elapsed > self.validity_length:
            return 0.0

        return self.excitement_rate ** time_elapsed


if __name__ == '__main__':
    # you can test the class here
    pass
