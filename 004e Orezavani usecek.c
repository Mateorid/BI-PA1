#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_LENGHTS 500000

//Function for sorting the new number
void numberSort(int *arr, int amount)
{
    int tmp = 0;
    for (int i = 0; i < amount - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
        }
    }
}

//Function for calculation the lowest possible cost of cutting
int cuttingPrice(int *arr, int amountOfCuts)
{
    int price = 0, i = 0, z = 0;
    for (int x = 0; x < amountOfCuts + z - 1; x++)
    {
        if (arr[i] <= arr[i + 1])
        {
            arr[i + 1] += arr[i];
            arr[i] = 0;
            price += arr[i + 1];
        }
        else
        {
            numberSort(arr, amountOfCuts);
            z++;
            i--;
        }
        i++;
    }
    return price;
}

int main(void)
{
    int status = 0, numberOfLenghts = 0, lenghts[MAX_LENGHTS] = {0};

    printf("Zadejte delky:\n"); //Reading sequence
    while (1)
    {
        status = scanf("%d", &lenghts[numberOfLenghts]);
        if (status == EOF) //Cheking for end of file
        {
            if (numberOfLenghts == 0) //No values entered
            {
                printf("Nespravny vstup.\n");
                return EXIT_FAILURE;
            }
            else
            {
                break;
            }
        }
        if (status != 1 || lenghts[numberOfLenghts] < 1 || numberOfLenghts == MAX_LENGHTS) //Input doesn't meet the requirements
        {
            printf("Nespravny vstup.\n");
            return EXIT_FAILURE;
        }
        else //Correct input, counting the amount of lenghts entered
        {
            numberOfLenghts++;
        }
    }

    //Sorting lenghts from shortest (maybe change to quicksort if this is 2 slow?)
    for (int i = 0; i < numberOfLenghts; i++)
    {
        for (int j = 0; j < numberOfLenghts - 1; j++)
        {
            if (lenghts[j] > lenghts[i])
            {
                int tmp = lenghts[i];
                lenghts[i] = lenghts[j];
                lenghts[j] = tmp;
            }
        }
    }

    //Checking if there is only 1 lenght
    if (numberOfLenghts == 1)
    {
        printf("Cena za deleni: 0\n");
        return 0;
    }
    //Calculating the cost
    int celkovaCena = cuttingPrice(lenghts, numberOfLenghts);
    printf("Cena za deleni: %d\n", celkovaCena);
    return 0;
}
