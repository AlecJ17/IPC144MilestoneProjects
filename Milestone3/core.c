/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Alec Josef Serrano
Student ID#: 133592238
Email      : ajserrano2@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "core.h"
#define PHONE_NUM_DIGITS 10
//Macro for array size protection
#define MAX_CHAR_INPUT 1500
//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
//Test-1
//This function makes sure that the number that is entered and returned
// is an integer. If a wrong number is entered, an error message will show up.
int inputInt(void)
{
    char newLine = 'x';
    int value = 0;
    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');

    //If the character next to the integer input is a newline character, valid
    //input was entered
    return value;
}

//Test-2
// This function must return an integer value greater than 0.
int inputIntPositive(void)
{
    int value;
    do
    {
        scanf("%d", &value);
        clearInputBuffer();
        if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);

    //returns the value after the validation
    return value;
}

//Test-3 and Test-4
//This function must return an integer value within a
//specified range and return the value. If invalid value inputted
//show the appropriate error message and continue until receiving valid input
int inputIntRange(int lowerBound, int upperBound)
{
    int value;
    int validInput;
    do
    {
        validInput = 1;
        value = inputInt();
        if (value < lowerBound || value > upperBound)
        {
            validInput = 0;
            printf("ERROR! Value must be between %d and %d inclusive: "
                    , lowerBound, upperBound);
        }
    } while (!validInput);
    //Return the value after the validation
    return value;
}

//Test-5
// This function must return a single character value
//from a list of valid characters and return after validation.
char inputCharOption(const char validChars[])
{
    int validInput, i, displayError;
    char input, newline = ' ';

    do
    {
        validInput = 1;
        displayError = 0;

        if (newline != '\n')
        {
            scanf("%c%c", &input, &newline);

            if (newline == '\n')
            {
                for (i = 0; validChars[i] != '\0'; i++ )
                {
                    if (input != validChars[i] && newline != '\n')
                    {
                        displayError = 0;
                    }
                    else
                    {
                        displayError = 1;
                    }
                }
            }
            else
            {
                displayError = 0;
                validInput = 0;
                clearInputBuffer();
            }

            if (displayError == 0)
            {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        }
    } while (!validInput);

    return input;
}

// This function is to obtain user input for a C string value with a length
// (number of characters) in the character range specified by the arguments.
void inputCString(char* str, int min, int max)
{
    int validInput;
    int length;
    char input[MAX_CHAR_INPUT + 1];  // Buffer for the format string

    do
    {
        validInput = 1; // true
        sprintf(input, "%%%d[^\n]", MAX_CHAR_INPUT + 1);
        scanf(input, str); // read up to 1500 char for safety
        clearInputBuffer();
        // Calculate the length of the input
        length = 0;
        while (str[length] != '\0')
        {
            length++;
        }
        // If the input is too long, clear the input buffer
        if (length > MAX_CHAR_INPUT + 1)
        {
            validInput = 0;
        }
        else
        {
            // Check if the length is within the allowed range
            if (min == max && length != min)
            {
                validInput = 0;
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (length > max)
            {
                validInput = 0;
                printf("ERROR: String length must be no more than %d chars: "
                                                                        , max);
            }
            else if (length < min)
            {
                validInput = 0;
                printf("ERROR: String length must be between %d and %d chars: "
                                                                   , min, max);
            }
            else
            {
                validInput = 1;
            }
        }
    } while (!validInput);
}

// This function is to display an array of
//10-character digits as a formatted phone number.
void displayFormattedPhone(const char *phoneNumber)
{
    int validInput = 1; // Assume the phone number is valid initially
    int i;
    const char *digits = "0123456789"; // String containing all digits

    // Check if phoneNumber is NULL or empty
    if (phoneNumber == NULL || phoneNumber[0] == '\0')
    {
        validInput = 0;
    } else
    {
        // Validate that the string has exactly 10 digits
        for (i = 0; i < PHONE_NUM_DIGITS && validInput; i++)
        {
            if (!strchr(digits, phoneNumber[i]))
            {
                validInput = 0;
            }
        }
        // Ensure the string is terminated correctly after 10 digits
        if (phoneNumber[PHONE_NUM_DIGITS] != '\0')
        {
            validInput = 0;
        }
    }

    // If the phone number is valid, print it in the formatted style
    if (validInput)
    {
        printf("(%.3s)%.3s-%.4s", phoneNumber, phoneNumber + 3, phoneNumber + 6);
    }
    else
    {
        // Print a placeholder if the input is invalid
        printf("(___)___-____");
    }
}

// Function to input and validate a valid phone number
void inputPhoneNumber(char *phoneNumber)
{
    int validInput = 0; // Initialize the flag to indicate invalid input
    char input[MAX_CHAR_INPUT + 1];

    do
    {
        sprintf(input, "%%%ds", MAX_CHAR_INPUT);
        scanf(input, input);
        clearInputBuffer();
        if (strlen(input) == PHONE_NUM_DIGITS && isAllDigits(input))
        {
            validInput = 1;
            strcpy(phoneNumber, input);
        }
        else
        {
            printf("Invalid %d-digit number! Number: ", PHONE_NUM_DIGITS);
        }
    } while (!validInput);
}

// Function to check if a string contains only digits
int isAllDigits(const char *str)
{
    int allDigits = 1;
    while (*str && allDigits)
    {
        if (!isdigit(*str))
        {
            allDigits = 0;
        }
        str++;
    }
    return allDigits;
}