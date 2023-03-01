from bus import Bus, BusNode, BusList
from student import Student, StudentNode, StudentList

class Trip:
    def __init__(self, bus:Bus, student:Student):
        self.bus = bus
        self.student = student
        
    def get_bus(self):
        return self.bus

    def get_student(self):
        return self.student
    
    def set_bus(self, bus:Bus):
        self.bus = bus
    
    def set_student(self, student:Student):
        self.student = student
        
    def __str__(self) -> str:
        return f"Student {self.student.get_student_id()} is traveling on bus {self.bus.get_bus_id()}"     
class TripNode:
    def __init__(self, trip:Trip):
        self.trip = trip
        self.next = None
        
    def set_trip(self, trip:Trip):
        self.trip = trip
        
    def get_next(self):
        return self.next
    
    def set_next(self, next):
        self.next = next
        
    def get_trip(self):
        return self.trip
    
    def __str__(self) -> str:
        return f"{self.trip}"
    
class TripList:
    def __init__(self):
        self.head = None
        
    def add(self, trip_node:TripNode):
        if self.head == None:
            self.head = trip_node
        else:
            current = self.head
            while current.get_next() != None:
                current = current.get_next()
            current.set_next(trip_node)
            current = current.get_next()
            current.set_next(None)
            
    def get_head(self):
        return self.head
    
    def delete(self, trip_node:TripNode):
        current = self.head
        previous = None
        while current != None:
            if current.get_trip().get_bus().get_bus_id() == trip_node.get_trip().get_bus().get_bus_id() and current.get_trip().get_student().get_student_id() == trip_node.get_trip().get_student().get_student_id():
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
        string = ""
        while current != None:
            string += f"{current}\n"
            current = current.get_next()
        return string
        