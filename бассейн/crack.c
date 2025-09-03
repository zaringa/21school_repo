#include <stdio.h>

int main() {
    double x, y;

    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("n/a\n");
        return 1; 
    }

    if (x * x + y * y <= 25) {
        printf("GOTCHA\n"); 
    } else {
        printf("MISS\n");   
    }

    return 0; 
}