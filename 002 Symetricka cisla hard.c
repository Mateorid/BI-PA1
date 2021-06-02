#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//Funkce pro zjisteni jestli je cislo palindrom(symetricke) = cisloPospatku
long long int palindrome(long long int vstup, int ciselZakl)
{
    long long int kopieVstupu, cisloPozpatku;

    cisloPozpatku = 0;
    kopieVstupu = vstup;
    //Prevod na bin pozpatku
    while (kopieVstupu != 0)
    {
        cisloPozpatku = cisloPozpatku * ciselZakl;
        cisloPozpatku = cisloPozpatku + kopieVstupu % ciselZakl;
        kopieVstupu = kopieVstupu / ciselZakl;
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
//Funkce na prevod do dane ciselne soustavy

char prevodDeciNaCiselnyZaklad(int vstupniCislo)
{
    if (vstupniCislo >= 0 && vstupniCislo <= 9)
        return (char)(vstupniCislo + '0');
    else
        return (char)(vstupniCislo - 10 + 'a');
}

//Funkce na vypsani
char *vypisCisla(char velikostPole[], int ciselnyZaklad, int vsupniCislo)
{
    int index = 0;
    while (vsupniCislo > 0)
    {
        velikostPole[index++] = prevodDeciNaCiselnyZaklad(vsupniCislo % ciselnyZaklad);
        vsupniCislo /= ciselnyZaklad;
    }
    velikostPole[index] = '\0';
    return velikostPole;
}


//Hlavni funkce
int main(void)
{
    printf("Vstupni intervaly:\n");
    char LnC;
    char velikostPole[100];
    int cisZakl;
    long long int lo, hi;
    long long int testEOF;
    int a = 1;

    while (a == 1)
    {
        testEOF = scanf(" %c %d %lld %lld", &LnC, &cisZakl, &lo, &hi);
        //Test EOF
        if (testEOF == EOF)
        {
            break;
            return 0;
            a = 0;
        }

        //Osetreni
        else if (testEOF != 4 || lo < 0 || lo > hi || hi < 0 || cisZakl < 2 || cisZakl > 36)
        {
            printf("Nespravny vstup.\n");
            break;
            a = 0;
            return 1;
        }
        else
        {
            //Funkce C
            if (LnC == 'c')
            {
                long long int temp = lo;
                long long int temp2 = 0;
                while (temp <= hi)
                {
                    if (palindrome(temp, cisZakl) == temp)
                    {
                        temp2 = temp2 + 1;
                    }

                    temp = temp + 1;
                }
                printf("Celkem: %lld\n", temp2);
            }
            //Funkce L
            else if (LnC == 'l')
            {
                long long int temp = lo;

                while (temp <= hi)
                {

                    if (palindrome(temp, cisZakl) == temp)
                    {
                        if (temp == 0)
                        {
                            printf("%lld = 0 (%d)\n", temp, cisZakl);
                            temp += temp;
                        }
                        else
                        {
                            printf("%lld = %s (%d)\n", temp, vypisCisla(velikostPole, cisZakl, temp), cisZakl);
                        }
                    }
                    temp = temp + 1;
                }
            }
            else //Neni f ani c
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
        }
    }
    return 0;
}
