#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//Funkce pro zjisteni jestli je cislo palindrom(binarne symetricke)
long long int palindrome(long long int vstup)
{
    long long int kopieVstupu, cisloPozpatku;

    cisloPozpatku = 0;
    kopieVstupu = vstup;
    //Prevod na bin pozpatku
    while (kopieVstupu != 0)
    {
        cisloPozpatku = cisloPozpatku * 2;
        cisloPozpatku = cisloPozpatku + kopieVstupu % 2;
        kopieVstupu = kopieVstupu / 2;
    }
    return cisloPozpatku;

    if (cisloPozpatku == vstup)
    {
        return vstup;
    }
    else
    {
        return 0;
    }
}
//Funkce na vypsani binarniho cisla
long long int decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];

    // counter for binary array
    if (n == 0)
    {
        printf("0");
    }

    int i = 0;
    while (n > 0)
    {

        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        cout << binaryNum[j];

    return 0;
}

//Hlavni funkce
int main(void)
{
    printf("Vstupni intervaly:\n");
    char LnC;
    long long int lo, hi;
    long long int testEOF;
    int a = 1;

    while (a == 1)
    {
        testEOF = scanf(" %c %lld %lld", &LnC, &lo, &hi);
        //Test pro EOF
        if (testEOF == EOF)
        {
            break;
            return 0;
            a = 0;
        }

        //Osetreni
        else if (testEOF != 3 || lo < 0 || lo > hi || hi < 0)
        {
            printf("Nespravny vstup.\n");
            break;
            a = 0;
            return 1;
        }
        else
        {
            //Funkce "c"
            if (LnC == 'c')
            {
                //long long int pocetCisel = (hi - lo) + 1;
                long long int temp = lo;
                long long int temp2 = 0;
                while (temp <= hi)
                {
                    if (temp % 2 == 1 || temp == 0)
                    {

                        if (palindrome(temp) == temp)
                        {
                            temp2 = temp2 + 1;
                        }
                    }
                    temp = temp + 1;
                }
                printf("Celkem: %lld\n", temp2);
            }
            //Funkce "l"
            else if (LnC == 'l')
            {
                long long int temp = lo;
                while (temp <= hi)
                {
                    if (palindrome(temp) == temp)
                    {
                        printf("%lld = ", temp);
                        decToBinary(temp);
                        printf("b\n");
                    }

                    temp = temp + 1;
                }
            }
            //Neni f ani c
            else
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
        }
    }

    return 0;
}
