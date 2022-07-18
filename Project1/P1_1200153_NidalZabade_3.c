#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////Bus Struct
struct bus
{
    int BusId;
    int Date;
    char TravelingTime[6];
    char From[15];
    char To[15];
    int TicketPrice;
    int Capacity;
};
typedef struct bus Bus;

////Bus List
struct list1
{
    Bus *b;
    struct list1 *next;
};
typedef struct list1 *BusLL;
typedef struct list1 BusList;

////Student Struct
struct student
{
    int StudentId;
    int Date;
    char TravelingTime[6];
    char From[15];
    char To[15];
};
typedef struct student Student;

////Student List
struct list2
{
    Student *s;
    struct list2 *next;

};
typedef struct list2 *StudentLL;
typedef struct list2 StudentList;

struct list3
{
    Bus *b;
    Student *s;
    struct list3 *next;
};
typedef struct list3 *ConnectionLL;
typedef struct list3 ConnectionList;



////Bus Prototypes

void ReadBuses();

Bus *NewBus(int BusId, int Date, char TravelingTime[5], char From[15], char To[15], int TicketPrice, int Capacity);

BusList *NewBusNode(Bus *b);

BusLL InitiateBusesLinkedList();

void AddBus(BusList *to_append);

void PrintBusInfo(BusList *c);

void PrintBusesLinkedList();

void PrintBus(Bus *c);

void PrintBusesLinkedListForFile();

Bus *PrintBusUsingID(int ID);

void DeleteList3(BusList * L);

BusList * MakeEmpty3(BusList * L);

int IsLast2(BusList * P, BusList * L);

BusList * FindPrevious2(int ID,BusList * L);

int IsEmpty2(BusList * L);


////Students Prototypes

void ReadStudent();

Student *NewStudent(int StudentId, int Date, char TravelingTime[5], char From[15], char To[15]);

StudentList *NewStudentNode(Student *s);

StudentLL InitiateStudentsLinkedList();

void AddStudent(StudentList *to_append);

void PrintStudentLinkedList();

void PrintStudentInfo(StudentList *c);

void PrintStudent(Student *c);

void PrintStudentLinkedListForFile();

void DeleteList2(StudentList * L);

StudentList * MakeEmpty2(StudentList * L);

int IsLast(StudentList * P, StudentList * L);

StudentList * FindPrevious(int ID,StudentList* L);

int IsEmpty1(StudentList * L);


////Connection Prototypes

ConnectionLL InitiateConnectionLinkedList();

void MakeConnections(BusList *r, StudentList *c);

Bus *Matching(BusList *r, StudentList *c);

void AddUnmatchedStudent(StudentList *to_append);

void AddConnection(ConnectionLL to_append);

void PrintMatchingLinkedList();

void PrintUnMatchingLinkedList();

void PrintPassengers(int ID);

void DeleteList(ConnectionList * L);

ConnectionList * MakeEmpty(ConnectionList * L);



////Menu Prototypes

void Menu();

void Delete(int ID);

void Delete2(int ID);


////Global Variables

BusLL Buses;
BusLL ForBusFile;
StudentLL Students;
StudentLL ForStudentFile;
ConnectionLL Connections;
StudentLL UnMatching;


////***************Students Linked List Functions***************//

/*
 * ReadStudent function used to read students(passengers) info [ID,Date,
 * Time,From,To] from passengers.txt and save the info in Students linked list
*/
void ReadStudent()
{
    FILE *StudentFile = fopen("passengers.txt", "r");//open passengers.txt file and set it mode to read only

    //Students info
    int StudentId;
    int Date;
    char TravelingTime[6];
    char From[15];
    char To[15];

    char Line[50];//Line variable to read from the file

    while (fgets(Line, sizeof(Line), StudentFile) != NULL) //read info from file until it has no next line
    {
        if (sscanf(Line, "%d#%d#%[^#]#%[^#]#%[^#\n]", &StudentId, &Date, TravelingTime, From, To) == 5) //check if the number of parameters equal 5
        {

            Student *obj = NewStudent(StudentId, Date, TravelingTime, From, To);//calling NewStudent to creat new Student struct and return it
            struct list2 *v = NewStudentNode(obj);//calling NewStudentNode function to creat student list node and return it
            AddStudent(v);//calling AddStudent to insert and append student list node to StudentList
        }
    }
    fclose(StudentFile);//close passengers.txt file
}

