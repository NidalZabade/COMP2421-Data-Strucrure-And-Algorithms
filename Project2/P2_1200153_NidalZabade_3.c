//Project_2: AVL Tree
//Student Name: Nidal Zabade            Student ID: 1200153

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Course Struct and its prototype
struct course
{
    char CourseName[30];
    int Hours;
    char CourseCode[10];
    char Department[30];
    char Topics[150];
};
typedef struct course Course;

typedef struct AVLnode *AVLNode;

//AVL Tree Struct
struct AVLnode
{
    Course *Element;
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};

void PrintCourse(Course *c) {
    printf("%s:%d#%s#%s/%s\n", c->CourseName,c->Hours,c->CourseCode,c->Department,c->Topics);
}

//Global Variables (Trees)
AVLNode TreeCourseCode;
AVLNode TreeCourseName;

//Function to Make the tree Empty
AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )//If the Tree elements not Empty
    {
        MakeEmpty( T->Left );//Recursive call for nodes in the Left leaf for the tree
        MakeEmpty( T->Right );//Recursive call for nodes in the Right leaf for the tree
        free( T );//Free the Node
    }
    return NULL;//Return empty node
}
//Function to Search for specific Course in the Tree given the Course Code
AVLNode Find( char X[10], AVLNode T )
{
    if( T == NULL )//If the Node is Empty or reach leaf return Null
        return NULL;
    if(strcmp(X, T->Element->CourseCode) < 0 )//To see if the given Code is smaller than node Code in ASCII Code
        return Find( X, T->Left );//Recursive Call to find the node in the left leaf
    else if(strcmp(X, T->Element->CourseCode) > 0)//To see if the given Code is greater than node Code in ASCII Code
        return Find( X, T->Right );//Recursive Call to find the node in the right leaf
    else
        return T;//the node has the same code as the given Code
}
//Function to Find the Minimum value in the Tree for the Course Code Tree
AVLNode FindMin( AVLNode T )
{
    if( T == NULL )//If the Node is Empty or reach leaf return Null
        return NULL;
    else if( T->Left == NULL )//If the Node reaches leaf return The node
        return T;
    else
        return FindMin( T->Left );//Recursive call if the node is not the minimum node
}
//Function to Find the Minimum value in the Tree for the Course Name Tree
AVLNode FindMin2( AVLNode T )
{
    if( T == NULL )//If the Node is Empty or reach leaf return Null
        return NULL;
    else if( T->Left == NULL )//If the Node reaches leaf return The node
        return T;
    else
        return FindMin2( T->Left );//Recursive call if the node is not the minimum node
}
//Function to find the Height of the Tree
int Height( AVLNode P )
{
    if( P == NULL )//If the function reaches leaf or the node is empty
        return -1;
    else
        return P->Height;//Return the height
}
//Function to find the maximum node in the tree
int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}
//Function to do single rotation to the left for the sup tree
AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;
}
//Function to do single rotation to the right for the sup tree
AVLNode SingleRotateWithRight( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;
}

