
#include <stdio.h>

int main(int argc, char *argv[]) {
    char word[5];   // Array to store the word
    int check = 1;   // Assume user won until proven otherwise

    printf("Enter a 5-letter word: ");
    scanf("%s", word);   // Read the word

    // Loop to take guesses
    for (int i = 0; i < 5; i++) {
        char guess;
        printf("Enter guess %d: ", i + 1);
        scanf(" %c", &guess);   // Use " %c" to skip any leftover newline character
        
        int found = 0;  // Flag to track if the guess is found in the word

        // Check if the guess is in the word
        for (int j = 0; j < 5; j++) {
            if (guess == word[j]) {
                word[j] = 'Z';  // Mark the guessed character as guessed
                found = 1;      // Set flag to indicate guess was correct
            }
        }

        // If the guess was incorrect, set check to 0 (lost)
        if (!found) {
            check = 0;
        }
    }

    // Check if all characters are guessed correctly (all are 'Z')
    for (int i = 0; i < 5; i++) {
        if (word[i] != 'Z') {
            check = 0;
            break;
        }
    }

    if (check) {
        printf("WON!\n");
    } else {
        printf("LOST\n");
    }

    return 0;
}