/*
 * NewStudent function is used to creat new struct node student and
 * give it all the student info and return it
 */
Student *NewStudent(int StudentId, int Date, char TravelingTime[5], char From[15], char To[15])
{
    Student *temp = (Student *) malloc(sizeof(Student));//creat new struct node student
    //give the new student node all the info for that student
    temp->StudentId = StudentId;
    temp->Date = Date;
    strcpy(temp->TravelingTime, TravelingTime);
    strcpy(temp->From, From);
    strcpy(temp->To, To);

    return temp;//return student node
}

/*
 * NewStudentNode function used to creat new linked list node for student list
 * by taking the new student and return the student list node
 */
StudentList *NewStudentNode(Student *s)
{
    StudentList *temp = (StudentList *) malloc(sizeof(StudentList));//creat new struct node for student list
    temp->s = s;
    return temp;//return student list node
}

/*
 * InitiateStudentsLinkedList function used to initiate the linked list for
 * student list by creating it head
 */
StudentLL InitiateStudentsLinkedList()
{
    StudentList *header = (StudentLL) malloc(sizeof(StudentList));//creat the head for student list
    header->next = NULL;
    return header;//return head
}

/*
 * AddStudent function is used to append and insert the new student list node
 * to the student list
 * The appending in terms of the student's ID
 */
void AddStudent(StudentList *to_append)
{
    StudentList *current = Students;
    int added = 0;//flag variable
    int i = 0;

    while (current->next)//Make sure that the list has next node [a.k.a. not NULL]
    {
        if ((current->next->s->StudentId) > (to_append->s->StudentId))//To see if the current node has greater ID or not
        {
            //insertion operation to append
            to_append->next = current->next;
            current->next = to_append;
            added = 1;
            break;
        }
        i++;
        current = current->next;
    }
    if (!added)//If there is no place to append the node will be added to the last of the list
    {
        current->next = to_append;
        to_append->next = NULL;
    }
}

/*
 * PrintStudentLinkedList used to print all the student linked list
 * on the screen
 */
void PrintStudentLinkedList()
{
    StudentList *current = Students;//Student linked list we want to print
    printf("\nStudentList:-\n");
    while (current->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        PrintStudentInfo((current->next));//calling PrintStudentInfo to print single node
        current = current->next;
    }
}

/*
 * PrintStudentInfo used to print single student linked list node
 * on the screen
 */
void PrintStudentInfo(StudentList *c)
{
    printf("%d, %d, %s, %s, %s\n", c->s->StudentId, c->s->Date, c->s->TravelingTime, c->s->From, c->s->To);//print student info from the list node
}

/*
 * PrintStudent used to print single student node
 * on the screen
 */
void PrintStudent(Student *c)
{
    printf("%d, %d, %s, %s, %s\n", c->StudentId, c->Date, c->TravelingTime, c->From, c->To);//print student info
}

/*
 * PrintStudentLinkedListForFile used to print all student linked list
 * on passengers.txt
 */
void PrintStudentLinkedListForFile()
{
    StudentList *current = ForStudentFile;
    FILE *StudentFile1 = fopen("passengers.txt", "w+");//open passengers.txt file and set it mode to write
    while (current->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        fprintf(StudentFile1, "%d#%d#%s#%s#%s", current->next->s->StudentId, current->next->s->Date,
                current->next->s->TravelingTime, current->next->s->From, current->next->s->To);//print format
        fprintf(StudentFile1, "\n");//print new line in the file
        current = current->next;//go to the next node
    }
    fclose(StudentFile1);//close passengers.txt file
}

////***************Busses Linked List Functions***************//

/*
 * ReadBuses function used to read busses info [ID,Date,Time,From,
 * To,TicketPrice,Capacity] from busses.txt and save the info
 * in Busses linked list
 */
void ReadBuses()
{
    FILE *BusFile = fopen("busses.txt", "r");//open busses.txt file and set it mode to read only

    //Bus info
    int BusId;
    int Date;
    char TravelingTime[6];
    char From[15];
    char To[15];
    int TicketPrice;
    int Capacity;


    while (fscanf(BusFile, "\n%d#%d#%[^#]#%[^#]#%[^#]#%d#%d", &BusId, &Date, TravelingTime, From, To, &TicketPrice,
                  &Capacity) == 7) //read info from file until it has no next line and check if the number of parameters equal 7
    {
        Bus *obj = NewBus(BusId, Date, TravelingTime, From, To, TicketPrice, Capacity);//calling NewBus to creat new Bus struct and return it
        struct list1 *c = NewBusNode(obj); //calling NewBustNode function to creat bus list node and return it
        AddBus(c); //calling AddBus to insert and append bus list node to BusList
    }
    fclose(BusFile);//close busses.txt file
}

