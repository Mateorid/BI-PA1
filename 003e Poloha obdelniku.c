#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#define RECT_NO_OVERLAP 0
#define RECT_OVERLAP 1
#define RECT_A_IN_B 2
#define RECT_B_IN_A 3
#define RECT_ERROR (-1)
#endif /* __PROGTEST__ */

int rectanglePosition(int ax1, int ay1,
                      int ax2, int ay2,
                      int bx1, int by1,
                      int bx2, int by2)
{
  //Udela a1/b1 levy dolni a a2/b2 pravy horni
  if (ax1 > ax2)
  {
    int tmp;
    tmp = ax1;
    ax1 = ax2;
    ax2 = tmp;
  }

  if (bx1 > bx2)
  {
    int tmp;
    tmp = bx1;
    bx1 = bx2;
    bx2 = tmp;
  }
  if (ay1 > ay2)
  {
    int tmp;
    tmp = ay1;
    ay1 = ay2;
    ay2 = tmp;
  }

  if (by1 > by2)
  {
    int tmp;
    tmp = by1;
    by1 = by2;
    by2 = tmp;
  }
  
  //Pokud vstup neni obdelnik
  if (ax1 == ax2 || ay1 == ay2 || bx1 == bx2 || by1 == by2)
  {
    return RECT_ERROR;
  }
  //Pokud se obdélníky nepřekrývaji (nad sebou nebo vedle sebe)
  else if ((ay1 >= by2) || (by1 >= ay2) || (bx1 >= ax2) || (ax1 >= bx2))
  {
    return RECT_NO_OVERLAP;
  }

  //Pokud je B v A
  else if ((ax1 < bx1) && (ax2 > bx2) && (ay1 < by1) && (ay2 > by2))
  {
    return RECT_B_IN_A;
  }

  //Pokud je A v B
  else if ((bx1 < ax1) && (bx2 > ax2) && (by1 < ay1) && (by2 > ay2))
  {
    return RECT_A_IN_B;
  }

  else
  {
    return RECT_OVERLAP;
  }
}

//testovaci program
#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  assert(rectanglePosition(0, 0, 10, 10, 2, 8, 4, 6) == RECT_B_IN_A);
  assert(rectanglePosition(2, 6, 3, 7, 1, 5, 4, 8) == RECT_A_IN_B);
  assert(rectanglePosition(0, 0, 50, 20, 50, -100, 100, -100) == RECT_ERROR);
  assert(rectanglePosition(1, 6, 3, 7, 1, 5, 4, 8) == RECT_OVERLAP);
  assert(rectanglePosition(0, 0, 1, 1, 1, 0, 0, 1) == RECT_OVERLAP);
  assert(rectanglePosition(0, 0, 50, 20, 10, 5, 75, 40) == RECT_OVERLAP);
  assert(rectanglePosition(0, 20, 50, 0, 75, 40, 10, 5) == RECT_OVERLAP);
  assert(rectanglePosition(0, 0, 50, 20, -100, 100, 100, 90) == RECT_NO_OVERLAP);
  assert(rectanglePosition(0, 0, 50, 20, 50, -100, 100, 100) == RECT_NO_OVERLAP);
  assert(rectanglePosition(70, 110, 63, 70, 70, 98, 61, 110) == RECT_OVERLAP);
  assert(rectanglePosition(152, 132, 132, 118, 152, 118, 132, 107) == RECT_NO_OVERLAP);
  assert(rectanglePosition(1, -1, 5, -5, 0, 0, 10, 10) == RECT_NO_OVERLAP);
  assert(rectanglePosition(0, 0, 8, 9, 0, 0, 3, 4) == RECT_OVERLAP);
  assert(rectanglePosition(2, 3, 4, -3, 1, 1, 5, 5) == RECT_OVERLAP);
  assert(rectanglePosition(-1, -1, 3, 1, 0, 3, 3, -3) == RECT_OVERLAP);
  assert(rectanglePosition(0, 0, 1, 2, 0, 0, -1, -2) == RECT_NO_OVERLAP);
  assert(rectanglePosition(40, -22, 61, -13, 40, -13, 61, 9) == RECT_NO_OVERLAP);
  assert(rectanglePosition(69, 126, 39, 118, 56, 151, 49, 97) == RECT_OVERLAP);
  assert(rectanglePosition(-7, -85, -26, -89, -26, -85, -7, -64) == RECT_NO_OVERLAP);
  return 0;
}
#endif /* __PROGTEST__ */
