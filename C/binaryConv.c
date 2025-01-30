
#include <stdio.h>

int main(int argc, char *argv[])
{
    int len = 10;
    int bin[len];    // Array to store binary digits
    int dec;
    
    // Initialize the bin array to 0
    for (int i = 0; i < len; i++) {
        bin[i] = 0;
    }

    printf("What number to convert: ");
    scanf("%d", &dec);
    
    // Handle the case when the number is zero
    if (dec == 0) {
        printf("Binary: 0\n");
        return 0;
    }

    // Convert decimal to binary
    int index = len - 1;
    while (dec > 0) {
        bin[index] = dec % 2;
        dec /= 2;
        index--;
    }
    
    // Print the binary representation
    printf("Binary: ");
    for (int i = 0; i < len; i++) {
        printf("%d", bin[i]);
    }
    printf("\n");

    return 0;
}
