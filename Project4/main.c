#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//Number of cities in the graph
#define NumberOfCities 15
#define INF 9999

//Function Translate takes an array of char (City name) and return the index of the city in the Graph
int Translate(char City[30])
{
    if (strcmp(City, "Akka") == 0)//if the city is Akka
        return 0;//return value 0
    else if (strcmp(City, "Bethlehem") == 0)//if the city is Bethlehem
        return 1;//return value 1
    else if (strcmp(City, "Haifa") == 0)//if the city is Haifa
        return 2;//return value 2
    else if (strcmp(City, "Hebron") == 0)//if the city is Hebron
        return 3;//return value 3
    else if (strcmp(City, "Jenin") == 0)//if the city is Jenin
        return 4;//return value 4
    else if (strcmp(City, "Jericho") == 0)//if the city is Jericho
        return 5;//return value 5
    else if (strcmp(City, "Jerusalem") == 0)//if the city is Jerusalem
        return 6;//return value 6
    else if (strcmp(City, "Nablus") == 0)//if the city is Nablus
        return 7;//return value 7
    else if (strcmp(City, "Nazareth") == 0)//if the city is Nazareth
        return 8;//return value 8
    else if (strcmp(City, "Qalqilya") == 0)//if the city is Qalqilya
        return 9;//return value 9
    else if (strcmp(City, "Ramallah") == 0)//if the city is Ramallah
        return 10;//return value 10
    else if (strcmp(City, "Salfit") == 0)//if the city is Salfit
        return 11;//return value 11
    else if (strcmp(City, "Tubas") == 0)//if the city is Tubas
        return 12;//return value 12
    else if (strcmp(City, "Tulkarem") == 0)//if the city is Tulkarem
        return 13;//return value 13
    else if (strcmp(City, "Yafa") == 0)//if the city is Yafa
        return 14;//return value 14
    else//if there is no such city
        return 999;//return value 999

}

//Function Translate takes an index of the city in the Graph and return array of char (City name)
char *TranslateBack(int City)
{
    if (City == 0)//if the index of array is 0
        return "Akka";//return Akka
    if (City == 1)//if the index of array is 1
        return "Bethlehem";//return Bethlehem
    if (City == 2)//if the index of array is 2
        return "Haifa";//return Haifa
    if (City == 3)//if the index of array is 3
        return "Hebron";//return Hebron
    if (City == 4)//if the index of array is 4
        return "Jenin";//return Jenin
    if (City == 5)//if the index of array is 5
        return "Jericho";//return Jericho
    if (City == 6)//if the index of array is 6
        return "Jerusalem";//return Jerusalem
    if (City == 7)//if the index of array is 7
        return "Nablus";//return Nablus
    if (City == 8)//if the index of array is 8
        return "Nazareth";//return Nazareth
    if (City == 9)//if the index of array is 9
        return "Qalqilya";//return Qalqilya
    if (City == 10)//if the index of array is 10
        return "Ramallah";//return Ramallah
    if (City == 11)//if the index of array is 11
        return "Salfit";//return Salfit
    if (City == 12)//if the index of array is 12
        return "Tubas";//return Tubas
    if (City == 13)//if the index of array is 13
        return "Tulkarem";//return Tulkarem
    if (City == 14)//if the index of array is 14
        return "Yafa";//return Yafa
    return "No";//if the there is no such index in the array return "No" (No such city)
}

