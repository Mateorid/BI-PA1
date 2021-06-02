#include <stdio.h>
#include <math.h>
#include <float.h>

//#define EPS 1e-6

int main(void)
{
    double x, y, z, m, n, o;

    //Nacteni 1.

    printf("Trojuhelnik #1:\n");

    if (scanf("%lf %lf %lf", &x, &y, &z) != 3 || x <= 0 || y <= 0 || z <= 0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    else if (fabs((x + y) - z) <= (1000 * DBL_EPSILON * z) || fabs((x + z) - y) <= (1000 * DBL_EPSILON * y) || fabs((z + y) - x) <=(1000 *  DBL_EPSILON  * x))
    {
        printf("Strany netvori trojuhelnik.\n");
        return 0;
    }

    //Nacteni 2.

    printf("Trojuhelnik #2:\n");

    if (scanf("%lf %lf %lf", &m, &n, &o) != 3 || m <= 0 || n <= 0 || o <= 0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    else if (fabs((m + n) - o) <= (1000 * DBL_EPSILON * o) || fabs((m + o) - n) <= ( 1000*DBL_EPSILON * n) || fabs((o + n) - m) <= ( 1000 * DBL_EPSILON * m))
    {
        printf("Strany netvori trojuhelnik.\n");
        return 0;
    }

    double tmp;
    //Serazeni 1
    if ((x <= y) && (x <= z))
    {
        if (z <= y)
        {

            tmp = z;
            z = y;
            y = tmp;
            //ok
        }
    }

    else if ((y <= x) && (y <= z))
    {
        if (x <= z)
        {
            tmp = y;
            y = x;
            x = tmp;
            //ok
        }
        else
        {
            tmp = x;
            x = y;
            y = tmp;
            tmp = y;
            y = z;
            z = tmp;
            //ok
        }
    }
    else if ((z <= x) && (z <= y))
    {
        if (x <= y)
        {
            tmp = y;
            y = z;
            z = tmp;
            tmp = x;
            x = y;
            y = tmp;
            //ok
        }
        else
        {
            tmp = z;
            z = x;
            x = tmp;
            //ok
        }
    }

    //Serazeni 2

    if ((m <= n) && (m <= o))
    {
        if (o <= n)
        {

            tmp = o;
            o = n;
            n = tmp;
            //ok
        }
    }

    else if ((n <= m) && (n <= o))
    {
        if (m <= o)
        {
            tmp = n;
            n = m;
            m = tmp;
            //ok
        }
        else
        {
            tmp = m;
            m = n;
            n = tmp;
            tmp = n;
            n = o;
            o = tmp;
            //ok
        }
    }
    else if ((o <= m) && (o <= n))
    {
        if (m <= n)
        {
            tmp = n;
            n = o;
            o = tmp;
            tmp = m;
            m = n;
            n = tmp;
            //ok
        }
        else
        {
            tmp = o;
            o = m;
            m = tmp;
            //ok
        }
    }
    //Shodnost
    if ((x == m) && (y == n) && (z == o))
    {
        printf("Trojuhelniky jsou shodne.\n");
        return 0;
    }
    double XM = (x / m);
    double YN = (y / n);
    double ZO = (z / o);

    if ((fabs(XM - YN) <= 1024 * DBL_EPSILON * YN) && (fabs(YN - ZO) <= 1024 * DBL_EPSILON * ZO))
    {
        printf("Trojuhelniky nejsou shodne, ale jsou podobne.\n");
    }

    else
    {
        printf("Trojuhelniky nejsou shodne ani podobne.\n");
    }

    return 0;
}