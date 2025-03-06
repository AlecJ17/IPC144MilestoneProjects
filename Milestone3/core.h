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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
//1st prototype
//Function: inputInt
//This function makes sure that the number that is entered and returned is
//an integer. If a wrong number is entered, an error message will show up.
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

// Function to input and validate a valid phone number
void inputPhoneNumber(char *phoneNumber);

// Function to check if a string contains only digits
int isAllDigits(const char *str);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
