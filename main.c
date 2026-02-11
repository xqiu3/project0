/* Project 0 - Input Validation and Buffer Overruns
 * Author: Keer Wang
 * Purpose: create a program that does not validate input and leads to a buffer
 *          overflow, and allows memory to directly accessed. Also, write
 *          more secure versions of the functions that do not have these
 *          vulnerabilities.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h> /* contains constant USHRT_MAX */
#include <stdlib.h> /* for exit() */

#define MAX_USERS 10
#define MAX_NAME_LEN 39
#define EXIT_VALUE 99

void print_this_user_info(unsigned short userindex, char username[], unsigned short userpin, bool userIsAdmin);
bool get_user_preference();
int get_user_to_modify_vulnerable();
void change_pin_vulnerable(int user_i, unsigned short u_pin[], int new_pin);
int get_user_to_modify_more_secure(int current_num_users);
bool change_pin_more_secure(int u_index, unsigned short u_pin[], int new_pin);

int main(void) {
    struct {
        unsigned short user_isAdmin[MAX_USERS];
        unsigned short user_pin[MAX_USERS];
        char user_name[MAX_USERS][MAX_NAME_LEN];
    } user_data;

    int i;
    int num_users = 0;
    int user_index = 0;
    int new_pin = 0;
    char buffer[256] = "";
    bool vulnerable_mode = false;
    bool success = false;

    /* initialize memory */
    memset(user_data.user_isAdmin, 0, sizeof(user_data.user_isAdmin));
    memset(user_data.user_pin, 0, sizeof(user_data.user_pin));
    memset(user_data.user_name, '-', sizeof(user_data.user_name));

    /* admin user */
    user_data.user_pin[0] = 16962;
    user_data.user_isAdmin[0] = true;
    strncpy(user_data.user_name[0], "ADMIN", strlen("ADMIN")+1);

    /* default user */
    user_data.user_pin[1] = 4369;
    user_data.user_isAdmin[1] = false;
    strncpy(user_data.user_name[1], "DEFAULT USER", strlen("DEFAULT USER")+1);

    num_users = 2;

    /* ask user preference */
    vulnerable_mode = get_user_preference();

    /* main loop */
    while (1) {

        /* print all users */
        for (i = 0; i < num_users; i++) {
            print_this_user_info(i,
                                 user_data.user_name[i],
                                 user_data.user_pin[i],
                                 user_data.user_isAdmin[i]);
        }

        printf("-------------\n");

        if (vulnerable_mode) {
            printf("Running VULNERABLE code\n");

            user_index = get_user_to_modify_vulnerable();

            printf("Enter new PIN: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &new_pin);

            change_pin_vulnerable(user_index, user_data.user_pin, new_pin);

        } else {
            printf("Running SECURE code\n");

            user_index = get_user_to_modify_more_secure(num_users);

            printf("Enter new PIN: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &new_pin);

            success = change_pin_more_secure(user_index, user_data.user_pin, new_pin);

            if (!success) {
                printf("PIN change failed due to validation.\n");
            }
        }
    }

    return 0;
}

/* ---------------- helper functions ---------------- */

void print_this_user_info(unsigned short userindex, char username[],
                          unsigned short userpin, bool userIsAdmin) {
    printf("---User Index #%d---\n", userindex);
    printf("Name: %s\n", username);
    printf("PIN: %u\tisAdmin: %d\n", userpin, userIsAdmin);
}

/* ask user for mode */
bool get_user_preference() {
    char buffer[256] = "";
    int selection = 0;

    printf("Choose program mode:\n");
    printf("1) Run VULNERABLE code\n");
    printf("2) Run SECURE code (default)\n");
    printf("Enter choice: ");

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &selection);

    return (selection == 1);
}

/* intentionally vulnerable */
int get_user_to_modify_vulnerable(void) {
    char buffer[256] = "";
    int index = 0;

    printf("Enter user index to modify (%d to quit): ", EXIT_VALUE);
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &index);

    if (index == EXIT_VALUE) exit(0);

    return index;  /* NO validation */
}

void change_pin_vulnerable(int user_i, unsigned short u_pin[], int new_pin) {
    u_pin[user_i] = new_pin;  /* no validation, vulnerable */
}

/* secure functions */
int get_user_to_modify_more_secure(int current_num_users) {
    char buffer[256] = "";
    int index = -1;

    while (1) {
        printf("Enter user index (0-%d) or %d to quit: ",
               current_num_users - 1, EXIT_VALUE);

        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &index) != 1) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (index == EXIT_VALUE) exit(0);

        if (index >= 0 && index < current_num_users) {
            return index;
        }

        printf("Invalid index. Try again.\n");
    }
}

bool change_pin_more_secure(int user_i, unsigned short u_pin[], int new_pin) {
    if (user_i < 0 || user_i >= MAX_USERS) {
        printf("Invalid user index!\n");
        return false;
    }

    if (new_pin < 0 || new_pin > USHRT_MAX) {
        printf("Invalid PIN value!\n");
        return false;
    }

    u_pin[user_i] = (unsigned short)new_pin;
    return true;
}
