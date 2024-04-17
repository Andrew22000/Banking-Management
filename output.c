#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "File_handling.h"
#include "output.h"
void Welcome_statement() {
    printf("Welcome to Horizon Trust Bank! In order to login into your account please enter the command 'login [NAME] [SURNAME]'\n");
    printf("If you want to register please enter the command 'register [NAME] [SURNAME]\n");
}

void Only_one_account_output(char **array) {
    printf("User logged in successfully!\nThis is your account!\n");
    printf("%s\n\n",array[0]);
}

void Account_choices() {
    printf("What action do you want to take next? (Enter the number corresponding to the action you want to take)\n");
    printf("1.View Amount                  2.Change IBAN\n");
    printf("3.Change Currency              4.Change Amount\n");
    printf("5.Make transaction             6.Delete account\n");
    printf("7.Exit\n");
}

void More_accounts_output(char **array,int nr_accounts) {
    printf("User logged in successfully! These are your accounts!\n");
    for(int i = 0; i < nr_accounts; i++){
        printf("%d.%s",i+1,array[i]);
    }
    printf("Please enter the number corresponding to the account you want to work in!\n");
}

void Print_amount(char *array) {
    printf("You have %s %s in your account!\n", Take_Amount(array), Take_Currency(array));
}

void Change_IBAN_print() {
    printf("In order to change your IBAN you need to enter a valid input.\n");
    printf("Our IBANs follow the next structure: RO[4 digits][8 lowercase letters][4 uppercase letters]\n");
    printf("Please enter a valid input!\n");
}

void Change_Currency_print() {
    printf("In order to change your currency you need to enter a currency accepted at our bank (ron, dollars, euro or yen)!\n");
}

void Change_Amount_print() {
    printf("Please enter the new amount desired!\n");
}

void Transactions_print() {
    printf("In order to perform a transaction you need to provide the IBAN of the account that you want to transfer money to\n");
    printf("Please enter the corresponding IBAN!\n");
}

void Exit_statement() {
    printf("Thank you for choosing Horizon Trust Bank! Have a nice day!");
}

void Invalid_input() {
    printf("This is not a valid input! Please enter another number!");
}

void Other_choice() {
    printf("Do you want to do anything else? If yes, please enter 'yes'. If no, enter any other input!\n");
}

void Delete_Account_print() {
    printf("Account deleted successfully!\n");
    printf("Thanks for choosing Horizon Trust Bank!\n");
}



