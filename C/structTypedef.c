#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ROCK = 'R',
    PAPER = 'P',
    SCISSORS = 'S'
} Choice;

int main() {
      srand(time(NULL));

    while(1) {
        printf("Enter R for Rock, P for Paper, or S for Scissors, or Q to Quit: ");
        char input;
        scanf(" %c", &input);

        if (input == 'Q' || input == 'q') {
            printf("Thanks for playing!");
            break;
        }

        Choice choice = (Choice)input;

        int computer = rand() % 3 + ROCK;

        printf("You chose: %c\n", input);
        printf("Computer chose: %c\n", (char)computer);

        if (choice == computer)
            printf("It's a tie!\n");
        else if ((choice == ROCK && computer == SCISSORS) ||
                                  (choice == PAPER && computer == ROCK) ||
                                  (choice == SCISSORS && computer == PAPER))
            printf("You win this round!\n");
        else
            printf("Computer wins this round!\n");

        printf("\n");
    }

    return 0;
}