//Function to do Double rotation to the left for the sup tree
AVLNode DoubleRotateWithLeft( AVLNode K3 )
{

    K3->Left = SingleRotateWithRight( K3->Left );


    return SingleRotateWithLeft( K3 );
}
//Function to do Double rotation to the right for the sup tree
AVLNode DoubleRotateWithRight( AVLNode K1 )
{

    K1->Right = SingleRotateWithLeft( K1->Right );

    return SingleRotateWithRight( K1 );
}
//Insertion Function take the course and include it to the tree in terms of the course code
AVLNode Insert( Course *X, AVLNode T )
{
    if( T == NULL )
    {

        T = malloc( sizeof( struct AVLnode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            T->Element=X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if(strcmp(X->CourseCode, T->Element->CourseCode) < 0  )
    {
        T->Left = Insert( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if (strcmp(X->CourseCode, T->Element->CourseCode) < 0)
                T = SingleRotateWithLeft(T);
            else
            {
                T = DoubleRotateWithLeft(T);
            }
    }
    else if( strcmp(X->CourseCode, T->Element->CourseCode) > 0  )
    {
        T->Right = Insert( X, T->Right );
        if(abs(Height( T->Right ) - Height( T->Left )) == 2 )
            if( strcmp(X->CourseCode, T->Right->Element->CourseCode) > 0  )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }


    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
//Insertion Function take the course and include it to the tree in terms of the course Name
AVLNode Insert2( Course *X, AVLNode T )
{
    if( T == NULL )
    {

        T = malloc( sizeof( struct AVLnode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            T->Element=X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if(strcmp(X->CourseName, T->Element->CourseName) < 0  )
    {
        T->Left = Insert2( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if (strcmp(X->CourseName, T->Element->CourseName) < 0)
                T = SingleRotateWithLeft(T);
            else
            {
                T = DoubleRotateWithLeft(T);
            }
    }
    else if( strcmp(X->CourseName, T->Element->CourseName) > 0  )
    {
        T->Right = Insert2( X, T->Right );
        if(abs(Height( T->Right ) - Height( T->Left )) == 2 )
            if( strcmp(X->CourseName, T->Right->Element->CourseName) > 0  )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }


    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
//Print the course information
void PrintCourse(Course *c);
//Print the nodes' information in order way
void PrintInOrder( AVLNode t)
{
    if( t != NULL)//Make sure if the node is empty or not
    {
        PrintInOrder( t->Left );//Recursive call for the left node
        PrintCourse(t->Element);//print course
        PrintInOrder( t->Right );//Recursive call for the right node
    }
}
//Function to delete the node given the course code
AVLNode Delete( char CourseCode[10], AVLNode T )
{
    AVLNode TmpCell;
    if( T == NULL )//if the node is empty or reaches the leaf
        printf( "Element not found\n" );
    else if(strcmp(CourseCode,T->Element->CourseCode)<0)//if the course code is less than the root
        T->Left = Delete( CourseCode, T->Left );//recursive call to delete the node in the left
    else if(strcmp(CourseCode,T->Element->CourseCode)>0 )//if the course code is greater than the root
        T->Right = Delete( CourseCode, T->Right );//recursive call to delete the node in the right
    else
    if( T->Left && T->Right )// Two children

    {
        //Replace with smallest in right subtree
        TmpCell = FindMin( T->Right );
        strcpy(TmpCell->Element->CourseCode,T->Element->CourseCode);
        T->Right = Delete( T->Element->CourseCode, T->Right );
    }
    else// One or zero children
    {
        TmpCell = T;
        if( T->Left == NULL )// Also handles 0 children

            T = T->Right;
        else if( T->Right == NULL )
            T = T->Left;
        free( TmpCell );
    }//end of Delete routine
    return T;
}
//Function to delete the node given the course name
AVLNode Delete2( char Name[30], AVLNode T )
{
    AVLNode TmpCell;
    if( T == NULL )//if the node is empty or reaches the leaf
        printf( "Element not found" );
    else if(strcmp(Name,T->Element->CourseName)<0)//if the course code is less than the root
        T->Left = Delete2( Name, T->Left );//recursive call to delete the node in the left
    else if(strcmp(Name,T->Element->CourseName)>0 )//if the course code is greater than the root
        T->Right = Delete2( Name, T->Right );//recursive call to delete the node in the right
    else
    if( T->Left && T->Right )// Two children

    {
        //Replace with smallest in right subtree
        TmpCell = FindMin2( T->Right );
        strcpy(TmpCell->Element->CourseName,T->Element->CourseName);
        T->Right = Delete2( T->Element->CourseName, T->Right );
    }
    else// One or zero children
    {
        TmpCell = T;
        if( T->Left == NULL )// Also handles 0 children

            T = T->Right;
        else if( T->Right == NULL )
            T = T->Left;
        free( TmpCell );
    }//end of Delete routine
    return T;
}
//Function to creat new course and return it
Course *NewCourse(  char CourseName[30], int Hours, char CourseCode[10], char Department[30], char Topics[150])
{
    Course *temp;
    temp = malloc(sizeof(Course));
    strcpy(temp->CourseName,CourseName);
    temp->Hours=Hours;
    strcpy(temp->CourseCode,CourseCode);
    strcpy(temp->Department,Department);
    strcpy(temp->Topics,Topics);

    return temp;
}
//Function to read data from courses.txt
void ReadFile()
{
    //pointer at data file
    FILE *CourseFile= fopen("courses.txt", "r");
    char CourseName[30];    //
    int Hours;              //
    char CourseCode[10];    // Course Prototypes
    char Department[30];    //
    char Topics[150];       //
    char Line[250];

    while (fgets(Line,sizeof (Line),CourseFile) != NULL)//read until the next line is null (there no more to read)
    {
        if (sscanf(Line,"%[^:]:%d#%[^#]#%[^/]/%[^\n]",CourseName,&Hours,CourseCode,Department,Topics))//see if the prototype is 5
        {
            Course *obj= NewCourse(CourseName,Hours,CourseCode,Department,Topics);//Make new course
            TreeCourseCode= Insert(obj,TreeCourseCode);//Insert the new course to the code tree
        }
    }
    fclose(CourseFile);//Close the file
}
//Function to find the course and update it if the user wants to
void FindAndUpdate()
{
    printf("Enter Course Code\n");
    char Code[30];
    scanf("%s",Code);
    AVLNode A;
    A= Find(Code, TreeCourseCode);//Find function implemented above
    if(A==NULL)
    {
        printf("There no such course\n");
        return;
    } else
    {
        //Cases for update the data of the course
        PrintCourse(A->Element);
        printf("1- Update Course Name\n");
        printf("2- Update Credit Hours\n");
        printf("3- Update Course Code\n");
        printf("4- Update Department\n");
        printf("5- Update Topics\n");
        printf("0- Exit\n");
        int command2=0;
        Course *B;
        printf("Enter Command Number:-\n");
        scanf("%d",&command2);
        switch (command2)
        {
            case 1:
                //Case one to update the course name
                printf("Enter new course name\n");
                char name [30];
                scanf("%s",name);
                strcpy(A->Element->CourseName,name);
                B=A->Element;
                TreeCourseCode= Delete(Code,TreeCourseCode);
                TreeCourseName= Delete(Code,TreeCourseName);
                TreeCourseCode= Insert(B,TreeCourseCode);
                TreeCourseName= Insert2(B,TreeCourseName);
                break;
            case 2:
                //Case two to update the course hours
                printf("Enter new Credit Hours\n");
                int hours;
                scanf("%d",&hours);
                A->Element->Hours=hours;
                B=A->Element;
                TreeCourseCode= Delete(Code,TreeCourseCode);
                TreeCourseCode= Insert(B,TreeCourseCode);
                TreeCourseName= Delete(Code,TreeCourseName);
                TreeCourseName= Insert(B,TreeCourseName);
                break;
            case 3:
                //Case three update the
                printf("Enter new course code\n");
                char Code2 [30];
                scanf("%s",Code2);
                strcpy(A->Element->CourseCode,Code2);
                B=A->Element;
                TreeCourseCode= Delete(Code,TreeCourseCode);
                TreeCourseCode= Insert(B,TreeCourseCode);
                TreeCourseName= Delete(Code,TreeCourseName);
                TreeCourseName= Insert(B,TreeCourseName);
                break;
            case 4:
                printf("Enter new Department name\n");
                char name2 [30];
                scanf("%s",name2);
                strcpy(A->Element->Department,name2);
                B=A->Element;
                TreeCourseCode= Delete(Code,TreeCourseCode);
                TreeCourseCode= Insert(B,TreeCourseCode);
                TreeCourseName= Delete(Code,TreeCourseName);
                TreeCourseName= Insert(B,TreeCourseName);
                break;
            case 5:
                printf("Enter new Topics\n");
                char Topic [30];
                scanf("%s",Topic);
                strcpy(A->Element->Topics,Topic);
                B=A->Element;
                TreeCourseCode= Delete(Code,TreeCourseCode);
                TreeCourseCode= Insert(B,TreeCourseCode);
                TreeCourseName= Delete(Code,TreeCourseName);
                TreeCourseName= Insert(B,TreeCourseName);
                break;
            case 0:
                break;
            default:
                printf("invalid command number\n");
        }

    }
}
//Function to Search for specific Course in the Tree given the Course Name
AVLNode Find2( char X[30], AVLNode T )
{
    if( T == NULL )//If the Node is Empty or reach leaf return Null
        return NULL;
    if(strcmp(X, T->Element->CourseName) < 0 )//To see if the given Name is smaller than node Name in ASCII Code
        return Find2( X, T->Left );//Recursive Call to find the node in the left leaf
    else if(strcmp(X, T->Element->CourseName) > 0)//To see if the given Name is greater than node Name in ASCII Code
        return Find2( X, T->Right );//Recursive Call to find the node in the right leaf
    else
        return T;
}
//Function to read data from courses.txt
void ReadFile2()
{
    //pointer at data file
    FILE *CourseFile= fopen("courses.txt", "r");
    char CourseName[30];    //
    int Hours;              //
    char CourseCode[10];    // Course Prototype
    char Department[30];    //
    char Topics[150];       //
    char Line[250];

    while (fgets(Line,sizeof (Line),CourseFile) != NULL)//read until the next line is null (there no more to read)
    {
        if (sscanf(Line,"%[^:]:%d#%[^#]#%[^/]/%[^\n]",CourseName,&Hours,CourseCode,Department,Topics))//see if the prototype is 5
        {
            Course *obj= NewCourse(CourseName,Hours,CourseCode,Department,Topics);//Make new course
            TreeCourseName= Insert2(obj,TreeCourseName);//Insert the new course to the name tree
        }
    }
    fclose(CourseFile);//Close the file
}
//Function to print course topics
void PrintCourseTopics(Course *c)
{
    printf("Topics: %s\n",c->Topics);
}
//Function to delete the node given the course code
void DeleteCourse(char Code [10], AVLNode T)
{
    AVLNode A;
    A= Find(Code, T);
    if(A==NULL)//if the node is empty or reaches the leaf
    {
        printf("There no such course\n");
        return;
    } else
    {
        TreeCourseCode = Delete(Code, T);//Delete the course
    }
}
//Function to delete the node given the course Name
void DeleteCourse2(char Name [30], AVLNode T)
{
    AVLNode A;
    A= Find2(Name,T);
    if(A==NULL)//if the node is empty or reaches the leaf
    {
        printf("There no such course\n");
        return;
    } else {
        TreeCourseName = Delete2(Name, T);//Delete the course
    }
}
//Function to delete courses with the same first character
AVLNode DeleteCourseWithChar(AVLNode Tree, char k)
{
    // If tree is empty (or reached a leaf in recursion)
    if (Tree == NULL)
    {
        return Tree;
    }

    if (k < Tree->Element->CourseName[0]) // k is smaller than first char of current tree root
    {
        Tree->Left = DeleteCourseWithChar(Tree->Left, k);
    }
    else if (k > Tree -> Element->CourseName[0])// k is greater than first char of current tree root
    {
        Tree->Right = DeleteCourseWithChar(Tree->Right, k);
    }else// equal
    {
        Tree->Left = DeleteCourseWithChar(Tree->Left, k);
        Tree->Right = DeleteCourseWithChar(Tree->Right, k);
        Delete(Tree->Element->CourseCode,TreeCourseCode);
        return Delete2(Tree->Element->CourseName,Tree );//Delete the course
    }
    return Tree;
}
//Function to Print courses with the same department
void PrintSameDepartment(AVLNode Tree, char Department [30])
{
    if( Tree != NULL)//if the node is not empty
    {
        PrintSameDepartment( Tree->Left,Department);//recursive call to print the left nodes
        if(strcmp(Tree->Element->Department,Department)==0) //check if the node has the same department name
        {
            PrintCourse(Tree->Element);//Print course
        }
        PrintSameDepartment( Tree->Right,Department);//recursive call to print the left nodes
    } else
        return;
}
//Function to Delete the courses with the same department from code tree
void DeleteCourseWithDepart(AVLNode Tree, char Department[30])
{
    if( Tree != NULL)//if the node is not empty
    {
        DeleteCourseWithDepart( Tree->Left,Department);//recursive call to delete the left nodes
        if(strcmp(Tree->Element->Department,Department)==0)//check if the node has the same department name
        {
            TreeCourseCode=Delete(Tree->Element->CourseCode,TreeCourseCode);//Delete course
        }
        DeleteCourseWithDepart( Tree->Right,Department);//recursive call to delete the left nodes
    } else
        return;
}
//Function to Delete the courses with the same department from name tree
void DeleteCourseWithDepart2(AVLNode Tree, char Department[30])
{
    if( Tree != NULL)//if the node is not empty
    {
        DeleteCourseWithDepart2( Tree->Left,Department);//recursive call to delete the left nodes
        if(strcmp(Tree->Element->Department,Department)==0) //check if the node has the same department name
        {
            TreeCourseName=Delete2(Tree->Element->CourseName,TreeCourseName);//Delete course
        }
        DeleteCourseWithDepart2( Tree->Right,Department);//recursive call to delete the left nodes
    } else
        return;
}
//Function to print data in the file
void PrintCourseForFile(Course *c)
{
    //pointer for the file
    FILE *SecondFile= fopen("offered_courses.txt","a");
    fprintf(SecondFile,"%s:%d#%s#%s/%s\n", c->CourseName,c->Hours,c->CourseCode,c->Department,c->Topics);
    fclose(SecondFile);
}
//Function to print the tree in order
void PrintFile(AVLNode t)
{
    if( t != NULL)//if the node is not empty
    {
        PrintFile( t->Left );//recursive call to print the left nodes
        PrintCourseForFile(t->Element);//print the node
        PrintFile( t->Right );//recursive call to print the right nodes
    }
}
//Menu Function
void Menu()
{
    while (1)//Continuous loop
    {
        printf("1- Read Information from file.\n");
        printf("2- Insert new course.\n");
        printf("3- Find or Update a course.\n");
        printf("4- List courses in lexicographic order.\n");
        printf("5- List all topics associated with a given course.\n");
        printf("6- List all courses in lexicographic order that belong to the same department.\n");
        printf("7- Delete a course.\n");
        printf("8- Delete all courses that start with a specific letter.\n");
        printf("9- Delete all courses belong to a given department.\n");
        printf("10- Save Data.\n");
        printf("0- Exit\n\n");
        printf("Enter Command Number:-\n");
        int command = 0;
        scanf("%d", &command);
        //cases
        switch (command)
        {
            //case 1 to Read the file courses.txt file and create the tree.
            case 1:
                ReadFile();
                ReadFile2();
                break;
            //case 2 to Insert a new course from the user with all its associated data
            case 2:
                printf("Please enter all the information for new course in form (CourseName:CreditHours#CourseCode#Department/Topic1,Topic2,...\n");
                char CourseName[30];
                int Hours;
                char CourseCode[10];
                char Department[30];
                char Topics[150];
                scanf("%[^:]:%d#%[^#]#%[^/]/%[^\n]", CourseName, &Hours, CourseCode, Department, Topics);
                Course *obj = NewCourse(CourseName, Hours, CourseCode, Department, Topics);
                TreeCourseCode = Insert(obj, TreeCourseCode);
                TreeCourseName = Insert2(obj,TreeCourseName);
                printf("Addition Completed");
                printf("\n");
                break;
            //case 3 to Find a course and support updating of its information
            case 3:
                FindAndUpdate();
                break;
            //case 4 to List courses in lexicographic order with their associated information (credit hours, IDs, and topics).
            case 4:
                printf("Lexicographic order by code:-\n");
                PrintInOrder(TreeCourseCode);
                printf("\nLexicographic order by Name:-\n");
                PrintInOrder(TreeCourseName);
                printf("\n");
                break;
            //case 5 to List all topics associated with a given course.
            case 5:
                printf("Enter Course Code\n");
                char Code[10];
                scanf("%s", Code);
                AVLNode A;
                A = Find(Code, TreeCourseCode);
                if (A == NULL)
                {
                    printf("There no such course\n");
                    break;
                } else
                {
                    PrintCourseTopics(A->Element);
                    printf("\n");
                }
                break;
            //case 6 to     List all courses in lexicographic order that belong to the same department.
            case 6:
                fflush(stdin);
                printf("Enter Department name\n");
                char Dep[30];
                gets(Dep);
                printf("The courses in %s department:-\n", Dep);
                PrintSameDepartment(TreeCourseName,Dep);
                printf("\n");
                break;
            //case 7 to Delete a course.
            case 7:
                printf("Enter Course Code\n");
                char Code2[10];
                scanf("%s",Code2);
                AVLNode a1;
                a1= Find(Code2,TreeCourseCode);
                if (a1==NULL)
                {
                    printf("There no such course\n");
                    break;
                }
                else
                {
                    char Name1 [30];
                    strcpy(Name1, a1->Element->CourseName);
                    DeleteCourse2(Name1,TreeCourseName);
                    DeleteCourse(Code2, TreeCourseCode);
                }
                break;
            //case 8 to Delete all courses that start with a specific letter.
            case 8:
                fflush(stdin);
                printf("Enter Character:-\n");
                char ch;
                scanf(" %c", &ch);
                TreeCourseName= DeleteCourseWithChar(TreeCourseName, ch);
                TreeCourseCode= TreeCourseName;
                break;
            //case 9 to Delete all courses belong to a given department.
            case 9:
                fflush(stdin);
                printf("Enter Department name\n");
                char Dep2[30];
                gets(Dep2);
                DeleteCourseWithDepart(TreeCourseCode,Dep2);
                DeleteCourseWithDepart2(TreeCourseName,Dep2);
                break;
            //case 10 to Save all words in file offered_courses.txt
            case 10:
                fflush(stdin);
                FILE *SecondFile= fopen("offered_courses.txt","w");
                PrintFile(TreeCourseCode);
                fclose(SecondFile);

                break;
            //case 0 to exit
            case 0:
                exit(0);
            //default case for invalid command
            default:
                printf("invalid command number\n");

        }
    }
}
//Main functions
int main()
{
    //initialize trees and make it empty
    TreeCourseCode = MakeEmpty(TreeCourseCode);
    TreeCourseName = MakeEmpty(TreeCourseName);
    Menu();
    return 0;
}