/// Name: Nidal Zabade     ID: 1200153
/// Project #3
/// Sec: 3

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

//Global Variables
#define MaxNameSize 30
#define DeletedNode (Course *)(0xFFFFFFFFFFFFFFFFUL)

//Course Struct
typedef struct
{
    char CourseName[MaxNameSize];
    int Hours;
    char CourseCode[10];
    char Department[30];
    char Topics[150];
} Course;


/****************************************************** Utility Functions ********************************/

//Function LastPrime takes an integer and return the previous prime
int LastPrime(int x)
{
    int count = 0;

    for (int i = x - 1; i >= 1; i--)//Find the previous number to x
    {
        for (int j = 2; j < i; j++)//Check if the number is prime or not by j: it divisors (the prime number itself and 1)
        {
            if (i % j == 0)//if the number is prime
                count++;
        }
        if (count == 0)
        {
            if (i == 1)//No prime number less than 2
            {
                return 2;
            }
            return i;//return the previous prime number
        }
        count = 0;
    }
    return 0;
}

//Function to Count number of lines in data file
int CountLines()
{
    FILE *fp = fopen("offered_courses.txt", "r");//Pointer for the data file
    int ch;
    int lines = 0;

    if (fp == NULL)
        return 0;
    lines++;
    while ((ch = fgetc(fp)) != EOF)//Check if the file not reach the end (EOF: End Of File)
    {
        if (ch == '\n')
            lines++;//increment the number of lines
    }
    fclose(fp);
    return lines;//return the number of lines
}

//Function LastPrime takes an integer and return the previous prime
int NextPrime(int x)
{
    for (int i = x + 1; i > 0; i++)//Find the next number to x (.e.g x=21 -> i=22)
    {
        int count = 0;
        for (int j = 1; j <= i; j++)//Check if the number is prime or not by j: it divisors (the prime number itself and 1)
        {
            if (i % j == 0)//if the number is prime
                count++;
        }
        if (count == 2)//Number of divisors is 2 (the prime number itself and 1)
        {
            return i;//return the next prime number
        }
    }
}

//Constructor For course
Course *NewCourse(char CourseName[MaxNameSize], int Hours, char CourseCode[10], char Department[30], char Topics[150])
{
    Course *temp;
    temp = malloc(sizeof(Course));
    strcpy(temp->CourseName, CourseName);
    temp->Hours = Hours;
    strcpy(temp->CourseCode, CourseCode);
    strcpy(temp->Department, Department);
    strcpy(temp->Topics, Topics);
    return temp;

}

//Function to Return the hash index
unsigned int Hash(char *CourseName, int HashTableSize)
{
    int length = strnlen(CourseName, MaxNameSize);//Count the size of the string (Name)
    unsigned int HashValue = 0;
    for (int i = 0; i < length; i++)
    {
        HashValue += CourseName[i];//Find the total of ASCII code values for the Course Name
    }
    HashValue = HashValue % HashTableSize;//Calculate the index
    return HashValue;//Return the index value
}

//Function to calculate the load factor
float Load(Course *HashTable[], int HashTableSize)
{
    float Occupied = 0, LoadFactor;
    for (int i = 0; i < HashTableSize; i++)//for loop for all the array
    {
        if (HashTable[i] == NULL || HashTable[i] == DeletedNode)//if the index is empty
        {
            continue;
        } else
        {
            Occupied++;//increment the number of Occupied indexes
        }
    }
    LoadFactor = Occupied / HashTableSize;//the load factor
    return LoadFactor;
}

//Function to print the hash array
void PrintTable(Course *HashTable[], int HashTableSize)
{
    for (int i = 0; i < HashTableSize; i++)//All the array
    {
        if (HashTable[i] == NULL) //Empty node
        {
            printf("\t%i\t----\n", i);

        } else if (HashTable[i] == DeletedNode)//Deleted node
        {
            printf("\t%i\tDeleted\n", i);
        } else//Course
        {
            printf("\t%d\t%s:%d#%s#%s/%s\n", i, HashTable[i]->CourseName, HashTable[i]->Hours, HashTable[i]->CourseCode,
                   HashTable[i]->Department, HashTable[i]->Topics);
        }
    }
}

//Function to print course info
void PrintCourse(Course *c)
{
    printf("%s:%d#%s#%s/%s\n", c->CourseName, c->Hours, c->CourseCode, c->Department, c->Topics);
}


