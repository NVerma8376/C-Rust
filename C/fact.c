#include <stdio.h>

int main(void) {
    int num;
    scanf("%d", &num);

    long long fact = 1;
    for(int i = 1; i <= num; i++) {
        fact = fact * i;
    }

    printf("%lld\n", fact);
    return 0;
}
