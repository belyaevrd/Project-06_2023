#include <stdio.h>
#include "func.h"

int main (void) {
    double x, y; 
    scanf ("%lf", &y);
    f1 (&x, y);
    printf ("f1: %lf\n", x);
    f2 (&x, y);
    printf ("f2: %lf\n", x);
    f3 (&x, y);
    printf ("f3: %lf\n", x);
    df1 (&x, y);
    printf ("df1: %lf\n", x);
    df2 (&x, y);
    printf ("df2: %lf\n", x);
    df3 (&x, y);
    printf ("df3: %lf\n", x);
    return 0;
}