//Function Dijkstra used to find the shortest path from a city (source) to another city (destination).
void Dijkstra(int Graph[NumberOfCities][NumberOfCities], int n, int Source, int Destination, int command)
{

    int TotalCost[NumberOfCities][NumberOfCities]/*Total cost between two cities*/, Weight[NumberOfCities]/*The shortest path array*/, Predecessor[NumberOfCities]/*The previous city*/;
    int Visited[NumberOfCities]/*The visited cities*/, Counter/*Number of visited cities*/, MinimumWeight, NextCity, i, j;
    //for loop to fill and initialized the TotalCost array
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (Graph[i][j] == 0)//if there is no distance between two cities save TotalCost[i][j] as INFINITY = 9999
                TotalCost[i][j] = INF;
            else//if there is distance between two cities save TotalCost[i][j] as Graph[i][j] which is distance
                TotalCost[i][j] = Graph[i][j];
    //for loop initialize the Weight, Predecessor, Visited
    for (i = 0; i < n; i++)
    {
        Weight[i] = TotalCost[Source][i];
        Predecessor[i] = Source;
        Visited[i] = 0;
    }
    Weight[Source] = 0;
    Visited[Source] = 1;
    Counter = 1;

    while (Counter < n - 1)
    {
        MinimumWeight = INF;
        //Find the city with the minimal distance.
        for (i = 0; i < n; i++)
        {
            if (Weight[i] < MinimumWeight && !Visited[i])//if the new weight is less than the current weight and not visited (new city)
            {
                //Update the distance of the neighbor city
                MinimumWeight = Weight[i];
                NextCity = i;
            }
        }
        //check if a better path exists through next city
        Visited[NextCity] = 1;
        for (i = 0; i < n; i++)
            if (!Visited[i])
            {
                if (MinimumWeight + TotalCost[NextCity][i] < Weight[i])
                {
                    Weight[i] = MinimumWeight + TotalCost[NextCity][i];
                    Predecessor[i] = NextCity;
                }

            }
        Counter++;
    }
    //Print result depend on the command
    for (i = 0; i < n; i++)
    {
        if (i != Source)
        {
            if (command == 2)//print the total distance between the source city and the all cities
            {
                printf("\nDistance from %s to %s = %d", TranslateBack(Source), TranslateBack(i), Weight[i]);
            }
            if (command == 3)//print the full route of the shortest path including the distance between each two cities and the total shortest cost
            {
                if (i == Destination)
                {
                    printf("\nDistance from %s to %s = %d", TranslateBack(Source), TranslateBack(i), Weight[i]);
                    printf("\nPath:\n%s", TranslateBack(i));
                    j = i;
                    do
                    {
                        int k=j;
                        j = Predecessor[j];
                        int r=j;
                        printf(" <--(%d)-- %s",Graph[k][r],TranslateBack(j));
                    } while (j != Source);
                    break;
                }
            }
            if (command == 0)//prints the information of step 3 (previous command) to shortest_path.txt and exits the program
            {
                FILE *Short= fopen("shortest_path.txt","a");
                if (i == Destination)
                {
                    fprintf(Short,"Distance from %s to %s = %d", TranslateBack(Source), TranslateBack(i), Weight[i]);
                    fprintf(Short,"\nPath:\n%s", TranslateBack(i));
                    j = i;
                    do
                    {
                        int k=j;
                        j = Predecessor[j];
                        int r=j;
                        fprintf(Short," <--(%d)-- %s",Graph[k][r],TranslateBack(j));
                    } while (j != Source);
                    fclose(Short);
                    break;
                }
            }
        }
    }

}

//main function
int main()
{
    //The adjacent array graph
    int Graph[NumberOfCities][NumberOfCities];
    //initialize the graph by zeros
    memset(Graph, 0, sizeof(Graph[0][0]) * NumberOfCities * NumberOfCities);
    //open the data file
    FILE *CitiesFile = fopen("cities.txt", "r");

    char City1[30];//From
    char City2[30];//To
    int Distance;//Distance between cities

    char Line[250];
    int Source = 6/*The default source is Jerusalem (The capital)*/, Destination = 0;
    int command;

    //continuous loop until break
    while (true)
    {
        //menu
        printf("1- Load cities\n");
        printf("2- Enter source city\n");
        printf("3- Enter destination city\n");
        printf("0- Exit");
        printf("\nEnter Command: \n");
        scanf("%d", &command);
        switch (command)
        {
            //Load the file and construct the graph
            case 1:
                while (fgets(Line, sizeof(Line), CitiesFile) != NULL)
                {
                    sscanf(Line, "%[^\t]\t%[^\t]\t%dkm", City1, City2, &Distance);
                    if (Graph[Translate(City1)][Translate(City2)] == 0)
                    {
                        Graph[Translate(City1)][Translate(City2)] = Distance;
                        Graph[Translate(City2)][Translate(City1)] = Distance;
                    }
                }
                fclose(CitiesFile);
                printf("Lode is done successfully\n");
                break;
                //Read the source city and compute the Dijkstra algorithm
            case 2:
                printf("Enter source city: \n");
                scanf("%s", City1);//Read the source city
                Source = Translate(City1);
                if (Source == 999)//if there is no such city
                {
                    printf("There is no such city\n");
                    exit(0);
                }
                Dijkstra(Graph, NumberOfCities, Source, Destination, command);//call the Dijkstra function
                printf("\n");
                break;
                //print the full route of the shortest path including the distance between each two cities and the total shortest cost
            case 3:
                printf("Enter destination city: \n");
                scanf("%s", City2);
                Destination = Translate(City2);
                if (Destination == 999)
                {
                    printf("There is no such city\n");
                    exit(0);
                }
                Dijkstra(Graph, NumberOfCities, Source, Destination, command);
                printf("\n");
                break;
                //prints the information of step 3 to shortest_path.txt and exits the program
            case 0:
                fflush(stdin);
                FILE *Short= fopen("shortest_path.txt","w");
                Dijkstra(Graph, NumberOfCities, Source, Destination, command);
                fclose(Short);
                printf("\n");
                exit(0);
            default:
                printf("Invalid command\n");
                exit(0);
        }
    }
    return 0;
}