//Function to print the double hash array in the file
void PrintCourseForFile(Course *HashTable[], int HashTableSize)
{
    FILE *SecondFile = fopen("saved_courses.txt", "a");//pointer for the file
    for (int i = 0; i < HashTableSize; i++)
    {
        if (HashTable[i] == NULL)//Empty Node
        {
            continue;
        }
        else if (HashTable[i] == DeletedNode)//Deleted Node
        {
            continue;
        } else //Course
        {
            fprintf(SecondFile, "%s:%d#%s#%s/%s\n", HashTable[i]->CourseName, HashTable[i]->Hours,
                    HashTable[i]->CourseCode, HashTable[i]->Department, HashTable[i]->Topics);
        }
    }
    fclose(SecondFile);
}

/************************************************** Double Hashing Functions ************************************************/

//Function to insert course in the double hashing table
int InsertHashTable(Course *c, Course *HashTable[], int HashTableSize)
{
    int NumberOfCollisions = 0;
    int ArrayIndex;
    if (c == NULL) return 0;//The entered course is Null
    int index = Hash(c->CourseName, HashTableSize);//Return the index from the hash function
    for (int i = 0; i < HashTableSize; i++)//Loop on the table
    {
        ArrayIndex= ((i * (LastPrime(HashTableSize) - (c->CourseName[i] % LastPrime(HashTableSize)))) + index) % HashTableSize;//Double Hashing
        if (HashTable[ArrayIndex] == NULL || HashTable[ArrayIndex] == DeletedNode)//if the place you want to insert to is free
        {
            HashTable[ArrayIndex] = c;//insert the course
            break;
        } else //There is A collision
        {
            NumberOfCollisions++;
        }
    }
    return NumberOfCollisions;//Return the number of Collisions
}

//Function to Delete Course from the double hashing array
Course *DeleteCourse(char *CourseName, Course *HashTable[], int HashTableSize)
{
    int index = Hash(CourseName, HashTableSize);//Return the index from the hash function
    int ArrayIndex;
    for (int i = 0; i < HashTableSize; i++)
    {
        ArrayIndex = ((i * (LastPrime(HashTableSize) - (CourseName[i] % LastPrime(HashTableSize)))) + index) % HashTableSize;//Double Hashing
        if (HashTable[ArrayIndex] == NULL)//The entered course is Null
        {
            return NULL;
        }
        if (HashTable[ArrayIndex] == DeletedNode) continue;//if the place is DeleteNode which mean that collision happened hear
        if (strncmp(HashTable[ArrayIndex]->CourseName, CourseName, HashTableSize) == 0)//if the entered name same as the index name
        {
            Course *temp = HashTable[ArrayIndex];//Save the index in case we need it
            HashTable[ArrayIndex] = DeletedNode;//Replace the Course with DeleteNode
            return temp;

        }
    }
    return NULL;//Not Found
}

//Function to find the Course by name in the double hashing array
Course *Find(char *CourseName, Course *HashTable[], int HashTableSize, int *ptr)
{
    int index = Hash(CourseName, HashTableSize);//Return the index from the hash function
    int ArrayIndex;
    for (int i = 0; i < HashTableSize; i++)//Loop on the table
    {
        ArrayIndex = (index + (i*(LastPrime(HashTableSize) - (CourseName[i] % LastPrime(HashTableSize)))) ) % HashTableSize;//Double Hashing
        if (HashTable[ArrayIndex] == NULL)//The entered course is Null
        {
            return NULL;
        }
        if (HashTable[ArrayIndex] == DeletedNode) continue;//if the place is DeleteNode which mean that collision happened here
        if (strncmp(HashTable[ArrayIndex]->CourseName, CourseName, HashTableSize) == 0)//if the entered name same as the index name
        {
            *ptr = ArrayIndex;//The index number
            return HashTable[ArrayIndex];//Return the course
        }
    }
    return NULL;//Not Found
}


/************************************************** Open Addressing Hashing Functions ************************************************/

//Function to insert course in the open addressing hashing table
int InsertHashTable2(Course *c, Course *HashTable[], int HashTableSize)
{
    int NumberOfCollisions = 0;
    int ArrayIndex;
    if (c == NULL) return 0;//The entered course is Null
    int index = Hash(c->CourseName, HashTableSize);//Return the index from the hash function
    for (int i = 0; i < HashTableSize; i++)//Loop on the table
    {
        ArrayIndex= (i + index) % HashTableSize;//Open Addressing Hashing (Linear)
        if (HashTable[ArrayIndex] == NULL || HashTable[ArrayIndex] == DeletedNode)//if the place you want to insert to is free
        {
            HashTable[ArrayIndex] = c;//insert the course
            break;
        } else//There is A collision
            NumberOfCollisions++;
    }
    return NumberOfCollisions;//Return the number of Collisions
}

