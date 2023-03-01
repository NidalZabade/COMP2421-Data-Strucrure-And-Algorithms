from bus import Bus, BusNode, BusList
from student import Student, StudentNode, StudentList
from trip import Trip, TripNode, TripList




busList=BusList()
studentList=StudentList()
tripList=TripList()
unmatchedList=StudentList()


def loadBusses():
    with open("busses.txt", "r") as file:
        for line in file:
            line=line.strip()
            info=line.split("#")
            bus_id=int(info[0])
            trip_date=int(info[1])
            departure_time=info[2]
            departure_place=info[3]
            arrival_place=info[4]
            price=int(info[5])
            capacity=int(info[6])
            bus=Bus(bus_id,trip_date,departure_time,departure_place,arrival_place,price,capacity)
            bus_node=BusNode(bus)
            busList.add(bus_node)
            
            
def loadStudents():
    with open("students.txt", "r") as file:
        for line in file:
            line=line.strip()
            info=line.split("#")
            student_id=int(info[0])
            traveling_date=int(info[1])
            traveling_time=info[2]
            departure_place=info[3]
            arrival_place=info[4]
            student=Student(student_id,traveling_date,traveling_time,departure_place,arrival_place)
            student_node=StudentNode(student)
            studentList.add(student_node)
            
def checkTrip(bus:Bus,student:Student):
    tripDate:bool=bus.get_trip_date()==student.get_traveling_date()
    tripTime:bool=False
    tripDeparturePlace:bool=bus.get_departure_place()==student.get_departure_place()
    tripArrivalPlace:bool=bus.get_arrival_place()==student.get_arrival_place()
    
    
    BusDepartureTime=bus.get_departure_time().split(":")
    StudentTravelingTime=student.get_traveling_time().split(":")
    
    busDepartureHour=int(BusDepartureTime[0])
    busDepartureMinute=int(BusDepartureTime[1])
    studentTravelingHour=int(StudentTravelingTime[0])
    studentTravelingMinute=int(StudentTravelingTime[1])
    
    if int(busDepartureHour)==int(studentTravelingHour):
        if int(busDepartureMinute)>=int(studentTravelingMinute):
            tripTime=True
    elif int(busDepartureHour)>int(studentTravelingHour):
        tripTime=True
    
    return tripDeparturePlace and tripArrivalPlace and tripDate and tripTime

def checkCapacity(bus:Bus):
    if bus.get_capacity()>0:
        return True
    else:
        return False
    

        
    

    
            
            
def match():
    current=studentList.get_head()
    while current!=None:
        student=current.get_student()
        currentBus=busList.get_head()
        while currentBus!=None:
            bus=currentBus.get_bus()
            if checkTrip(bus,student) and checkCapacity(bus):
                trip=Trip(bus,student)
                trip_node=TripNode(trip)
                tripList.add(trip_node)
                bus.set_capacity(bus.get_capacity()-1)
                break
            currentBus=currentBus.get_next()
        if currentBus==None:
            unmatchedStudent=StudentNode(student)
            unmatchedList.add(unmatchedStudent)
        current=current.get_next()
        
    

            
        
def printBusInfoWithStudents(bus_id:int):
    studentsInBus:tuple=[]
    print("Bus info: ")
    print(busList.get_bus(bus_id))
    current=tripList.get_head()
    while current!=None:
        if current.get_trip().get_bus().get_bus_id()==bus_id:
            studentsInBus.append(current.get_trip().get_student())
        current=current.get_next()
    print("Students in this bus: ")
    for student in studentsInBus:
        print(student)
        
def addNewStudent():
    student_id=int(input("Enter student id: "))
    traveling_date=int(input("Enter traveling date: "))
    traveling_time=input("Enter traveling time: ")
    departure_place=input("Enter departure place: ")
    arrival_place=input("Enter arrival place: ")
    student=Student(student_id,traveling_date,traveling_time,departure_place,arrival_place)
    student_node=StudentNode(student)
    studentList.add(student_node)
    current=busList.get_head()
    while current!=None:
        bus=current.get_bus()
        if checkTrip(bus,student) and checkCapacity(bus):
            trip=Trip(bus,student)
            trip_node=TripNode(trip)
            tripList.add(trip_node)
            bus.set_capacity(bus.get_capacity()-1)
            break
        else:
            current=current.get_next()
    if current==None:
        unmatchedList.add(student_node)
        
