#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

double root (void (*f)(double*, double), void (*g)(double*, double), double a, double b, double eps1, const char param1, const char param2) {
    double x, y, y1, y2, xn, xnn;
    unsigned n = 1;
    eps1 /= 1024.0;
    d(&x, f, a);
    d(&y, g, a);
    y1 = x-y;
    d(&x, f, b);
    d(&y, g, b);
    y2 = x-y;
    if ((y1-y2 <= 0.0 && y1 > 0.0 && y2 > 0.0) || (y1-y2 >= 0.0 && y1 < 0.0 && y2 < 0.0)) { // F' > 0 и не убывает или F' < 0 и не возрастает
        xnn = a;
        do {
        xn = xnn;
        f(&x, xn);
        g(&y, xn);
        y1 = x-y;
        xnn = xn - (b-xn)*y1/(y2-y1);
        ++n;
        } while (xnn-xn-eps1 > 0 || xn-xnn-eps1 > 0);
    }
    else {
        xnn = b;
        do {
        xn = xnn;
        f(&x, xn);
        g(&y, xn);
        y2 = x-y;
        xnn = xn - (a-xn)*y2/(y1-y2);
        ++n;
        } while (xnn-xn-eps1 > 0 || xn-xnn-eps1 > 0);
    }
    if (param1) printf ("number of iterations: %u\n", n);
    if (param2) printf ("intersection point: %lf\n", xnn);
 }

double integral (void *f, double a, double b, double eps2);

void testroot (unsigned N) {
    printf ("Test format: n m a b eps ; where n and m - numbers of functions, a and b - borders of the segment\n");
    for (unsigned i = 1; i <= N; ++i) {
        printf ("Test %u: ", i);
        unsigned n, m;
        double a, b, eps;
        scanf ("%u%u%lf%lf%lf", &n, &m, &a, &b, &eps);
        if (n == m) {
            printf ("n = m -- ERROR\n");
            i--;
            continue;
        }
        if (n > m) {
            n ^= m;
            m ^= n;
            n ^= m;
        }
        if (n == 1 && m == 2) root (f1, f2, a, b, eps, 1, 1);
        else if(n == 1 && m == 3) root (f1, f3, a, b, eps, 1, 1);
        else if(n == 2 && m == 3) root (f2, f3, a, b, eps, 1, 1);  
        else {
            printf ("ERROR: m and n should be in the range from 1 to 3\n");
            i--;
            continue;
        }
    }
}

int main (char argc, char** argv) {
    double x, y; 
/*    scanf ("%lf", &y);
for (y = 1.0; y-2.0 <= 0.0; y += 0.2) {
    printf ("\ny = %lf\n", y);
    f1 (&x, y);
    printf ("f1: %lf\n", x);
    f2 (&x, y);
    printf ("f2: %lf\n", x);
    f3 (&x, y);
    printf ("f3: %lf\n", x);
    d(&x, f1, y);
    printf ("df1: %lf\n", x);
    d(&x, f2, y);
    printf ("df2: %lf\n", x);
    d(&x, f3, y);
    printf ("df3: %lf\n", x);
}
*/
    double eps1 = 0.00000000001;
    char a = 0, it = 0;
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i],"-a")) {
            a = 1;
        }
        if (!strcmp(argv[i],"-it")) {
            it = 1;
        }
        if (!strcmp(argv[i],"-help")) {
            printf ("OPTIONS:\n-a  : output of all abscissa values of intersection points for all pairs of functions\n-it : output of the numbers of iterations to find the roots of the equations\n-test-root NUM : testing of the function root; NUM is number of the tests\n");
        }
        if (!strcmp(argv[i],"-test-root")) {
            int N = atoi(argv[i+1]); 
            testroot (N);
        }
     }
    if (it || a) printf ("Functions:\nf1 and f2:\n");
    root (f1, f2, 1.0, 2.0, eps1, it, a);
    if (it || a) printf ("\nf1 and f3:\n");
    root (f1, f3, -3.0, -2.0, eps1, it, a);
    if (it || a) printf ("\nf2 and f3:\n");
    root (f3, f2, -1.0, -0.5, eps1, it, a);

    return 0;
}