/*
 * NewBus function is used to creat new struct node bus and
 * give it all the bus info and return it
 */
Bus *NewBus(int BusId, int Date, char TravelingTime[5], char From[15], char To[15], int TicketPrice, int Capacity)
{
    Bus *temp = (Bus *) malloc(sizeof(Bus));//creat new struct node bus
    //give the new bus node all the info for that bus
    temp->BusId = BusId;
    temp->Date = Date;
    strcpy(temp->TravelingTime, TravelingTime);
    strcpy(temp->From, From);
    strcpy(temp->To, To);
    temp->TicketPrice = TicketPrice;
    temp->Capacity = Capacity;

    return temp;//return bus node
}

/*
 * NewBusNode function used to creat new linked list node for bus list
 * by taking the new bus and return the bus list node
 */
BusList *NewBusNode(Bus *b)
{
    BusList *temp = (BusList *) malloc(sizeof(BusList));//creat new struct node for bus list
    temp->b = b;
    return temp;//return bus list node
}

/*
 * InitiateBusesLinkedList function used to initiate the linked list for
 * bus list by creating it head
 */
BusLL InitiateBusesLinkedList()
{
    BusList *header = (BusLL) malloc(sizeof(BusList));//creat the head for bus list
    header->next = NULL;
    return header;//return head
}

/*
 * AddBus function is used to append and insert the new bus list node
 * to the bus list
 * The appending in terms of the bus's ID
 */
void AddBus(BusList *to_append)
{
    BusList *current = Buses;
    int added = 0;//flag variable
    int i = 0;

    while (current->next) //Make sure that the list has next node [a.k.a. not NULL]
    {
        if ((current->next->b->BusId) > (to_append->b->BusId)) //To see if the current node has greater ID or not
        {
            //insertion operation to append
            to_append->next = current->next;
            current->next = to_append;
            added = 1;
            break;
        }
        i++;
        current = current->next;
    }

    if (!added) //If there is no place to append the node will be added to the last of the list
    {
        current->next = to_append;
        to_append->next = NULL;
    }
}

/*
 * PrintBusesLinkedList used to print all the bus linked list
 * on the screen
 */
void PrintBusesLinkedList()
{
    BusList *current = Buses;//Bus linked list we want to print
    printf("\nBusList:- \n");
    while (current->next != NULL) //Make sure that the list has next node [a.k.a. not NULL]
    {
        PrintBusInfo((current->next));//calling PrintBusInfo to print single node
        current = current->next;
    }
}

/*
 * PrintBusInfo used to print single bus linked list node
 * on the screen
 */
void PrintBusInfo(BusList *c)
{
    printf("%d, %d, %s, %s, %s, %d, %d\n", c->b->BusId, c->b->Date, c->b->TravelingTime, c->b->From, c->b->To,
           c->b->TicketPrice, c->b->Capacity);//print bus info from the list node
}

/*
 * PrintBus used to print single bus node
 * on the screen
 */
void PrintBus(Bus *c)
{
    printf("%d, %d, %s, %s, %s, %d, %d", c->BusId, c->Date, c->TravelingTime, c->From, c->To,
           c->TicketPrice, c->Capacity);//print student info
}

/*
 * PrintBusesLinkedListForFile used to print all bus linked list
 * on busses.txt
 */
void PrintBusesLinkedListForFile()
{
    BusList *current = ForBusFile;
    FILE *BusFile1 = fopen("busses.txt", "w+");//open busses.txt file and set it mode to write

    while (current->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        fprintf(BusFile1, "%d#%d#%s#%s#%s#%d#%d", current->next->b->BusId, current->next->b->Date,
                current->next->b->TravelingTime, current->next->b->From, current->next->b->To,
                current->next->b->TicketPrice, current->next->b->Capacity);//print format
        fprintf(BusFile1, "\n");//print new line in the file
        current = current->next;//go to the next node
    }
    fclose(BusFile1);//close busses.txt file
}


////***************Connection Linked List Functions***************//


/*
 * InitiateConnectionLinkedList function used to initiate the linked list for
 * connection (bus-student) list by creating it head
 */
