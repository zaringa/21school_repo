#include <stdio.h>

int max(int b1, int b2){
    int mx;
    if(b1 > b2){
        mx = b1;
    }
    else {
        mx = b2;
    }
    return mx;
}
int main(){
    float a1, a2;
    scanf("%f %f", &a1, &a2);
    int b1 = (int)a1;
    int b2 = (int)a2;
    
    if (a1 == b1 && a2 == b2) {
        printf("%d\n", max(b1,b2));
    }else{
        printf("n/a\n");
    }
    return 0;

}