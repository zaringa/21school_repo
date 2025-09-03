#include <stdio.h>

int main() {
    float a1, a2;
    
    scanf("%f %f", &a1, &a2);
    int b1 = (int)a1;
    int b2 = (int)a2;
    
    if (a1 == b1 && a2 == b2) {
        if (a2 == 0.0){
            printf("%d %d %d n/a\n", (int)(a1 + a2), (int)(a1 - a2), (int)((float)(b1 * b2)));
        }
        else{
            printf("%d %d %d %d\n", (int)(a1 + a2), (int)(a1 - a2), (int)((float)(b1 * b2)), (int)((float)(b1 / (float)b2)));
        }
    } else {
        
        printf("n/a\n");
        return 0;
    }
    return 0;
}