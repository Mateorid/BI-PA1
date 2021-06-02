#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#define epsilon 100000000 * DBL_EPSILON /*=10^-8, is used as margain of error for floats comparison*/

/*
* Structure for the Flights
* "x" and "y" are the coordinates of the plane
* "name" is the name of the flight
*/
typedef struct Flight
{
    long double x;
    long double y;
    char *name;
} T_FLIGHT;

/*Scanning function for the flights*/
T_FLIGHT *scanFlights(int *n)
{
    /*
    * tmpFlight = temporary T_FLIGHT structure
    * max = the allocated memory for flights
    * n = number of flights
    * line = scanned line from getline
    * tmp = temp arr for storing the flight name
    * length = holds the size of the input buffer
    */
    T_FLIGHT *tmpFlight = NULL;
    int max = 0;
    *n = 0;
    char *line = NULL;
    char *tmp = NULL;
    size_t length = 0;

    /*Scanning stdin until EOF*/
    while (getline(&line, &length, stdin) != -1)
    {
        /*Increasing the memory, slower at the start(+10), faster later (x1.5)*/
        if (*n >= max)
        {
            max += (max < 50) ? 10 : max / 2;
            tmpFlight = (T_FLIGHT *)realloc(tmpFlight, max * sizeof(*tmpFlight));
        }

        /*Allocating memory for the tmp name array.*/
        tmp = (char *)malloc((strlen(line)) * sizeof(char));

        /*
        * Checking for incorrect input & getting the X,Y coordinates and the name
        * If the input is incorrect it returns "NULL"
        */
        if (sscanf(line, " [ %Lf , %Lf ] %[^\n]", &tmpFlight[*n].x, &tmpFlight[*n].y, tmp) != 3)
        {
            free(line);
            free(tmp);
            if (tmpFlight != NULL)
            {
                for (int i = 0; i < *n; i++)
                {
                    free(tmpFlight[i].name);
                }
            }
            free(tmpFlight);
            return NULL;
        }

        /*Allocating the memory and copying the name into the structure name + 1 for newline*/
        tmpFlight[*n].name = (char *)malloc(strlen(tmp) * sizeof(char) + 1);
        strcpy(tmpFlight[*n].name, tmp);
        free(tmp);
        (*n)++;
    }
    free(line);
    return tmpFlight;
}

/*Function used to find the distance between 2 points*/
long double findDistance(T_FLIGHT f1, T_FLIGHT f2)
{
    return sqrt((f1.x - f2.x) * (f1.x - f2.x) + (f1.y - f2.y) * (f1.y - f2.y));
}

/*Function that finds and returns the shortest distance between flights*/
long double closestPoints(T_FLIGHT Flight[], int n)
{
    long double min = FLT_MAX; /*Sets "min" to the highest possible float, so it's always >= than the distance between the flights*/
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (findDistance(Flight[i], Flight[j]) < min)
            {
                min = findDistance(Flight[i], Flight[j]);
            }
        }
    }
    return min;
}

/*Function that finds and prints the names of the flights that are closest together*/
void printFlights(T_FLIGHT Flight[], int n, long double min)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(findDistance(Flight[i], Flight[j]) - min) <= (epsilon * findDistance(Flight[i], Flight[j])))
            {
                printf("%s - %s\n", Flight[i].name, Flight[j].name);
            }
        }
    }
}

/*------------------------------MAIN------------------------------*/
int main(void)
{
    int n = 0;
    long double min = 0;
    T_FLIGHT *Flights = NULL;

    /*Scanning inputs*/
    printf("Zadejte lety:\n");
    Flights = scanFlights(&n);

    /*Checking for error while scanning the inputs*/
    if (Flights == NULL || n < 2)
    {
        printf("Nespravny vstup.\n");
        free(Flights);
        return 1;
    }

    /*Printing the results*/
    min = closestPoints(Flights, n);
    printf("Nejmensi vzdalenost: %Lf\n", min);
    printFlights(Flights, n, min);

    /*Freeing memory*/
    if (Flights != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            free(Flights[i].name);
        }
    }
    free(Flights);
    return 0;
}