def deleteStudent(student_id:int):
    current=studentList.get_head()
    while current!=None:
        if current.get_student().get_student_id()==student_id:
            studentList.delete(current.get_student().get_student_id())
            break
        current=current.get_next()
    current=tripList.get_head()
    while current!=None:
        if current.get_trip().get_student().get_student_id()==student_id:
            tripList.delete(current)
            current.get_trip().get_bus().set_capacity(current.get_trip().get_bus().get_capacity()+1)
            break
        current=current.get_next()
    current=unmatchedList.get_head()
    while current!=None:
        if current.get_student().get_student_id()==student_id:
            unmatchedList.delete(current.get_student().get_student_id())
            break
        current=current.get_next()
        
def deleteBus(bus_id:int):
    current=busList.get_head()
    while current!=None:
        if current.get_bus().get_bus_id()==bus_id:
            busList.delete(current.get_bus().get_bus_id())
            break
        current=current.get_next()
    current=tripList.get_head()
    while current!=None:
        if current.get_trip().get_bus().get_bus_id()==bus_id:
            unmatchedStudent=StudentNode(current.get_trip().get_student())
            tripList.delete(current)
            unmatchedList.add(unmatchedStudent)
            current=current.get_next()
        else:
            current=current.get_next()
            
            
def PrintToFiles():
    with open("busses.txt","w") as f:
        current=busList.get_head()
        while current!=None:
            bus=current.get_bus()
            f.write(str(bus.get_bus_id())+"#"+str(bus.get_trip_date())+"#"+bus.get_departure_time()+"#"+bus.get_departure_place()+"#"+bus.get_arrival_place()+"#"+str(bus.get_price())+"#"+str(bus.get_capacity()))
        f.close()
    
    with open("students.txt","w") as f:
        current=studentList.get_head()
        while current!=None:
            student=current.get_student()
            f.write(str(student.get_student_id())+"#"+str(student.get_traveling_date())+"#"+student.get_traveling_time()+"#"+student.get_departure_place()+"#"+student.get_arrival_place())
        f.close()
            

def menu():
    print("1. Load busses")
    print("2. Load students")
    print("3. Match students to busses")
    print("4. Print bus info with students")
    print("5. Print unmatched students")
    print("6. Add new student")
    print("7. Delete student")
    print("8. Delete bus")
    print("9. Exit")

def main():
    while True:
        menu()
        try:
            command=int(input("Enter a command: "))
            if command==1:
                loadBusses()
                print("Busses loaded")
                print("Busses: ")
                print(busList)
            elif command==2:
                loadStudents()
                print("Students loaded")
                print("Students: ")
                print(studentList)
            elif command==3:
                match()
                print(tripList)
            elif command==4:
                bus_id=int(input("Enter a bus id: "))
                printBusInfoWithStudents(bus_id)
            elif command==5:
                print(unmatchedList)
            elif command==6:
                addNewStudent()
            elif command==7:
                student_id=int(input("Enter student id: "))
                deleteStudent(student_id)
                print("Student deleted")
                print("Students: ")
                print(studentList)
                print("Trips: ")
                print(tripList)
                print("Unmatched students: ")
                print(unmatchedList)
            elif command==8:
                bus_id=int(input("Enter bus id: "))
                deleteBus(bus_id)
                print("Bus deleted")
                print("Busses: ")
                print(busList)
                print("Trips: ")
                print(tripList)
                print("Unmatched students: ")
                print(unmatchedList)
            elif command==9:
                print("Goodbye")
                break
        except ValueError:
            print("Invalid command")
            continue
        
main()