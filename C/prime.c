#include <stdio.h>

int main(void) {
    int num;
    scanf("%d", &num);

    int isPrime = 1;
    for(int i = 2; i < num; i++) {
        if(num % i == 0) {
            isPrime = 0;
            break;
        }
    }

    if(isPrime) {
        printf("Prime\n");
    } else {
        printf("Not Prime\n");
    }

    return 0;
}
