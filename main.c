/*

Author:			Dylan Hussain
Description:	This program is a menu based Lotto game.
                The menu will prompt the user to select
                6 options, each option is function driven.
                Options 2 - 5 cannot be selected until
                option 1 has been selected. The amount of
                times a user enters a number when guessing
                the lotto numbers is tracked. The first
                option is to input the user lotto number
                guess. The second option displays the numbers
                that the user entered seperated by commas.
                The third option sorts the guess that the 
                user entered using the insertion sort
                alogrithm. The fourth option is to check
                the numbers guessed with the winning lotto
                numbers, depending on how many matches they
                have it will display along with any winnings.
                The fifth option displays the frequency
                of how many times a certain number was inputted.
                The sixth option will allow the user to exit the
                program.

Date:			02/03/22

*/

#define MAX_GUESS           42
#define STRING_BUFFER       100
#define MAX_NUMBER_SIZE     6

#define PREFIX_ERROR        "[ERROR]"
#define PREFIX_OUTPUT       "[OUTPUT]"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void display_menu(void);

int get_number_frequency(int, int*);
void handle_menu_input(int, int*, int*, int*);
void increment_number_frequency(int, int*);
void perform_number_guess(int*, int*);
void perform_display_guess(int*);
void perform_sort_guess(int*);
void display_frequency(int*, int*);
void check_matching(int*);
void validate_input(int*);
void exit_program(int*);

void convert_string_upper(char*);
void output_err(char*);

const int WINNING_NUMBERS[MAX_NUMBER_SIZE] = {1, 3, 5, 7, 9, 11};

