/* Project 0 - Input Validation and Buffer Overruns
 * Author: Keer Wang
 * Purpose: demonstrate vulnerable input handling and buffer overrun
 *          memory can be accessed directly without validation.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_NAME_LEN 39
#define EXIT_VALUE 99

void print_this_user_info(unsigned short userindex, char username[], unsigned short userpin, bool userIsAdmin);
int get_user_to_modify_vulnerable();
void change_pin_vulnerable(int user_i, unsigned short u_pin[], int new_pin);

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

    printf("Running VULNERABLE version (no input validation!)\n");

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

        /* vulnerable flow */
        user_index = get_user_to_modify_vulnerable();

        printf("Enter new PIN: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &new_pin);

        change_pin_vulnerable(user_index, user_data.user_pin, new_pin);
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
