#include <stdio.h>
#include <string.h>

int main(){
    printf("Enter string: ");
    char str[100];
    scanf("%s", str);
    char action[10];
    printf("What do you want to do? (len/rev/palin): ");
    scanf("%s", action);

    if (strcmp(action, "len") == 0) {

        int len = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            len++;
        }
        printf("Length: %d\n", len);
    }
    else if (strcmp(action, "rev") == 0) {
            printf("Reversed string: ");
            // Find the length of string first
            int len = strlen(str);
            // Print characters from last to first
            for (int i = len - 1; i >= 0; i--) {
                printf("%c", str[i]);
            }
            printf("\n");
    }
    else if (strcmp(action, "palin") == 0) {

        int len = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            len++;
        }
        int is_palindrome = 1;
        for (int i = 0; i < len/2; i++) {
            if (str[i] != str[len-i-1]) {
                is_palindrome = 0;
                break;
            }
        }
        if (is_palindrome) {
            printf("Palindrome\n");
        } else {
            printf("Not a palindrome\n");
        }
    }
}
