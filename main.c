/* Project 0 - Input Validation and Buffer Overruns
 * Author: Keer Wang
 * Purpose: initial skeleton for the project
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

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

    int i, num_users = 0;
    int user_index = 0, new_pin = 0;
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

    /* main loop placeholder */
    while (1) {
        for (i = 0; i < num_users; i++) {
            print_this_user_info(i, user_data.user_name[i],
                                 user_data.user_pin[i], user_data.user_isAdmin[i]);
        }
        printf("-------------\n");

        if (vulnerable_mode) {
            printf("VULNERABLE functionality will go here\n");
        } else {
            printf("SECURE functionality will go here\n");
        }
    }

    return 0;
}

/* function skeletons */

void print_this_user_info(unsigned short userindex, char username[],
                          unsigned short userpin, bool userIsAdmin) {
    printf("---User Index #%d---\n", userindex);
    printf("Name: %s\nPIN: %u\tisAdmin: %d\n", username, userpin, userIsAdmin);
}


bool get_user_preference() {
    printf("Menu: 1) Vulnerable 2) Secure (default)\n");
    return false;  /* default is secure */
}

int get_user_to_modify_vulnerable() { return -1; }
void change_pin_vulnerable(int user_i, unsigned short u_pin[], int new_pin) {}
int get_user_to_modify_more_secure(int current_num_users) { return -1; }
bool change_pin_more_secure(int user_i, unsigned short u_pin[], int new_pin) { return false; }
