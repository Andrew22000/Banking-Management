#include <stdio.h>

/**
 * checks if a given string is an IBAN
 * @param command The given IBAN
 * @return 1 if the string is a valid IBAN, 0 else
 */

char check_IBAN(char *command);

/**
 * removes spaces at the beginning and end of a given string
 * @param string the given string
 * @return  returns the string without spaces
 */

char check_Currency(char* Currency);

char* strstrip(char* input_string);

/**
 * allows you to view your account data
 * @param IBAN is your account's IBAN
 * @param amount represents the amount of money that you have in your account
 */
void view_data(char* name_surname);
/**
 * logs your account into the console
 * @param input the input given
 * @return 1 if login is valid and 0 otherwise
 */
int login(char* input);

/**
 * it eliminates the first word from an input
 * @param input the given input
 * @return the rest of the input without the first word
 */
char* Eliminate_first_word(char* input);

/**
 * Opens a file
 * @param file_path path
 * @param mode mode of operations
 * @return file
 */
FILE *open_file(const char *file_path, const char *mode);

/**
 * finds the first word in a given command
 * @param command the command given
 * @return the first word
 */
char* check_if_login_or_register(char *command);

/**
 * puts the given account into an array of accounts with the same owner on the given position
 * @param array_of_accounts The array that holds the accounts
 * @param account The account that must be put into the array
 * @param pos The position that the account must be inserted on
 * @return the array of accounts
 */
char* Add_Account(char* array_of_accounts,char* account);

char* change_IBAN(char** Array, char* placeholder, const char* IBAN, int right_account);

char* change_Currency(char** Array,char* placeholder,const char* New_currency,int right_account);

char* exchange_rate_Amount(const char* account, char* new_currency);

char* change_Amount(char** Array, char* placeholder, const char* New_amount, int right_account);

char* Remaining_Amount(char* account,char* Amount);

char* Transaction(char** Array,char* placeholder, const char* Amount, int right_account, int transaction_account);

double Take_Amount_as_Double(char* account);






