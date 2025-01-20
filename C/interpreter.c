#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

// Function to handle arithmetic operations
void handle_arithmetic(char *command) {
    char op;
    double num1, num2, result;

    // Parse the input (e.g., "add 5 3" becomes "+ 5 3")
    if (sscanf(command, "%lf %c %lf", &num1, &op, &num2) != 3) {
        printf("Error: Invalid input format.\n");
        return;
    }

    // Perform the operation
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero.\n");
                return;
            }
            result = num1 / num2;
            break;
        default:
            printf("Error: Unsupported operator '%c'.\n", op);
            return;
    }

    // Print the result
    printf("Result: %.2lf\n", result);
}

// Main REPL function
void repl() {
    char input[MAX_INPUT];

    printf("Welcome to the Mini Interpreter! Type 'exit' to quit.\n");

    while (1) {
        printf("> ");
        if (!fgets(input, MAX_INPUT, stdin)) {
            break; // Handle EOF
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        // Exit the interpreter
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Check the command
        if (strncmp(input, "calc ", 5) == 0) {
            handle_arithmetic(input + 5);
        } else {
            printf("Error: Unknown command. Use 'calc' for arithmetic operations.\n");
        }
    }

    printf("Goodbye!\n");
}

int main() {
    repl();
    return 0;
}
