#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;
    char playAgain;

    // Seed the random number generator
    srand(time(0));

    do {
        // Generate a random number between 1 and 100
        number = rand() % 10 + 1;

        printf("Welcome to the Number Guessing Game!\n");
        printf("I have selected a number between 1 and 10. Can you guess it?\n");
        printf("%d", number);
        printf("\n");

        // Reset attempts for each game
        attempts = 0;

        do {
            printf("Enter your guess: ");
            scanf("%d", &guess);

            attempts++;

            if (guess > number) {
                printf("Too high! Try again.\n");
            } else if (guess < number) {
                printf("Too low! Try again.\n");
            } else {
                printf("Congratulations! You guessed the number in %d attempts.\n", attempts);
            }
        } while (guess != number);

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain); // The space before %c consumes any leftover newline character

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thank you for playing! Goodbye.\n");
    return 0;
}
