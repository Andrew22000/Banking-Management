#include <stdio.h>
#include "functions.h"
#include "File_handling.h"
#include <stdlib.h>
#include <string.h>

// TODO
// Crashes if 3 names are provided in login




int main() {

    int nr_accounts = 0;

    FILE *Banking_Information = fopen("E:\\Programming Project\\Bank_Accounts.txt", "r");

    char* header = (char*)malloc(100 * sizeof(char));
    fgets(header, 255, Banking_Information);

    char* user_input = (char*)malloc(100 * sizeof(char));

    printf("Welcome to Horizon Trust Bank! In order to login into your account please enter the command 'login [NAME] [SURNAME]'\n");

    fgets(user_input, 255, stdin);
    user_input[strlen(user_input) - 1] = '\0';

    char* file_line = (char*)malloc(10 * sizeof(char*));
    char** Same_Owner_accounts = malloc(100 * sizeof(char*));

    if(strcmp("login",check_if_login(user_input)) == 0) {

        strcpy(file_line, "");

        while(fgets(file_line, 255, Banking_Information)){

            if(strcmp(Eliminate_first_word(user_input), Take_Name_Surname(file_line)) == 0){
                Same_Owner_accounts = Add_Account(Same_Owner_accounts,file_line,nr_accounts);
                nr_accounts++;
            }
            strcpy(file_line, "");
        }

        if(nr_accounts == 0){
            printf("There is no account with that owner!");
        }

        if(nr_accounts == 1){
            printf("User logged in successfully! What action do you want to take next?\n");
            printf("1.View Amount                  2.Change IBAN\n");
            printf("3.Change Currency              4.Delete account\n");
            printf("5.Exit\n");
        }

        if(nr_accounts > 1){
            printf("User logged in successfully! Choose which account do you want to work in!\n");
            for(int i = 0; i < nr_accounts; i++){
                printf("%d.%s",i+1,Same_Owner_accounts[i]);
            }

        }


    }


    free(Same_Owner_accounts);
    free(file_line);
    free(header);
    free(user_input);
    return 0;

}
