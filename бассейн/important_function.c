#include <stdio.h>
#include <math.h>

double imf(double x) {
    return 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1.0/3.0) - 1e3) * x + 3) / 
    (x * x / 2) - x * pow(10 + x, 2.0 / x) - 1.01;
}

int main() {
    double x;

    if (scanf("%lf", &x) != 1 && x<= 0) {
        printf("n/a\n");
        return 1;
    }

    printf("%.1f\n", imf(x)); 

    return 0;
}