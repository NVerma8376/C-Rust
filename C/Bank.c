
#include <stdio.h>

typedef struct UserInfo{
    int id[100];           // Store user IDs
    int balance[100];      // Store user balances
    int idcount;           // Keep track of the number of users
} UserInfo;

int main(int argc, char *argv[]) {
    UserInfo user;
    user.idcount = 0;

    while (1) {
        printf("What do you want to do? 1 for new user, 2 for signin: ");
        int input;
        scanf("%d", &input);
        
        if (input == 1) {
            printf("Creating new user...\n");
            int newId = user.idcount + 1; // Assign new ID based on count
            user.id[user.idcount] = newId;
            user.balance[user.idcount] = 0; // Initialize balance to 0
            user.idcount++;
            printf("New user created with ID: %d\n", newId);
        } 
        else if (input == 2) {
            printf("Enter ID: ");
            int idno;
            scanf("%d", &idno);
            int check = 0;
            
            // Find the user by ID
            for (int i = 0; i < user.idcount; i++) {
                if (user.id[i] == idno) {
                    printf("Signed in!\n");
                    check = 1;
                    // Proceed with balance-related operations
                    int action;
                    printf("What do you want to do? 3 for deposit, 4 for withdrawal, 5 for quit: ");
                    scanf("%d", &action);
                    if (action == 3) {
                        int deposit;
                        printf("Enter deposit amount: ");
                        scanf("%d", &deposit);
                        user.balance[i] += deposit;  // Update the balance for the user
                        printf("Your balance is: $%d\n", user.balance[i]);
                    }
                    else if (action == 4) {
                        int withdraw;
                        printf("Enter withdrawal amount: ");
                        scanf("%d", &withdraw);
                        if (withdraw <= user.balance[i]) {
                            user.balance[i] -= withdraw;  // Deduct the amount from the balance
                            printf("Your balance is: $%d\n", user.balance[i]);
                        } else {
                            printf("Insufficient balance!\n");
                        }
                    }
                    else if (action == 5) {
                        printf("See you again!\n");
                    }
                    break;
                }
            }
            if (!check) {
                printf("Invalid ID!\n");
            }
        }
    }
    return 0;
}