//Function to Delete Course from the open addressing array
Course *DeleteCourse2(char *CourseName, Course *HashTable[], int HashTableSize)
{
    int index = Hash(CourseName, HashTableSize);//Return the index from the hash function
    int ArrayIndex;
    for (int i = 0; i < HashTableSize; i++)
    {
        ArrayIndex= (i + index) % HashTableSize;//Open Addressing Hashing (Linear)
        if (HashTable[ArrayIndex] == NULL)//The entered course is Null
        {
            return NULL;
        }
        if (HashTable[ArrayIndex] == DeletedNode) continue;//if the place is DeleteNode which mean that collision happened here
        if (strncmp(HashTable[ArrayIndex]->CourseName, CourseName, HashTableSize) == 0)//if the entered name same as the index name
        {
            Course *temp = HashTable[ArrayIndex];//Save the index in case we need it
            HashTable[ArrayIndex] = DeletedNode;//Replace the Course with DeleteNode
            return temp;

        }
    }
    return NULL;//Not Found
}

//Function to find the Course by name in the open addressing array
Course *Find2(char *CourseName, Course *HashTable[], int HashTableSize, int *ptr)
{
    int index = Hash(CourseName, HashTableSize);//Return the index from the hash function
    int ArrayIndex;
    for (int i = 0; i < HashTableSize; i++)//Loop on the table
    {
        ArrayIndex= (i + index) % HashTableSize;//Open Addressing Hashing (Linear)
        if (HashTable[ArrayIndex] == NULL)
        {
            return NULL;
        }
        if (HashTable[ArrayIndex] == DeletedNode) continue;//The entered course is Null
        if (strncmp(HashTable[ArrayIndex]->CourseName, CourseName, HashTableSize) == 0)//if the entered name same as the index name
        {
            *ptr = ArrayIndex;//The index number
            return HashTable[ArrayIndex];//Return the course
        }
    }
    return NULL;//Not Found
}

/***************************************************** File Reading Functions *********************************************/


void ReadFile(Course *HashTable[],Course *HashTable2[], int HashTableSize, int *TotalCollisions, int *TotalCollisions2)
{
    FILE *CourseFile = fopen("offered_courses.txt", "r");//Pointer at data file

    char CourseName[MaxNameSize];
    int Hours;
    char CourseCode[10];                  //Course Attributes
    char Department[30];
    char Topics[150];

    char Line[250];//Line declaration

    int Num = 0, Num2=0;//intermediate variables

    while (fgets(Line, sizeof(Line), CourseFile) != NULL)//Read until the end of the file
    {
        if (sscanf(Line, "%[^:]:%d#%[^#]#%[^/]/%[^\n]", CourseName, &Hours, CourseCode, Department, Topics))//rescanning the line
        {
            Course *obj = NewCourse(CourseName, Hours, CourseCode, Department, Topics);//Creat course struct
            Num = InsertHashTable(obj, HashTable, HashTableSize);//add the new course to the double hashing array
            TotalCollisions = TotalCollisions + Num;//compute the collisions
            Num2 = InsertHashTable2(obj, HashTable2, HashTableSize);//add the new course to the open addressing hashing array
            TotalCollisions2 = TotalCollisions2 + Num2;//compute the collisions
        }
    }
    fclose(CourseFile);//close the file
}

