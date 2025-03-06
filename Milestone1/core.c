/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Alec Josef Serrano
Student ID#: 133592238
Email      : ajserrano2@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include "core.h"
#define PHONE_NUM_DIGITS 10



// Clear the standard input buffer
void clearInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ;  // empty statement intentional
    }
}

void suspend(void)
{
    {
        printf("Press enter to continue ...");
        while (getchar() != '\n')
        {
            ;  // empty statement intentional
        }
    }
}

//Test-1
//This function must return a valid integer input from the keyboard
int inputInt(void)
{
    char newLine = 'x';
    int value = 0;
    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine == '\n')
        {
            return value;
        } else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');

}

//Test-2
// This function must return an integer value greater than 0.
int inputIntPositive(void)
{
    int input;
    do
    {
        scanf("%d", &input);
        clearInputBuffer();
        if (input <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (input <= 0);
    return input;
}

//Test-3 and Test-4
// This function must return an integer value within a specified range.
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

    return value;
}

//Test-5
// This function must return a single character
// value from a list of valid characters.
char inputCharOption(const char validChars[])
{
    char input;
    int validInput;
    int found, i;

    do
    {
        validInput = 0;  // Initialize as false
        found = 0;    // Initialize as false

        // Read a single character
        scanf("%c", &input);
        clearInputBuffer();

        // Check if the character is in the validChars list
        for (i = 0; validChars[i] != '\0' && !found; ++i)
        {
            if (input == validChars[i])
            {
                validInput = 1; // Set as true
                found = 1;   // Set as true
            }
        }

        if (!validInput)
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
    } while (!validInput);

    return input;

}
void inputCString(char* str, int min, int max) {
    int validInput;
    int length;
    char input[1500];  // Buffer for the format string


    do
    {
        validInput = 1; // true
        sprintf(input, "%%%d[^\n]", 1500);
        scanf(input, str); // read up to 1500 char for safety
        clearInputBuffer();
        // Calculate the length of the input
        length = 0;
        while (str[length] != '\0')
        {
            length++;
        }

        // If the input is too long, clear the input buffer
        if (length > 1500)
        {
            validInput = 0;
            clearInputBuffer();
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

void displayFormattedPhone(const char *phoneNumber)
{
    int validInput = 1; // Assume the phone number is valid initially
    int i;
    const char* digits = "0123456789"; // String containing all digits

    // Check if phoneNumber is NULL
    if (phoneNumber == NULL)
    {
        validInput = 0;
    }
    else
    {
        // Validate that the string has exactly 10 digits
        for (i = 0; i < PHONE_NUM_DIGITS && validInput; i++)
        {
            if (strchr(digits, phoneNumber[i]) == NULL)
            {
                validInput = 0; // If not a digit
            }
        }

        // Check for string termination after 10 digits
        if (validInput && phoneNumber[i] != '\0')
        {
            validInput = 0;
        }
    }

    // If the phone number is valid, print it in the formatted style
    if (validInput)
    {
        printf("(%.3s)%.3s-%.4s", &phoneNumber[0], &phoneNumber[3], &phoneNumber[6]);
    }
    else
    {
        // Print a placeholder if the input is invalid
        printf("(___)___-____");
    }
}