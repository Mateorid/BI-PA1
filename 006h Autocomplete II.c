#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/*Structure for the texts*/
typedef struct Text
{
    long double amount;
    char *text;
} TTEXT;

/*Scanning function*/
TTEXT *scanTexts(int *n)
{
    int max = 0;
    size_t lenght = 0;
    char *line = NULL;
    char *tmpData = NULL;
    TTEXT *tmpText = NULL;

    while (getline(&line, &lenght, stdin) != EOF)
    {
        /*Increasing the memory for the text structure*/
        if (*n >= max)
        {
            max += (max < 50) ? 10 : (max / 2);
            tmpText = (TTEXT *)realloc(tmpText, max * sizeof(*tmpText));
        }

        /*No data input*/
        if (strlen(line) == 0)
        {
            free(tmpText);
            free(line);
            return NULL;
        }

        tmpData = (char *)malloc((strlen(line) + 1) * sizeof(char));

        /*Scanning*/
        if (sscanf(line, " %Lf : %[^\n\n]", &tmpText[*n].amount, tmpData) != 2 || tmpText[*n].amount < 0)
        {
            /*Empty line break*/
            if (sscanf(line, "%1[\n]", tmpData) == 1)
            {
                if (*n == 0) //0 lines entered
                {
                    free(line);
                    free(tmpData);
                    free(tmpText);
                    return NULL;
                }

                free(line);
                free(tmpData);
                return tmpText;
            }
            /*Wrong inputs*/
            if (tmpText != NULL)
            {
                for (int i = 0; i < *n; i++)
                {
                    free(tmpText[i].text);
                }
            }
            free(line);
            free(tmpData);
            free(tmpText);
            return NULL;
        }

        /*Allocating memory for the text*/
        tmpText[*n].text = (char *)malloc(strlen(tmpData) * sizeof(char) + 1);
        strcpy(tmpText[*n].text, tmpData);

        free(tmpData);
        (*n)++;
    }
    free(line);
    if (tmpText != NULL)
    {
        for (int i = 0; i < *n; i++)
        {
            free(tmpText[i].text);
        }
    }
    free(tmpText);
    return NULL;
}

/*Quick sort*/
int sortFunction(const void *a, const void *b)
{
    return (*(long double *)b - *(long double *)a);
}

/*Getting the number of phrases*/
void autocomplete(TTEXT arr[], char *word, int count)
{
    int matches = 0;
    for (int i = 0; i < count; i++)
    {
        /*Getting and printing the amount of aligible suggestion*/
        if ((strcasestr(arr[i].text, word)) != NULL)
        {
            matches = matches + 1;
        }
    }
    printf("Nalezeno: %d\n", matches);
    for (int i = 0; i < count; i++)
    {
        /*Getting and printing suggestions*/
        if ((strcasestr(arr[i].text, word)) != NULL)
        {
            printf("> %s\n", arr[i].text);
        }
    }
}

/*------------------------------MAIN------------------------------*/
int main(void)
{
    TTEXT *texts = NULL; //Arr of the text structures
    int count = 0;       //Number of phrases scanned
    int count2 = 0;      //Number of phrases that we search for
    size_t lenght = 0;   //Getline argument
    char *word = NULL;   //Getline scanned word

    /*Scanning 1*/
    printf("Casto hledane fraze:\n");
    texts = scanTexts(&count);

    if (texts == NULL) //Wrong input
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    /*Sorting the phrases by their search number*/
    qsort(texts, count, sizeof(TTEXT), sortFunction);

    /*Scanning 2*/
    printf("Hledani:\n");
    while (getline(&word, &lenght, stdin) != EOF)
    {
        /*Getting rid of the newline in the word*/
        word[strcspn(word, "\r\n")] = 0;

        /*Getting and printing answers*/
        autocomplete(texts, word, count);
        count2 += 1;
    }
    /*Checking if there is > 0 words scanned and returning fail if false*/
    if (count2 == 0)
    {
        printf("Nespravny vstup.\n");

        /*Freeing memory*/
        if (texts != NULL)
        {
            for (int i = 0; i < count; i++)
            {
                free(texts[i].text);
            }
        }
        free(texts);
        free(word);
        return 1;
    }

    /*Freeing memory*/
    if (texts != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            free(texts[i].text);
        }
    }
    free(texts);
    free(word);
    return 0;
}