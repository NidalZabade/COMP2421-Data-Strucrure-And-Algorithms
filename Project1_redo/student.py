


class Student:

    def __init__(self, student_id:int, traveling_date:int,traveling_time,departure_place,arrival_place):
        self.__student_id = student_id
        self.__traveling_date = traveling_date
        self.__traveling_time = traveling_time
        self.__departure_place = departure_place
        self.__arrival_place = arrival_place
        
    def get_student_id(self):
        return self.__student_id
    def get_traveling_date(self):
        return self.__traveling_date
    def get_traveling_time(self):
        return self.__traveling_time
    def get_departure_place(self):
        return self.__departure_place
    def get_arrival_place(self):
        return self.__arrival_place
    
    def set_student_id(self, student_id):
        self.__student_id = student_id
    def set_traveling_date(self, traveling_date):
        self.__traveling_date = traveling_date
    def set_traveling_time(self, traveling_time):
        self.__traveling_time = traveling_time
    def set_departure_place(self, departure_place):
        self.__departure_place = departure_place
    def set_arrival_place(self, arrival_place):
        self.__arrival_place = arrival_place
    
    
    def __str__(self) -> str:
        return f"{self.__student_id} {self.__traveling_date} {self.__traveling_time} {self.__departure_place} {self.__arrival_place}"
        

class StudentNode:
    def __init__(self, student:Student):
        self.student = student
        self.next = None
        
    def set_student(self, student):
        self.student = student
    
    def get_student(self):
        return self.student
    
    def get_next(self):
        return self.next
    
    def set_next(self, next):
        self.next = next
        
    def __str__(self) -> str:
        return f"{self.student}"
    

class StudentList:
    def __init__(self):
        self.head = None
        
    def add(self, student_node:StudentNode):
        if self.head == None:
            self.head = student_node
        else:
            current = self.head
            while current.get_next() != None:
                current = current.get_next()
            current.set_next(student_node)
            current = current.get_next()
            current.set_next(None)

            
    def get_head(self):
        return self.head
    
    def delete(self, student_id:int):
        current = self.head
        previous = None
        while current != None:
            if current.get_student().get_student_id() == student_id:
                if previous == None:
                    self.head = current.get_next()
                else:
                    previous.set_next(current.get_next())
                return
            else:
                previous = current
                current = current.get_next()
                
    
    def __str__(self) -> str:
        current = self.head
        while current != None:
            print(current)
            current = current.get_next()
        return ""
