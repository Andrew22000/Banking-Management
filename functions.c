#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "Account_handling.h"
#include "output.h"

// 1. spatii la inceput
// 2. VERIFICA ALTE CHESTII
char check_IBAN(char *command) {

    command = strstrip(command);
    if (strlen(command) != 18) return 0;

    if(command[0] != 'R')
        return 0;
    if(command[1] != 'O')
        return 0;

    for (int i = 2 ; i < 6 ; i++){
        if (!('0' <= command[i] && command[i] <= '9')) return 0;
    }
    for (int i = 6 ; i < 14 ; i++){
        if (!('a' <= command[i] && command[i] <= 'z')) return 0;
    }
    for (int i = 14 ; i < 18 ; i++){
        if (!('A' <= command[i] && command[i] <= 'Z')) return 0;
    }

    return 1;
}

char check_Currency(char *Currency) {

    if(strcmp(strlwr(Currency),"ron") == 0 || strcmp(strlwr(Currency),"dollars") == 0 || strcmp(strlwr(Currency),"yen") == 0 || strcmp(strlwr(Currency),"euro") == 0) {
        return 1;
    }

    return 0;
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

char *check_if_login_or_register(char *command) {
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

char *Add_Account(char* array_of_accounts, char *account) {
    strcpy(array_of_accounts, account);

    return array_of_accounts;
}

char *change_IBAN(char **Array, char *placeholder, const char *IBAN, int right_account) {
    int number_of_commas = 0;
    int k = 0;
    int something;

    for (int i = 0; i < strlen(Array[right_account]); i++) {
        if (Array[right_account][i] == ',') {
            placeholder[i] = Array[right_account][i];
            number_of_commas++;
            continue;
        }
        if(number_of_commas == 1) {
            placeholder[i] = IBAN[k];
            k++;
            continue;
        }

        placeholder[i] = Array[right_account][i];
        something = i + 1;
    }

    placeholder[something] = '\0';

    return placeholder;
}

char *change_Currency(char **Array, char *placeholder, const char *New_currency, int right_account) {
    int number_of_commas = 0;
    int k = 0,pos = 0;

    for (int i = 0; i < strlen(Array[right_account]); i++) {
        if (Array[right_account][i] == ',') {
            placeholder[pos] = Array[right_account][i];
            number_of_commas++;
            pos++;
            continue;
        }
        if(number_of_commas == 2)
            while(New_currency[k] != '\0') {
                placeholder[pos] = New_currency[k];
                k++;
                pos++;
            }

        if(number_of_commas != 2) {
            placeholder[pos] = Array[right_account][i];
            pos++;
        }
    }

    placeholder[pos] = '\0';

    return placeholder;
}

char *exchange_rate_Amount(const char* account, char* new_currency) {
    char* Amount = malloc(100 * sizeof(char));

    char* ptr;

    double new_amount = strtod(Take_Amount(account),&ptr);

    if(strcmp(Take_Currency(account),"ron") == 0){
        if(strcmp(new_currency,"dollars") == 0)
            new_amount *= 0.21;

        else if(strcmp(new_currency,"euro") == 0)
            new_amount *= 0.20;

        else if(strcmp(new_currency,"yen") == 0)
            new_amount *= 32.80;

    }

    else if(strcmp(Take_Currency(account),"dollars") == 0){
        if(strcmp(new_currency,"ron") == 0)
            new_amount *= 4.67;

        else if(strcmp(new_currency,"euro") == 0)
            new_amount *= 0.94;

        else if(strcmp(new_currency,"yen") == 0)
            new_amount *= 153.28;

    }

    else if(strcmp(Take_Currency(account),"euro") == 0){
        if(strcmp(new_currency,"ron") == 0)
            new_amount *= 4.99;

        else if(strcmp(new_currency,"dollars") == 0)
            new_amount *= 1.07;

        else if(strcmp(new_currency,"yen") == 0)
            new_amount *= 163.57;
    }

    else if(strcmp(Take_Currency(account),"yen") == 0){
        if(strcmp(new_currency,"ron") == 0)
            new_amount *= 0.03;

        else if(strcmp(new_currency,"dollars") == 0)
            new_amount *= 0.0065;

        else if(strcmp(new_currency,"euro") == 0)
            new_amount *= 0.0061;
    }

    sprintf(Amount, "%lf", new_amount);

    for (int i = strlen(Amount) - 1; i >= 0; i--) {

        if (Amount[i] == '.') {
        Amount[i] = '\0';
        //Amount[i+1] = '\0';
        break;

    } else if (Amount[i] != '0') {
        Amount[i+1] = '\0';
        //Amount[i+2] = '\0';
            break;
    }

    Amount[i] = '\0';
}

    return Amount;

}

char *change_Amount(char **Array, char *placeholder, const char *New_amount, int right_account) {
    int number_of_commas = 0;
    int k = 0,pos = 0;

    for (int i = 0; i < strlen(Array[right_account]) - strlen(Take_Amount(Array[right_account])); i++) {
        if (Array[right_account][i] == ',') {
            placeholder[pos] = Array[right_account][i];
            number_of_commas++;
            pos++;
            continue;
        }

        /*if(number_of_commas == 3)
            while(New_amount[k] != '\0'){
            placeholder[pos] = New_amount[k];
            k++;
            pos++;
        }*/

        if(number_of_commas != 3) {
            placeholder[pos] = Array[right_account][i];
            pos++;
        }
    }

    for(int i = 0; i < strlen(New_amount); i++){
        placeholder[pos] = New_amount[i];
        pos++;
    }

    placeholder[pos] = '\n';
    placeholder[pos + 1] = '\0';
    return placeholder;
}

char *Remaining_Amount(char* account, char *Amount) {
    double new_amount = Take_Amount_as_Double(account);

    char* p;

    double transaction_amount = strtod(Amount,&p);

    new_amount -= transaction_amount;

    sprintf(Amount, "%lf", new_amount);

    for (int i = strlen(Amount) - 1; i >= 0; i--) {

        if (Amount[i] == '.') {
            Amount[i] = '\0';
            //Amount[i+1] = '\0';
            break;

        } else if (Amount[i] != '0') {
            Amount[i+1] = '\0';
            //Amount[i+2] = '\0';
            break;
        }

        Amount[i] = '\0';
    }

    return Amount;


}

double Take_Amount_as_Double(char *account) {
    char* ptr;

    double amount = strtod(Take_Amount(account),&ptr);

    return amount;
}


char *Transaction(char **Array, char *placeholder, char *Amount, int right_account, int transaction_account) {

    char* p;

    double amount_after_transaction = Take_Amount_as_Double(Array[transaction_account]);

    double amount_added = strtod(Amount,&p);


    if(strcmp(Take_Currency(Array[right_account]),"ron") == 0){
        if(strcmp(Take_Currency(Array[transaction_account]),"dollars") == 0)
            amount_added *= 0.21;

        else if(strcmp(Take_Currency(Array[transaction_account]),"euro") == 0)
            amount_added *= 0.20;

        else if(strcmp(Take_Currency(Array[transaction_account]),"yen") == 0)
            amount_added *= 32.80;

    }

    else if(strcmp(Take_Currency(Array[right_account]),"dollars") == 0){
        if(strcmp(Take_Currency(Array[transaction_account]),"ron") == 0)
            amount_added *= 4.67;

        else if(strcmp(Take_Currency(Array[transaction_account]),"euro") == 0)
            amount_added *= 0.94;

        else if(strcmp(Take_Currency(Array[transaction_account]),"yen") == 0)
            amount_added *= 153.28;

    }

    else if(strcmp(Take_Currency(Array[right_account]),"euro") == 0){
        if(strcmp(Take_Currency(Array[transaction_account]),"ron") == 0)
            amount_added *= 4.99;

        else if(strcmp(Take_Currency(Array[transaction_account]),"dollars") == 0)
            amount_added *= 1.07;

        else if(strcmp(Take_Currency(Array[transaction_account]),"yen") == 0)
            amount_added *= 163.57;
    }

    else if(strcmp(Take_Currency(Array[right_account]),"yen") == 0){
        if(strcmp(Take_Currency(Array[transaction_account]),"ron") == 0)
            amount_added *= 0.03;

        else if(strcmp(Take_Currency(Array[transaction_account]),"dollars") == 0)
            amount_added *= 0.0065;

        else if(strcmp(Take_Currency(Array[transaction_account]),"euro") == 0)
            amount_added *= 0.0061;
    }

    amount_after_transaction += amount_added;

    sprintf(Amount,"%lf",amount_after_transaction);

    for (int i = strlen(Amount) - 1; i >= 0; i--) {

        if (Amount[i] == '.') {
            Amount[i] = '\0';
            //Amount[i+1] = '\0';
            break;

        } else if (Amount[i] != '0') {
            Amount[i+1] = '\0';
            //Amount[i+2] = '\0';
            break;
        }

        Amount[i] = '\0';
    }

    strcpy(Array[transaction_account],change_Amount(Array,placeholder,Amount,transaction_account));

    return Array[transaction_account];

}









