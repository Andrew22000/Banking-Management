#include <stdio.h>

/**
 * gets the Name and Surname from the owner's account
 * @param file_line the owner's banking information stored on that line in the file
 * @return the Name and Surname of the account's owner
 */
char* Take_Name_Surname(const char* file_line);

/**
 * gets the IBAN from the owner's account
 * @param file_line the owner's banking information stored on that line in the file
 * @return the IBAN of the account's owner
 */
char* Take_IBAN(const char* file_line);

/**
 * gets the Currency from the owner's account
 * @param file_line the owner's banking information stored on that line in the file
 * @return the Currency of the account's owner
 */
char* Take_Currency(const char* file_line);

/**
 * gets the Amount stored in the owner's account
 * @param file_line the owner's banking information stored on that line in the file
 * @return the Amount stored in the owner's account
 */
char* Take_Amount(char* file_line);


