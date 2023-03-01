

class Bus:
    def __init__(self, bus_id:int,trip_date:int,departure_time,departure_place,arrival_place,price:int,capacity:int):
        self.bus_id = bus_id
        self.trip_date = trip_date
        self.departure_time = departure_time
        self.departure_place = departure_place
        self.arrival_place = arrival_place
        self.price = price
        self.capacity = capacity
        
    def get_bus_id(self):
        return self.bus_id
    def get_trip_date(self):
        return self.trip_date
    def get_departure_time(self):
        return self.departure_time
    def get_departure_place(self):
        return self.departure_place
    def get_arrival_place(self):
        return self.arrival_place
    def get_price(self):
        return self.price
    def get_capacity(self):
        return self.capacity
    
    def set_bus_id(self, bus_id):
        self.bus_id = bus_id
    def set_trip_date(self, trip_date):
        self.trip_date = trip_date
    def set_departure_time(self, departure_time):
        self.departure_time = departure_time
    def set_departure_place(self, departure_place):
        self.departure_place = departure_place
    def set_arrival_place(self, arrival_place):
        self.arrival_place = arrival_place
    def set_price(self, price):
        self.price = price
    def set_capacity(self, capacity):
        self.capacity = capacity
    
        
    def __str__(self) -> str:
        return f"{self.bus_id} {self.trip_date} {self.departure_time} {self.departure_place} {self.arrival_place} {self.price} {self.capacity}"    
    
class BusNode:
    def __init__(self, bus:Bus):
        self.bus = bus
        self.next = None
        
    def set_bus(self, bus):
        self.bus = bus
    
    def get_next(self):
        return self.next
    
    def set_next(self, next):
        self.next = next
        
    def get_bus(self):
        return self.bus
    
    def __str__(self) -> str:
        return f"{self.bus}"
    


class BusList:
    def __init__(self):
        self.head = None
        
    def add(self, bus_node:BusNode):
        if self.head == None:
            self.head = bus_node
        else:
            current = self.head
            while current.get_next() != None:
                current = current.get_next()
            current.set_next(bus_node)
            current = current.get_next()
            current.set_next(None)
            
    
    def get_head(self):
        return self.head
    
    def get_bus(self, bus_id):
        current = self.head
        while current != None:
            if current.get_bus().get_bus_id() == bus_id:
                return current.get_bus()
            current = current.get_next()
        return None
    
    def delete(self, bus_id:int):
        current = self.head
        previous = None
        while current != None:
            if current.get_bus().get_bus_id() == bus_id:
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
        result = ""
        while current != None:
            result += str(current) + "\n"
            current = current.get_next()
        return result
        
        
        