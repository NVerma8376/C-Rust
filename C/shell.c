#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define DELIMITERS " \t\r\n\a"

void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fork failed
        perror("Error creating process");
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    }
}

char **parse_command(char *line) {
    int bufsize = MAX_ARGUMENTS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_ARGUMENTS;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

void shell_loop() {
    char *line = NULL;
    size_t bufsize = 0;
    char **args;

    while (1) {
        printf("NVerma> ");
        getline(&line, &bufsize, stdin);

        // Parse the command into arguments
        args = parse_command(line);

        // Check if command is empty
        if (args[0] == NULL) {
            free(args);
            continue;
        }

        // Exit command
        if (strcmp(args[0], "exit") == 0) {
            free(args);
            break;
        }

        // Execute the command
        execute_command(args);
        free(args);
    }

    free(line);
}

int main() {
    printf("Welcome to My Shell! Type 'exit' to quit.\n");
    shell_loop();
    printf("Goodbye!\n");
    return 0;
}