ConnectionLL InitiateConnectionLinkedList()
{
    ConnectionList *header = (ConnectionLL) malloc(sizeof(ConnectionList));//creat the head for connection list
    header->next = NULL;
    return header;//return head
}

/*
 * MakeConnections function used to get the connection linked list behave and be capable
 * to organize the students with the busses
 */
void MakeConnections(BusList *r, StudentList *c)
{
    while (c->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        Bus *temp2;//temporary bus
        temp2 = Matching(r, c->next);//calling Matching to see if the student matches any bus from the bus list
        if (temp2 == NULL)//there is matching bus the student or the matching bus is full
        {
            StudentList *temp3 = NewStudentNode(c->next->s);
            AddUnmatchedStudent(temp3);
        } else//there is matching bus for student
        {
            ConnectionList *temp = (ConnectionLL) malloc(sizeof(ConnectionList));//creat new connection node
            temp->s = c->next->s;
            temp->b = temp2;
            AddConnection(temp);//calling AddConnection to insert and append new connection node to connection list
        }
        c = c->next;
    }
}

/*
 * Matching function is used to see which bus is the best for student else
 * there is no matching bus or the matching bus is full
 */
Bus *Matching(BusList *r, StudentList *c)
{
    Bus *temp;//temporary bus
    r = r->next;
    while (r != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        if ((r->b->Date == c->s->Date) && (strcmp(r->b->From, c->s->From) == 0) && (strcmp(r->b->To, c->s->To) == 0))//check if the date, time, to and from for the bus is matching for the student
        {
            int T1 = atoi(r->b->TravelingTime);//bus time
            int T2 = atoi(c->s->TravelingTime);//student time

            int t= T1 - T2;
            if (t>=0)//check matching time
            {
                if (r->b->Capacity > 0)//check the capacity if it is more than 0
                {
                    temp = r->b;
                    r->b->Capacity = r->b->Capacity - 1;
                    return temp;
                } else //there no matching or the bus is full
                {
                    break;
                }
            }
        } else//check next bus
        {
            r = r->next;
        }
    }
    return NULL;//there is no bus is matching the student
}

/*
 * AddConnection function is used to append and insert the new connection list node
 * to the connection list
 * The appending in terms of the student's ID and bus's ID
 */
void AddConnection(ConnectionLL to_append)
{
    ConnectionList *current = Connections;

    int added = 0;//flag variable
    int i = 0;

    while (current->next)//Make sure that the list has next node [a.k.a. not NULL]
    {
        if (((current->b->BusId) > (to_append->b->BusId)) &&
            ((current->next->s->StudentId) > (to_append->s->StudentId))) //To see if the current node has greater ID or not
        {
            //insertion operation to append
            to_append->next = current->next;
            current->next = to_append;
            added = 1;
            break;
        }
        i++;
        current = current->next;
    }
    if (!added) //If there is no place to append the node will be added to the last of the list
    {
        current->next = to_append;
        to_append->next = NULL;
    }
}

/*
 * AddUnmatchedStudent function is used to append and insert the new unmatched student list node
 * to the unmatched student list
 * The appending in terms of the student's ID
 */
void AddUnmatchedStudent(StudentList *to_append)
{
    StudentList *current = UnMatching;

    int added = 0;//flag variable
    int i = 0;

    while (current->next)//Make sure that the list has next node [a.k.a. not NULL]
    {
        if ((current->next->s->StudentId) > (to_append->s->StudentId))//To see if the current node has greater ID or not
        {
            //insertion operation to append
            to_append->next = current->next;
            current->next = to_append;
            added = 1;
            break;
        }
        i++;
        current = current->next;
    }
    if (!added)//If there is no place to append the node will be added to the last of the list
    {
        current->next = to_append;
        to_append->next = NULL;
    }
}

/*
 * PrintMatchingLinkedList used to print all matching list
 * on the screen
 */
void PrintMatchingLinkedList()
{
    ConnectionList *current = Connections;//Matching linked list we want to print
    printf("\nMatching List:-\n");
    while (current->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        printf("\nStudent: ");
        PrintStudent((current->next->s));//calling PrintStudentInfo to print single student
        printf("in Bus: ");
        PrintBus(current->next->b);//calling PrintBusInfo to print single bus
        current = current->next;
    }
}

/*
 * PrintUnMatchingLinkedList used to print all unmatched students linked list
 * on the screen
 */
