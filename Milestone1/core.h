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
#include <string.h>

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//1st prototype
//Function: inputInt
//This function must return a valid integer input from the keyboard
int inputInt(void);

// 2nd prototype
// Function: inputIntPositive
// This function must return an integer value greater than 0.
int inputIntPositive(void);

//3rd prototype
// This function must return an integer value within a specified range.
int inputIntRange(int lowerBound, int upperBound);


//4th prototype
// This function must return a single character value from a list of valid characters.
char inputCharOption(const char validChars[]);

//5th prototype
// This function is to obtain user input for a C string value with a length
// (number of characters) in the character range specified by the arguments.
void inputCString(char* str, int min, int max);

//6th prototype
// This function is to display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char *phoneNumber);