void Menu()
{
    int NumberOfCollisions, NumberOfCollisions2;
    int NumberOfLines;
    int size;
    float LoadFactor, LoadFactor2;
    int index, index2;
    NumberOfLines = CountLines();//count number of lines in the data file
    size = NextPrime(2 * NumberOfLines);//compute the initial size of the array in terms of data
    Course *HashTable = (Course *) calloc(size, sizeof(Course));//creating an array of courses
    Course *HashTable2 = (Course *) calloc(size, sizeof(Course));//creating an array of courses
    ReadFile(HashTable,HashTable2,size, &NumberOfCollisions, &NumberOfCollisions2);//Read the data file to save data in the arrays

    while (1)//Continuous loop
    {
        //The Menu that the user will interact with
        printf("1- Print hashed tables.\n");
        printf("2- Print out table size and the load factor.\n");
        printf("3- Print out the used hash functions.\n");
        printf("4- Insert a new record.\n");
        printf("5- Search for a specific word.\n");
        printf("6- Delete a specific record.\n");
        printf("7- Compare between the two methods in terms of number of collisions occurred.\n");
        printf("8- Save hash table.\n");
        printf("0- Exit\n\n");
        printf("Enter Command Number:-\n");
        int command = 0;
        scanf("%d", &command);
        //cases
        switch (command)
        {

            case 1://Print hashed tables both open addressing and the double hashing
                printf("Linear Hashing Table:-\n");
                PrintTable(HashTable2, size);//print the open addressing table
                printf("\n");
                printf("Double Hashing Table:-\n");
                PrintTable(HashTable, size);//print the double hashing table
                printf("\n");
                break;
            case 2://Print out table size and the load factor for both open addressing and the double hashing.
                printf("Linear Hashing Table:-\n");
                LoadFactor = Load(HashTable, size);//compute the load factor of open addressing table
                LoadFactor2 = Load(HashTable2, size);//compute the load factor of double hashing table
                printf("Load factor = %f\n", LoadFactor2);
                printf("Size=%d\n", size);
                printf("\n");
                printf("Double Hashing Table:-\n");
                printf("Load factor = %f\n", LoadFactor);
                printf("Size=%d\n", size);
                break;

            case 3://Print out the used hash functions.
                printf("Linear Hashing Table:-\n");
                printf("HashValue += CourseName[i]: Find the total of ASCII code values for the Course Name\nH1= ArrayIndex = HashValue %% HashTableSize: Find the index for the course in the array\nIf collision happened the indexing:-\nArrayIndex = (HashValue + i) %% HashTableSize: The next index in the Array\n\n");
                printf("Double Hashing Table:-\n");
                printf("HashValue += CourseName[i]: Find the total of ASCII code values for the Course Name\nH1= ArrayIndex = HashValue %% HashTableSize: Find the index for the course in the array\nIf collision happened the indexing:-\nH2= ArrayIndex = (HashValue + (i*(LastPrime(HashTableSize) - (CourseName[i] %% LastPrime(HashTableSize)))) ) %% HashTableSize: Using the R- ( HashValue %% R ), where R is a prime smaller than HashTableSize\n\n");
                break;

            case 4://Insert a new record.
                fflush(stdin);
                printf("Please enter all the information for new course in form (CourseName:CreditHours#CourseCode#Department/Topic1,Topic2,...\n");

                char CourseN[MaxNameSize];
                int Hours;
                char CourseC[10];
                char Department[30];
                char Topics[150];

                scanf("%[^:]:%d#%[^#]#%[^/]/%[^\n]", CourseN, &Hours, CourseC, Department, Topics);

                Course *obj = NewCourse(CourseN, Hours, CourseC, Department, Topics);//new course created
                PrintCourse(obj);
                if (Load(HashTable, size)>.75)//checks if the table is 75% full
                {
                    //Rehashing

                    size=NextPrime(2*size);//New size = prime> 2*size

                    HashTable = realloc(HashTable, size * sizeof(Course));//chang the size of the array in terms of the new size
                    HashTable2 = realloc(HashTable2, size * sizeof(Course));//chang the size of the array in terms of the new size

                }

                    NumberOfCollisions += InsertHashTable(obj, HashTable, size);//Collisions
                    NumberOfCollisions2 += InsertHashTable2(obj, HashTable2, size);//Collisions
                    printf("\nAddition Completed");
                    printf("\n\n");
                break;
            case 5://Search for a specific word.
                printf("Enter Course Name\n");
                char Name[MaxNameSize];
                fflush(stdin);
                gets(Name);//read the name
                Course *c1 = Find(Name, HashTable, size, &index);//Search in Double hashing array
                Course *c2 = Find2(Name, HashTable2, size, &index2);//Search in open addressing array
                if (c1==NULL||c2==NULL)//There is no such course
                {
                    printf("There no such Course\n\n");
                }else
                {
                    printf("Location in the Linear Hashing Table in index: %d\n\n", index2);
                    PrintCourse(c1);
                    printf("Location in the Double Hashing Table in index: %d\n\n", index);
                    PrintCourse(c2);
                }
                break;
            case 6://Delete a specific record.
                printf("Enter Course Name\n");
                fflush(stdin);
                char Name2[MaxNameSize];
                gets(Name2);
                Course *cd1= DeleteCourse(Name2, HashTable, size);
                Course *cd2=DeleteCourse2(Name2, HashTable2, size);
                if (cd1==NULL||cd2==NULL)//There is no such course
                {
                    printf("There no such Course\n\n");
                }else
                    printf("Deletion Completed\n\n");
                break;
            case 7://Compare between the two methods in terms of number of collisions occurred.
                printf("Linear Hashing Table:-\n");
                printf("Number of Collisions = %d", NumberOfCollisions2);
                printf("\n\n");
                printf("Double Hashing Table:-\n");
                printf("Number of Collisions = %d", NumberOfCollisions);
                printf("\n\n");
                break;
            case 8://Save hash table.
                fflush(stdin);
                FILE *SecondFile = fopen("saved_courses.txt", "w");
                PrintCourseForFile(HashTable, size);//print the double hashing array in the file
                fclose(SecondFile);
                break;
            case 0://Exit
                exit(0);
            default://default case for invalid command
                printf("invalid command number\n");

        }
    }
}
//Main Function
int main()
{
    Menu();

    return 0;
}