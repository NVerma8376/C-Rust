#include <stdio.h>
#include <string.h>

int main() {
    int amt;
    printf("Enter the number of elements: ");
    scanf("%d", &amt);

    int arr[amt];
    printf("Enter %d numbers:\n", amt);
    for (int i = 0; i < amt; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Array: ");
    for(int i = 0; i < amt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Clear input buffer
    while (getchar() != '\n');

    char action[10];
    printf("What do you want to do? (max/min/sum/avg/rev): ");
    scanf("%s", action);

    if (strcmp(action, "max") == 0) {
        int max = arr[0];
        for (int i = 1; i < amt; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        printf("Max: %d\n", max);
    }
    else if (strcmp(action, "min") == 0) {
        int min = arr[0];
        for (int i = 1; i < amt; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        printf("Min: %d\n", min);
    }
    else if (strcmp(action, "sum") == 0) {
        int sum = 0;
        for (int i = 0; i < amt; i++) {
            sum += arr[i];
        }
        printf("Sum: %d\n", sum);
    }
    else if (strcmp(action, "avg") == 0) {
        float sum = 0;
        for (int i = 0; i < amt; i++) {
            sum += arr[i];
        }
        printf("Avg: %.2f\n", sum/amt);
    }else if (strcmp(action, "rev") == 0) {
        printf("Reversed array: ");
        for (int i = amt - 1; i >= 0; i--) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else {
        printf("Invalid input\n");
    }

    return 0;
}
