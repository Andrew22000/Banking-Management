#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. spatii la inceput
// 2. VERIFICA ALTE CHESTII
char check_IBAN(char *command) {

    command = strstrip(command);
    if (strlen(command) != 16) return 0;

    for (int i = 0 ; i < 4 ; i++){
        if (!('0' <= command[i] && command[i] <= '9')) return 0;
    }
    for (int i = 4 ; i < 12 ; i++){
        if (!('a' <= command[i] && command[i] <= 'z')) return 0;
    }
    for (int i = 12 ; i < 16 ; i++){
        if (!('A' <= command[i] && command[i] <= 'Z')) return 0;
    }

    return 1;
}

char *strstrip(char *input_string) {
    char* spaceless_string;
    spaceless_string = (char*) malloc(sizeof(input_string));
    int i = 0;
    int k = 0;
    while(input_string[i] == ' ') {
        i++;
    }

    int j = strlen(input_string) - 1;
    while(input_string[j] == ' ') {
        j--;
    }

    while(i <= j){
        spaceless_string[k] = input_string[i];
        i++;
        k++;
    }
    spaceless_string[k] = '\0';
    return spaceless_string;
}

/*void view_data(char* name_surname) {
    FILE* f = fopen("E:\\Programming Project\\Bank_Accounts.txt","r");
    char line[255];
    while(fgets(line,255,f)) {

        if()
    }
} */

char *Eliminate_first_word(char *input) {
    int i = 0;
    input = strstrip(input);
    while(input[i] != ' ') {
        input[i] = ' ';
        i++;
    }
    input = strstrip(input);
    return input;
}



FILE *open_file(const char *file_path, const char *mode) {
    if (file_path == NULL || mode == NULL || strlen(file_path) == 0 || strlen(mode) == 0) return 0;
    FILE *file = fopen(file_path, mode);

    return file;
}

char *check_if_login(char *command) {
    command = strstrip(command);

    char *first;
    first = malloc(sizeof(command));

    for (int i = 0; i < strlen(command); i++) {
        if (command[i] != ' ' && command[i] != '\0')
            first[i] = command[i];
        else {
            first[i] = '\0';
            return first;
        }
    }
    return first;
}

char **Add_Account(char **array_of_accounts, char *account, int pos) {

    array_of_accounts[pos] = malloc((strlen(account) + 1) * sizeof(char));

    strcpy(array_of_accounts[pos], account);

    return array_of_accounts;
}



