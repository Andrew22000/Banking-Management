#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "Account_handling.h"
#include "output.h"

// TODO
// Crashes if 3 names are provided in login




int main() {

    int nr_accounts_of_person = 0,total_accounts = 0;

    FILE* Banking_Information = fopen("E:\\Programming Project\\Bank_Accounts.txt", "r");

    char* header = (char*)malloc(100 * sizeof(char));
    fgets(header, 255, Banking_Information);

    char* user_input = (char*)malloc(100 * sizeof(char));

    Welcome_statement();

    fgets(user_input, 255, stdin);
    user_input[strlen(user_input) - 1] = '\0';

    char* file_line = (char*)malloc(100 * sizeof(char));
    char** Same_Owner_accounts = malloc(100 * sizeof(char*));
    char** All_Accounts = malloc(100 * sizeof(char*));

    for(int i = 0; i < 10; i++){
        Same_Owner_accounts[i] = malloc(100 * sizeof(char));
    }

    for(int i = 0; i < 10; i++){
        All_Accounts[i] = malloc(100 * sizeof(char));
    }

    if(strcmp("login",check_if_login_or_register(user_input)) == 0) {

        strcpy(file_line, "");

        while(fgets(file_line, 255, Banking_Information)){

            strcpy(All_Accounts[total_accounts],Add_Account(All_Accounts[total_accounts],file_line));

            if(strcmp(strlwr(Eliminate_first_word(user_input)), strlwr(Take_Name_Surname(file_line))) == 0){
                strcpy(Same_Owner_accounts[nr_accounts_of_person],Add_Account(Same_Owner_accounts[nr_accounts_of_person],file_line));
                nr_accounts_of_person++;
            }
            strcpy(file_line, "");
            total_accounts++;
        }

        if(nr_accounts_of_person == 0){
            printf("There is no account with that owner!");
        }

        if(nr_accounts_of_person == 1){
            Only_one_account_output(Same_Owner_accounts);

            int right_account;

            for(int i = 0; i <= total_accounts; i++){
                if(strcmp(Same_Owner_accounts[0],All_Accounts[i]) == 0) {
                    right_account = i;
                    break;
                }
            }

            Same_Owner_accounts[0][strlen(Same_Owner_accounts[0])-1] = '\0';

            char choice[255];
            int action;

            while(1) {
                Account_choices();

                scanf("%d",&action);

                    if (action == 1) {
                        Print_amount(Same_Owner_accounts[0]);

                        Other_choice();

                        scanf("%s",choice);

                        if(strcmp(strlwr(choice),"yes") != 0) {
                            Exit_statement();
                            break;
                        }

                    }

                    else if (action == 2) {

                        Change_IBAN_print();

                        char* New_IBAN = malloc(100 * sizeof(char));
                        char* placeholder_account2 = malloc((sizeof(All_Accounts[right_account])));

                        while(1){

                        scanf("%s",New_IBAN);

                        char verify_IBAN = 0;
                        verify_IBAN = check_IBAN(New_IBAN);


                            if (verify_IBAN == 1) {
                                strcpy(All_Accounts[right_account],change_IBAN(All_Accounts, placeholder_account2, New_IBAN, right_account));
                                printf("IBAN changed successfully\n");
                                break;
                            }

                            else if (verify_IBAN == 0) {
                                printf("That is an invalid IBAN! Please try again!\n");
                            }
                        }

                        free(New_IBAN);


                        Other_choice();

                        scanf("%s",choice);

                        if(strcmp(strlwr(choice),"yes") != 0) {
                            Exit_statement();
                            break;
                        }
                    }

                    else if (action == 3) {

                        Change_Currency_print();

                        char* New_currency = malloc(100 * sizeof(char));
                        char* placeholder_account3 = malloc(sizeof(All_Accounts[right_account]));
                        char* amount = malloc(sizeof(All_Accounts[right_account]));

                        while(1){

                            scanf("%s",New_currency);

                            char verify_currency = 0;
                            verify_currency = check_Currency(New_currency);

                            if(verify_currency == 1){
                                strcpy(amount, exchange_rate_Amount(All_Accounts[right_account],New_currency));
                                strcpy(All_Accounts[right_account], change_Amount(All_Accounts,placeholder_account3,amount,right_account));
                                strcpy(All_Accounts[right_account], change_Currency(All_Accounts,placeholder_account3,New_currency,right_account));

                                printf("Currency changed successfully!\n");
                                break;
                            }

                            else{
                                printf("this input is invalid! Please enter another input!\n");
                            }

                        }

                        free(New_currency);

                        Other_choice();

                        scanf("%s",choice);

                        if(strcmp(strlwr(choice),"yes") != 0)
                            break;
                    }

                    else if (action == 4) {
                        Change_Amount_print();

                        char* New_amount = malloc(100 * sizeof(char));
                        char* placeholder_account4 = malloc(sizeof(All_Accounts[right_account]));

                        scanf("%s",New_amount);
                        strcpy(All_Accounts[right_account], change_Amount(All_Accounts, placeholder_account4, New_amount,right_account));

                        printf("Amount changed successfully!");

                        Other_choice();

                        scanf("%s",choice);

                        if(strcmp(strlwr(choice),"yes") != 0) {
                            Exit_statement();
                            break;
                        }
                    }

                    else if (action == 5) {
                        Transactions_print();

                        int transaction_account = total_accounts + 1;

                        char* Transaction_IBAN = malloc(sizeof(All_Accounts[right_account]));
                        char* Transaction_amount = malloc(sizeof(All_Accounts[right_account]));
                        char* placeholder5 = malloc(sizeof(All_Accounts[right_account]) + 1);
                        char* Transaction_amount_copy = malloc(sizeof(All_Accounts[right_account]));

                        while(1){
                            scanf("%s",Transaction_IBAN);

                            for(int i = 0; i < total_accounts; i++) {

                                if (strcmp(Take_IBAN(All_Accounts[i]), Transaction_IBAN) == 0) {

                                    transaction_account = i;
                                    break;
                                }
                            }

                            if(transaction_account != total_accounts + 1 && transaction_account != right_account) {

                                while (1) {
                                    printf("Account found! Please enter the amount that you want to transfer!\n");

                                    scanf("%s", Transaction_amount);

                                    if (strcmp(Take_Amount(All_Accounts[right_account]), Transaction_amount) < 0) {
                                        printf("You do not have enough money in your account in order to complete this transaction!\n");
                                        printf("Try entering a lower amount!\n");
                                    }

                                    else
                                        break;
                                }

                                strcpy(Transaction_amount_copy,Transaction_amount);

                                Transaction(All_Accounts,placeholder5,Transaction_amount,right_account,transaction_account);

                                strcpy(All_Accounts[right_account], change_Amount(All_Accounts,placeholder5,
                                                                                  Remaining_Amount(All_Accounts[right_account],Transaction_amount_copy),right_account));

                                printf("Transaction made successfully!\n");
                                break;


                            }

                            else if(transaction_account == right_account){
                                printf("You cannot make a transaction into the same account! Try entering another IBAN!");
                            }

                            else{
                                printf("There is no account with that IBAN! Try entering another IBAN!");
                            }
                        }


                        Other_choice();

                        scanf("%s",choice);

                        if(strcmp(strlwr(choice),"yes") != 0) {
                            Exit_statement();
                            break;
                        }
                    }

                    else if(action == 6){

                        for(int i = 0; i < total_accounts; i++) {
                            if (i == total_accounts - 1)
                                strcpy(All_Accounts[i], "");

                            else if (i >= right_account)
                                strcpy(All_Accounts[i], All_Accounts[i + 1]);
                        }

                        Delete_Account_print();
                        break;
                    }

                    else if(action == 7){
                        Exit_statement();

                        break;
                    }

                    else {
                        Invalid_input();
                    }

            }


        }

        if(nr_accounts_of_person > 1){
            More_accounts_output(Same_Owner_accounts,nr_accounts_of_person);

            int chosen_account,right_account;

            while(1) {
                scanf("%d", &chosen_account);

                if (chosen_account > nr_accounts_of_person || chosen_account < 0) {
                    printf("There is no account with that number!\n");
                    printf("Please enter another number!\n");
                } else
                    break;
            }

            chosen_account--;

            for(int i = 0; i <= total_accounts; i++){
                if(strcmp(Same_Owner_accounts[chosen_account],All_Accounts[i]) == 0) {
                    right_account = i;
                    break;
                }
            }

            Same_Owner_accounts[chosen_account][strlen(Same_Owner_accounts[chosen_account])-1] = '\0';

            char choice[255];
            int action;

            while(1) {
                Account_choices();

                scanf("%d",&action);

                if (action == 1) {
                    Print_amount(Same_Owner_accounts[chosen_account]);

                    Other_choice();

                    scanf("%s",choice);

                    if(strcmp(strlwr(choice),"yes") != 0) {
                        Exit_statement();
                        break;
                    }

                }

                else if (action == 2) {

                    Change_IBAN_print();

                    char* New_IBAN = malloc(100 * sizeof(char));
                    char* placeholder_account2 = malloc((sizeof(All_Accounts[right_account])));

                    while(1){

                        scanf("%s",New_IBAN);

                        char verify_IBAN = 0;
                        verify_IBAN = check_IBAN(New_IBAN);


                        if (verify_IBAN == 1) {
                            strcpy(All_Accounts[right_account],change_IBAN(All_Accounts, placeholder_account2, New_IBAN, right_account));
                            printf("IBAN changed successfully\n");
                            break;
                        }

                        else if (verify_IBAN == 0) {
                            printf("That is an invalid IBAN! Please try again!\n");
                        }
                    }

                    free(New_IBAN);


                    Other_choice();

                    scanf("%s",choice);

                    if(strcmp(strlwr(choice),"yes") != 0) {
                        Exit_statement();
                        break;
                    }
                }

                else if (action == 3) {

                    Change_Currency_print();

                    char* New_currency = malloc(100 * sizeof(char));
                    char* placeholder_account3 = malloc(sizeof(All_Accounts[right_account]));
                    char* amount = malloc(sizeof(All_Accounts[right_account]));

                    while(1){

                        scanf("%s",New_currency);

                        char verify_currency = 0;
                        verify_currency = check_Currency(New_currency);

                        if(verify_currency == 1){
                            strcpy(amount, exchange_rate_Amount(All_Accounts[right_account],New_currency));
                            strcpy(All_Accounts[right_account], change_Amount(All_Accounts,placeholder_account3,amount,right_account));
                            strcpy(All_Accounts[right_account], change_Currency(All_Accounts,placeholder_account3,New_currency,right_account));

                            printf("Currency changed successfully!\n");
                            break;
                        }

                        else{
                            printf("this input is invalid! Please enter another input!\n");
                        }

                    }

                    free(New_currency);

                    Other_choice();

                    scanf("%s",choice);

                    if(strcmp(strlwr(choice),"yes") != 0)
                        break;
                }

                else if (action == 4) {
                    Change_Amount_print();

                    char* New_amount = malloc(100 * sizeof(char));
                    char* placeholder_account4 = malloc(sizeof(All_Accounts[right_account]));

                    scanf("%s",New_amount);
                    strcpy(All_Accounts[right_account], change_Amount(All_Accounts, placeholder_account4, New_amount,right_account));

                    printf("Amount changed successfully!");

                    Other_choice();

                    scanf("%s",choice);

                    if(strcmp(strlwr(choice),"yes") != 0) {
                        Exit_statement();
                        break;
                    }
                }

                else if (action == 5) {
                    Transactions_print();

                    int transaction_account = total_accounts + 1;

                    char* Transaction_IBAN = malloc(sizeof(All_Accounts[right_account]));
                    char* Transaction_amount = malloc(sizeof(All_Accounts[right_account]));
                    char* placeholder5 = malloc(sizeof(All_Accounts[right_account]) + 1);
                    char* Transaction_amount_copy = malloc(sizeof(All_Accounts[right_account]));

                    while(1){
                        scanf("%s",Transaction_IBAN);

                        for(int i = 0; i < total_accounts; i++) {

                            if (strcmp(Take_IBAN(All_Accounts[i]), Transaction_IBAN) == 0) {

                                transaction_account = i;
                                break;
                            }
                        }

                        if(transaction_account != total_accounts + 1 && transaction_account != right_account) {

                            while (1) {
                                printf("Account found! Please enter the amount that you want to transfer!\n");

                                scanf("%s", Transaction_amount);

                                if (strcmp(Take_Amount(All_Accounts[right_account]), Transaction_amount) < 0) {
                                    printf("You do not have enough money in your account in order to complete this transaction!\n");
                                    printf("Try entering a lower amount!\n");
                                }

                                else
                                    break;
                            }

                            strcpy(Transaction_amount_copy,Transaction_amount);

                            Transaction(All_Accounts,placeholder5,Transaction_amount,right_account,transaction_account);

                            strcpy(All_Accounts[right_account], change_Amount(All_Accounts,placeholder5,
                                                                              Remaining_Amount(All_Accounts[right_account],Transaction_amount_copy),right_account));


                            printf("Transaction made successfully!\n");
                            break;


                        }

                        else if(transaction_account == right_account){
                            printf("You cannot make a transaction into the same account! Try entering another IBAN!");
                        }

                        else{
                            printf("There is no account with that IBAN! Try entering another IBAN!");
                        }
                    }


                    Other_choice();

                    scanf("%s",choice);

                    if(strcmp(strlwr(choice),"yes") != 0) {
                        Exit_statement();
                        break;
                    }
                }

                else if(action == 6){

                    for(int i = 0; i < total_accounts; i++) {
                        if (i == total_accounts - 1)
                            strcpy(All_Accounts[i], "");

                        else if (i >= right_account)
                            strcpy(All_Accounts[i], All_Accounts[i + 1]);
                    }

                    Delete_Account_print();
                    break;
                }

                else if(action == 7){
                    Exit_statement();

                    break;
                }

                else {
                    Invalid_input();
                }

            }

        }
    }
    else if (strcmp("register",check_if_login_or_register(user_input)) == 0){
        printf("In order to register you need to provide an IBAN and the currency you want your account to have!\n");
        printf("Please enter a valid IBAN! Our IBANs follow the next structure: RO[4 digits][8 lowercase letters][4 uppercase letters]\n");

        char* Register_IBAN = malloc(100 * sizeof(char));
        char* Register_Currency = malloc(100 * sizeof(char));

        char verify_registered_IBAN = 0;
        char verify_registered_currency = 0;

        while(1){
            scanf("%s",Register_IBAN);

            verify_registered_IBAN = check_IBAN(Register_IBAN);

            if(verify_registered_IBAN == 0){
                printf("This is an invalid IBAN! Please try entering another input!\n");
            }

            else {
                printf("IBAN entered successfully!\n");
                break;
            }

        }

        while(1){
            printf("Please enter one of our accepted currencies (ron, dollars, euro, yen)!\n");

            scanf("%s",Register_Currency);

            verify_registered_currency = check_Currency(Register_Currency);

            if(verify_registered_currency == 0){
                printf("This is not an accepted currency! Please try entering another input!\n");
            }

            else {
                printf("Currency entered successfully!\n");
                break;
            }

        }

        char* Registered_Account = strcat(Eliminate_first_word(user_input),",");
        Registered_Account = strcat(Registered_Account,Register_IBAN);
        Registered_Account = strcat(Registered_Account,",");
        Registered_Account = strcat(Registered_Account,Register_Currency);
        Registered_Account = strcat(Registered_Account,",0");

        FILE* Add_account = fopen("E:\\Programming Project\\Bank_Accounts.txt", "a");
        fputs(Registered_Account, Add_account);
        fclose(Add_account);


    }

    if(total_accounts != 0){
        FILE* write_account = fopen("E:\\Programming Project\\Bank_Accounts.txt", "w");

        fprintf(write_account,header);

        fclose(write_account);

        FILE* print_accounts = fopen("E:\\Programming Project\\Bank_Accounts.txt", "a");

        for(int i = 0; i < total_accounts; i++){
            fputs(All_Accounts[i],print_accounts);
        }
        fclose(print_accounts);

    }


    for (int i = 0; i < nr_accounts_of_person; i++) {
        free(Same_Owner_accounts[i]);
    }



    free(All_Accounts);
    free(Same_Owner_accounts);
    free(file_line);
    free(header);
    free(user_input);
    fclose(Banking_Information);
    return 0;

}
