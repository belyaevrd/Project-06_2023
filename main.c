#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"

double root (double (*f)(double), double (*g)(double), double a, double b, double eps1, const char param1, const char param2) {
    double x, y, y1, y2, xn, xnn;
    unsigned n = 1;
    y1 = d(f, a) - d(g, a);
    y2 = d(f, b) - d(g, b);
    if ((y1-y2 <= 0.0 && y1 > 0.0 && y2 > 0.0) || (y1-y2 >= 0.0 && y1 < 0.0 && y2 < 0.0)) { // F' > 0 и не убывает или F' < 0 и не возрастает
        xnn = a;
        y2 = f(b)-g(b);
        do {
            xn = xnn;
            y1 = f(xn) - g(xn);
            xnn = xn - (b-xn)*y1/(y2-y1);
            x = f (xnn);
            y = g (xnn);
            ++n;
        } while ((fabs(xnn-xn)-eps1 > 0) || (fabs(x-y-y1)-eps1 > 0));
    }
    else { // F' < 0 и не убывает или F' > 0 и не возрастает
        xnn = b;
        y1 = f(a)-g(a);
         do {
            xn = xnn;
            y2 = f(xn)-g(xn);
            xnn = xn - (xn-a)*y2/(y2-y1);
            x = f (xnn);
            y = g (xnn);
            ++n;
        } while ((fabs(xnn-xn)-eps1 > 0) || (fabs(x-y-y2)-eps1 > 0));
    }
    if (param1) printf ("number of iterations: %u\n", n);
    if (param2) printf ("intersection point: %lf\n", xnn);
    return xnn;
 }

double integral (double (*f)(double), double a, double b, double eps2, char param) {
    double S = 0, r, x;
    int n;
    if (f == f1) {
        n = sqrt((b-a)*(b-a)*(b-a)/24/eps2*f(b));
        ++n;
    }
    else if (f == f2) {
        n = 2;
    }
    else {
        double x = fabs(10.0/(a*a*a)), y = fabs(10.0/(b*b*b));
        x = x-y > 0 ? x : y;
        x = x > 0 ? x : 1.0;
        n = sqrt((b-a)*(b-a)*(b-a)/24/eps2*x);
        ++n;
    }
    r = (b-a)/n/2;
    S = 0;
    for (int i = 1; i <= 2*n-1; i += 2) {
       S += f(a+r*i);
    }
    S = S*(b-a)/n;
    if (param) printf ("Integral of function: %lf\n", S);
    return S;
}

void testroot (unsigned N) {
    if (!N) return;
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
        if      (n == 1 && m == 2) root (f1, f2, a, b, eps, 1, 1);
        else if (n == 1 && m == 3) root (f1, f3, a, b, eps, 1, 1);
        else if (n == 2 && m == 3) root (f2, f3, a, b, eps, 1, 1);  
        else {
            printf ("ERROR: m and n should be in the range from 1 to 3\n");
            i--;
            continue;
        }
    }
}

void testintegral (unsigned N) {
    if (!N) return;
    printf ("Test format: n a b eps ; where n - number of function, a and b - borders of the segment\n");
    for (unsigned i = 1; i <= N; ++i) {
        printf ("Test %u: ", i);
        unsigned n, m;
        double a, b, eps;
        scanf ("%u%lf%lf%lf", &n, &a, &b, &eps);
        if      (n == 1) integral (f1, a, b, eps, 1);
        else if (n == 2) integral (f2, a, b, eps, 1);
        else if (n == 3) integral (f3, a, b, eps, 1);  
        else {
            printf ("ERROR: n should be in the range from 1 to 3\n");
            i--;
            continue;
        }
    }
}

int main (char argc, char** argv) {
    double x, y; 
    double eps1 = 0.00001, eps2 = 0.0001;
    char a = 0, it = 0;
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i],"-a")) {
            a = 1;
        }
        if (!strcmp(argv[i],"-it")) {
            it = 1;
        }
        if (!strcmp(argv[i],"-help")) {
            printf ("OPTIONS:\n-a  : output of all abscissa values of intersection points for all pairs of functions\n\
-it : output of the numbers of iterations to find the roots of the equations\n\
--test-root NUM : testing of the function root; NUM is number of the tests\n\
--test-integral NUM : testing of the function integral; NUM is number of the tests\n");
        }
        if (!strcmp(argv[i],"--test-root")) {
            int N = atoi(argv[i+1]); 
            testroot (N);
        }
        if (!strcmp(argv[i],"--test-integral")) {
            int N = atoi(argv[i+1]); 
            testintegral (N);
        }
      }

    double x1, x2, x3;
    if (it || a) printf ("Functions:\nf1 and f2:\n");
    x3 = root (f1, f2, 1.0, 2.0, eps1, it, a);
    if (it || a) printf ("\nf1 and f3:\n");
    x1 = root (f1, f3, -3.0, -2.0, eps1, it, a);
    if (it || a) printf ("\nf2 and f3:\n");
    x2 = root (f3, f2, -1.0, -0.5, eps1, it, a);
    
    double i1, i2, i3, I;
    i1 = integral (f1, x1, x3, eps2, 0);
    i2 = integral (f2, x2, x3, eps2, 0);
    i3 = integral (f3, x1, x2, eps2, 0);
    I = i3+i2-i1;
    printf ("The area of the figure: %lf\n", I);
    return 0;
}
