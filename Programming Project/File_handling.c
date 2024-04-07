#include "File_handling.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *Take_Name_Surname(const char *file_line) {
    char* Name_Surname = (char*)malloc(sizeof(file_line));

    int k = 0;

    for(int i = 0; i < strlen(file_line); i++) {

        if (file_line[i] != ','){
            Name_Surname[k] = file_line[i];
            k++;
        }

        else
        {
            Name_Surname[k] = '\0';
            return Name_Surname;
        }
    }

}


char *Take_IBAN(const char *file_line) {
    char *IBAN = (char *) malloc(sizeof(file_line));

    int k = 0;

    for (int i = 0; i < strlen(file_line); i++) {

        if (file_line[i] == ',') {

            for (int j = i; j < strlen(file_line); j++) {

                if (file_line[j] != ',') {

                    IBAN[k] = file_line[j];
                    k++;
                }
                else {
                    IBAN[k] = '\0';
                    return IBAN;
                }
            }
        }
    }
}


char *Take_Currency(const char *file_line) {
    char* Currency = (char*)malloc(sizeof(file_line));

    int k = 0, comma_nr = 0;

    for(int i = 0; i < strlen(file_line); i++){

        if(file_line[i] == ','){
            comma_nr++;

            if(comma_nr == 2){

                for(int j = i + 1; j < strlen(file_line); j++) {

                    if (file_line[j] != ',') {
                        Currency[k] = file_line[j];
                        k++;
                    } else {
                        Currency[k] = '\0';
                        return Currency;
                    }
                }
            }
        }
    }
}


char *Take_Amount(char *file_line) {
    char* Amount = (char*)malloc(sizeof(file_line));

    int k = 0, comma_nr = 0;

    for(int i = 0; i < strlen(file_line); i++){

        if(file_line[i] == ','){
            comma_nr++;

            if(comma_nr == 3){

                for(int j = i + 1; j < strlen(file_line); j++) {

                    Amount[k] = file_line[j];
                    k++;
                }

                Amount[k] = '\0';
                return Amount;
            }
        }
    }
}