void PrintUnMatchingLinkedList()
{
    StudentList *current = UnMatching;//Student linked list we want to print
    printf("\n\nUnmatched Student List:-\n");
    while (current->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        PrintStudentInfo((current->next));//calling PrintStudentInfo to print single node
        current = current->next;
    }
}

/*
 * PrintPassengers function used to print passengers' info giving the bus ID
 */
void PrintPassengers(int ID)
{
    ConnectionList *current = Connections;//Matching linked list we want to print
    printf("\nBus:");
    PrintBus(PrintBusUsingID(ID));//calling PrintBus to print bus info and PrintBusUsingID to get the bus we want to print
    printf("\n\nMatching List:-\n");
    while (current->next != NULL)//Matching bus id
    {
        if (current->next->b->BusId == ID)
        {
            printf("\nStudent: ");
            PrintStudent((current->next->s));//calling PrintStudent to print student info
        }
        current = current->next;
    }

}

/*
 * PrintBusUsingID function used to get the bus using the id
 */
Bus *PrintBusUsingID(int ID)
{
    BusList *current = Buses;
    while (current->next != NULL)//Make sure that the list has next node [a.k.a. not NULL]
    {
        if (current->next->b->BusId == ID) //Matching id
        {
            return current->next->b;
        } else
        {
            current = current->next;
        }
    }
    return NULL;//There is no such bus
}

/*
 * MakeEmpty function used to despot empty connection list
 */
ConnectionList * MakeEmpty(ConnectionList * L)
{
    if(L != NULL)//if there is a node
        DeleteList( L );//calling DeleteList to free it
    L = (ConnectionList *)malloc(sizeof(ConnectionList));//new head
    if(L == NULL)//see if there is space in the memory
        printf("Out of memory!\n");
    L->next = NULL;
    return L;//return head
}

/*
 * DeleteList function used to delete connection list node
 */
void DeleteList(ConnectionList * L)
{
    ConnectionList * P;
    ConnectionList * temp;
    P = L->next;
    L->next = NULL;
    while(P != NULL)//if there is a node
    {
        temp = P->next;
        free(P);
        P=temp;
    }
}

/*
 * MakeEmpty2 function used to despot empty student list
 */
StudentList * MakeEmpty2(StudentList * L)
{
    if(L != NULL)//if there is a node
        DeleteList2( L );//calling DeleteList2 to free it
    L = (StudentList *)malloc(sizeof(StudentList));//new head
    if(L == NULL)//see if there is space in the memory
        printf("Out of memory!\n");
    L->next = NULL;
    return L;//return head
}

/*
 * DeleteList function used to delete student list node
 */
void DeleteList2(StudentList * L)
{
    StudentList * P;
    StudentList * temp;
    P = L->next;
    L->next = NULL;
    while(P != NULL)//if there is a node
    {
        temp = P->next;
        free(P);
        P=temp;
    }
}

/*
 * MakeEmpty function used to despot empty bus list
 */
BusList * MakeEmpty3(BusList * L)
{
    if(L != NULL)//if there is a node
        DeleteList3( L );//calling DeleteList3 to free it
    L = (BusList *)malloc(sizeof(BusList));//new head
    if(L == NULL)//see if there is space in the memory
        printf("Out of memory!\n");
    L->next = NULL;
    return L;
}

/*
 * DeleteList3 function used to delete bus list node
 */
void DeleteList3(BusList * L)
{
    BusList * P;
    BusList * temp;
    P = L->next;
    L->next = NULL;
    while(P != NULL)//if there is a node
    {
        temp = P->next;
        free(P);
        P=temp;
    }
}

/*
 * Delete function used to delete student giving his ID
 */
void Delete(int ID)
{
    StudentList *s1=Students;
    StudentList * P;
    StudentList *temp;
    P = FindPrevious(ID, s1);//calling FindPrevious
    if( !IsLast(P, s1) )//check IsLast
    {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }
}

/*
 * FindPrevious function is used to fine the previous to the giving id
 */
StudentList * FindPrevious(int ID,StudentList* L)
{
    StudentList * P;
    P = L;
    while(P->next != NULL && P->next->s->StudentId != ID)//check id
        P = P->next;
    return P;
}

/*
 * IsLast function is used to check if the node is the last or not
 */
int IsLast(StudentList * P, StudentList * L)
{
    return (P->next==NULL);
}

/*
 * Delete2 function used to delete bus giving his ID
 */