int main()
{
    int has_exited = 0; // Stores whether or not the program has exited.
    int user_number_guess[MAX_NUMBER_SIZE] = { 0 }; // Stores the users' lotto numbers.
    int guess_frequency[MAX_GUESS] = { 0 }; // Contains the frequency of each number that gets entered.
    int user_input; // Stores the users integer input accross the program.

    while (has_exited == 0)
    {
        /*
        *   This will loop through the game
        *   until the user decides to exit
        */

        display_menu();
        validate_input(&user_input);
        handle_menu_input(user_input, &has_exited, user_number_guess, guess_frequency);
    } // end while

    return 0;

} // end main()
void display_menu()
{
    /*
    *   Displays a menu system with 6 options
    *   on it, options 2, 3, 4, 5 can only be
    *   selected when option 1 has been selected.
    */

    printf("\n%-5s%-24s%20s\n\n", "", "1. Take Guess", "2. Display Guess");
    printf("%-5s%-24s%20s\n\n", "", "3. Sort Guess", "4. Check Numbers");
    printf("%-5s%-23s%20s\n\n", "", "5. Display Frequency", "6. Exit Program");

} // end display_menu()
int get_number_frequency(int target, int* array)
{
    /*
    *   This function returns the target
    *   value in the given frequency array.
    */

    return *(array + target - 1);
    
} // end get_number_frequency()
void handle_menu_input(int option, int* has_exited, int* user_number_guess, int* guess_frequency)
{
    /*
    *    This function handles which option
    *    the user selects from the menu.
    *    It validates the input to ensure
    *    that it is a valid option and then
    *    it will call the options function.
    */

    if (option == 1)
        perform_number_guess(user_number_guess, guess_frequency);
    else if (option == 6)
        exit_program(has_exited);
    else if (option >= 2 && option <= 5)
    {   
        /*
        *   If option is between 2 and 5 make sure
        *   they entered the number first.
        */ 

        if (*(user_number_guess) == 0)
            output_err("You must enter in a number first, please try again");
        else if (option == 2)
            perform_display_guess(user_number_guess);
        else if (option == 3)
            perform_sort_guess(user_number_guess);
        else if (option == 4)
            check_matching(user_number_guess);
        else if (option == 5)
            display_frequency(user_number_guess, guess_frequency);
        // end if
    }
    else
    {
        output_err("This number is not an option in the menu, please try again.");
    } // end if 

} // end handle_menu_input()
void increment_number_frequency(int target, int* array)
{
    /*
    *   This function returns the increments
    *   the target index in the given frequency
    *   array.
    */

    *(array + target - 1) += 1;

} // end increment_number_frequency()
void perform_number_guess(int* user_number_guess, int*guess_frequency)
{
    /*
    *   This function prompts the user to enter
    *   6 numbers which they think will be the
    *   winning lotto numbers.
    */
   
    int guessed_numbers[MAX_GUESS] = { 0 };
    int user_input = 0;
    int i = 0;
    
    printf("\n%-15sEnter in 6 numbers (1-42).\n\n", PREFIX_OUTPUT);
    
    /*
    *   Prompt the user to enter a set of 6 numbers
    *   and validate the input to ensure it follows
    *   the guidelines.
    */
    do {

        printf("\n%-15sEnter number #%d.\n\n", PREFIX_OUTPUT, i + 1);
        validate_input(&user_input);

        if ((user_input <= 0 || user_input > MAX_GUESS))
        {
            output_err("Please enter a number within range (1-42), please try again");
        } else if (get_number_frequency(user_input, guessed_numbers) != 0) {
            output_err("That number has already been guessed, please try again");
        } else {
            *(user_number_guess + i) = user_input;
            increment_number_frequency(user_input, guessed_numbers);
            increment_number_frequency(user_input, guess_frequency);
            i++;
        } // end if

    } while (i < MAX_NUMBER_SIZE); // end do while
} // end perform_number_guess()
void perform_display_guess(int * user_number_guess)
{
    /*
    *   This function displays the users guessed
    *   lotto numbers, seperated by commas.
    */

    printf("\n%-15s", PREFIX_OUTPUT);

    for (int i = 0; i < MAX_NUMBER_SIZE; i++)
    {
        // If the number isn't the last number add a comma
        if (i < MAX_NUMBER_SIZE - 1)
        {
            printf("%d, ", *(user_number_guess + i) );
        } 
        else
        {
            printf("%d", *(user_number_guess + i) );
        } // end if

    } // end for

    printf("\n");

} // end perform_display_guess()
void perform_sort_guess(int * user_number_guess)
{   
    /*
    *   The insertion sort algorithm is used
    *   here because the list is short.
    *   If the unsorted index value is greater
    *   than the current index value we place 
    *   it on the right, else we place it on
    *   the left.
    */

    int current;
    int j = 0;
    
    // Loop through array
    for(int i = 1 ; i < MAX_NUMBER_SIZE ; i++)
    {
        current = *(user_number_guess + i );
        j = i - 1;

        // compare an element to previous element
        while(j >= 0 && current < *(user_number_guess + j))
        {
            *(user_number_guess + j + 1 ) = *(user_number_guess + j);
            j--;
        } // end while

        *(user_number_guess + j + 1 ) = current;

    } // end for

    printf("\n%-15sYou sorted the array.\n\n", PREFIX_OUTPUT);

} // end perform_sort_guess()
void display_frequency(int * user_number_guess, int * guess_frequency)
{
    /*
    *   This function displays the frequency
    *   of how many times the numbers that
    *   have been guessed.
    */

    int frequency;

    for (int i = 0; i < MAX_NUMBER_SIZE; i++)
    {
        // Get the frequency of the given number
        frequency = get_number_frequency(*(user_number_guess + i), guess_frequency);
        
        if (frequency > 0)
        {
            printf("\n%-15sNumber %d has been selected %d times.\n", PREFIX_OUTPUT, *(user_number_guess + i), frequency);
        } // end if

    } // end for

    printf("\n");

} // end display_frequency()
void check_matching(int * user_number_guess)
{
    /*
    *   This function checks the users lotto
    *   number guess with the winning numbers
    *   and it outputs any possible winnings
    *   depending on the amount of numbers matched.
    */

    int match_count = 0;

    for (int i = 0; i < MAX_NUMBER_SIZE; i++)
    {
        /*
        *   Loop through the users' guessed lotto
        *   numbers and compare it to the winning
        *   lotto numbers. If they match it will
        *   count it and keep track of it.
        */
       for (int j = 0; j < MAX_NUMBER_SIZE; j ++)
        {
            if (*(user_number_guess + i) == *(WINNING_NUMBERS + j))
                match_count++;
            // end if
            
        } // end for


    } // end for

    if (match_count >= 3) {
        /*
        *   If the user guessed enough winning
        *   numbers then output what they won.
        */

        printf("%-15sCongratulations you match %d and won ", PREFIX_OUTPUT, match_count);

        switch(match_count)
        {
            case 3:
                printf("a Cinema Pass");
                break;
            case 4:
                printf("a Weekend Away");
                break;
            case 5:
                printf("a New Car");
                break;
            case 6:
                printf("the Jackpot!");
                break;
        } // end switch

        printf("\n\n");

    } else {
        /* 
        *   If the user doesn't guess enough let
        *   them know that they won nothing
        */

        printf("\n%-15sUnfortunately, you match %d and won nothing.\n\n", PREFIX_OUTPUT, match_count);
    } // end if

} // end check_matching()
void validate_input(int *output)
{
    /*
    *    This function checks for valid numeric
    *    value input, it will loop until a
    *    valid numeric value passed through and
    *    then it will set the passed in param
    *    as the valid input once entered.
    */

    int valid_input = 0;

    do 
    {
        // Prompt the user to input a value.
        printf("> ");

        if (!scanf("%d", output))
        {
            /*
            *   If the user enters a character, let
            *   them know they need to enter a numeric value.
            */

            output_err("You must enter a numeric value, please try again.");
            fflush(stdin);
        } else {
            // If they enter a valid numeric value, they exit the loop
            valid_input = 1;
        } // end if

    } while (valid_input == 0); // end do while
} // end validate_input()
void exit_program(int * has_exited)
{
    /*
    *   This function prompts the user to 
    *   ensure they want to exit the program,
    *   which will help in case the user
    *   accidentally presses the exit option.
    */ 

    char user_input[STRING_BUFFER];

    fflush(stdin); // Flushes the input buffer so no unwanted input is captured.

    do {
        /*
        *   Prompts a message to the user to ask
        *   for input and loops until the input
        *   is valid.
        */ 

        printf("\n%-15sAre you sure you want to exit the program? (Y)es or (N)o.\n\n", PREFIX_OUTPUT);
        printf("> ");

        /*
        *   The space before the delimiter tells
        *   the program to ignore the newline.
        *   scanf is being used in this case as
        *   fgets was causing issues with strcmp
        *   not working as expected.
        */

        if (scanf(" %s", user_input)) {

            convert_string_upper(user_input);

            if (strcmp(user_input, "Y") == 0)
            {
                // Setting this to 1 will prevent the game from looping in main() 
                *has_exited = 1; 
            }
            else if (strcmp(user_input, "N") == 0)
            {
                // Exit out of the function as the user has decided not to leave the program.
                return;
            }
            else
            {
                // The user entered a value other than Y or N, so prompt the user to try again.
                printf("\n");
                output_err("You did not enter Y or N, please try again.");
            } // end if 

        } // end if

    } while (*has_exited == 0); // end do while
} // end exit_program()
void convert_string_upper(char *str)
{
    /*
    *   This function loops through a given
    *   string until it finds the null character
    *   and will convert each char to uppercase.
    */

    int i = 0;
    do
    {
        *(str + i) = toupper(*(str + i));
        i++;
    } while (*(str + i) != '\0'); // end do while

} // end convert_string_upper()
void output_err(char *str)
{
    /*
    *   This function outputs a formatted
    *   error message with a prefix attached to it.
    */

    printf("\n%-15s%s\n\n", PREFIX_ERROR, str);

} // end output_err()