void Delete2(int ID)
{
    BusList *b1=Buses;
    BusList * P;
    BusList *temp;
    P = FindPrevious2(ID, b1);//calling FindPrevious2
    if( !IsLast2(P, b1) )//check IsLast
    {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }
}

/*
 * FindPrevious2 function is used to fine the previous to the giving id
 */
BusList * FindPrevious2(int ID,BusList * L)
{
    BusList * P;
    P = L;
    while(P->next != NULL && P->next->b->BusId != ID)//check id
        P = P->next;
    return P;
}

/*
 * IsLast2 function is used to check if the node is the last or not
 */
int IsLast2(BusList * P, BusList * L)
{
    return (P->next==NULL);
}

/*
 * IsEmpty1 function is used to check if the student list is the empty or not
 */
int IsEmpty1(StudentList * L)
{
    return L->next == NULL;
}

/*
 * IsEmpty2 function is used to check if the student list is the empty or not
 */
int IsEmpty2(BusList * L)
{
    return L->next == NULL;
}

/*
 * Menu function used to make the menu
 */
void Menu()
{
    ForBusFile = Buses;
    ForStudentFile = Students;
    ReadBuses();
    ReadStudent();
    int BusID,PassengerID;

    while (1)//continuous loop
    {
        printf("1- Load the bus information file\n");
        printf("2- Load the passenger information file\n");
        printf("3- Assign passengers and print assignment information of all busses\n");
        printf("4- Print specific bus information along with its passengers information\n");
        printf("5- Print unmatched passengers\n");
        printf("6- Add new passenger\n");
        printf("7- Delete passenger\n");
        printf("8- Delete bus number\n");
        printf("9- Print buses list\n");
        printf("10- Print passengers list\n");
        printf("0- Exit\n\n");
        printf("Enter Command Number:-\n");
        int command = 0;
        scanf("%d", &command);

        switch (command)
        {
            case 1:
                PrintBusesLinkedListForFile();
                break;
            case 2:
                PrintStudentLinkedListForFile();
                break;
            case 3:
                MakeConnections(Buses, Students);
                PrintBusesLinkedList();
                printf("\n");
                PrintStudentLinkedList();
                printf("\n");
                PrintMatchingLinkedList();
                printf("\n");
                break;
            case 4:
                printf("Please Enter Bus ID:\n");
                scanf("%d", &BusID);
                PrintPassengers(BusID);
                break;
            case 5:
                PrintUnMatchingLinkedList();
                printf("\n\n");
                break;
            case 6:
                printf("Please enter all the new passenger in form (ID#Date#TravellingTime#From#To)\n");
                int StudentId;
                int Date;
                char TravelingTime[6];
                char From[15];
                char To[15];
                scanf("%d#%d#%[^#]#%[^#]#%[^#\n]", &StudentId, &Date, TravelingTime, From, To);
                Student *obj = NewStudent(StudentId, Date, TravelingTime, From, To);
                struct list2 *v = NewStudentNode(obj);
                AddStudent(v);
                break;
            case 7:
                printf("Please enter passenger ID:\n");
                scanf("%d", &PassengerID);
                MakeEmpty(Connections);
                MakeEmpty2(Students);
                MakeEmpty3(Buses);
                MakeEmpty2(UnMatching);
                ReadBuses();
                ReadStudent();
                Delete(PassengerID);
                MakeConnections(Buses, Students);
                break;
            case 8:
                printf("Please enter Bus ID:\n");
                scanf("%d", &BusID);
                MakeEmpty(Connections);
                MakeEmpty2(Students);
                MakeEmpty3(Buses);
                MakeEmpty2(UnMatching);
                ReadBuses();
                ReadStudent();
                Delete2(BusID);
                MakeConnections(Buses, Students);
                break;
            case 9:
                if(IsEmpty2(Buses))
                {
                    printf("Please load the file first\n");
                }
                else
                {
                    PrintBusesLinkedList();
                    printf("\n\n");
                }
                break;
            case 10:
                if(IsEmpty1(Students))
                {
                    printf("Please load the file first\n");
                }
                else
                {
                    PrintStudentLinkedList();
                    printf("\n\n");
                }
                break;
            case 0:
                exit(0);
            default:
                printf("invalid command number\n");

        }
    }
}
//main function
int main()
{
    //initiate all the heads
    Buses = InitiateBusesLinkedList();
    Students = InitiateStudentsLinkedList();
    UnMatching = InitiateStudentsLinkedList();
    Connections = InitiateConnectionLinkedList();

    Menu();//menu function
    return 0;
}