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
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int found = 0;
    int i;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            found = 1;
        }
    }

    if (!found)
    {
        printf("*** No records found ***\n\n");
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int choice;
    do
    {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");

        choice = inputIntRange(0, 2);

        switch (choice)
        {
            case 1:
                searchPatientByPatientNumber(patient, max);
                break;
            case 2:
                searchPatientByPhoneNumber(patient, max);
                break;
            case 0:
                putchar('\n');
                break;
        }
    } while (choice != 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int index = -1; // Initialize the index to -1 as an indicator
    int newPatientNumber;
    int foundAvailableIndex = 0;
    int i;

    // Find an available index with a patient number of 0
    for (i = 0; i < max && !foundAvailableIndex; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i;
            foundAvailableIndex = 1;
        }
    }

    if (!foundAvailableIndex)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        newPatientNumber = nextPatientNumber(patient, max);

        patient[index].patientNumber = newPatientNumber;

        inputPatient(&patient[index]);

        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int patientNumber, i;
    int patientIndex = -1;
    int found = 0;

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    putchar('\n');

    for (i = 0; i < max && !found; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            findPatientIndexByPatientNum(patientNumber, patient, i);
            patientIndex = i;
            found = 1;
        }
    }

    if (found)
    {
        menuPatientEdit(&patient[patientIndex]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNumber, i;
    int patientIndex = -1;
    int found = 0;
    char selection;

    printf("Enter the patient number: ");

    patientNumber = inputIntPositive();
    putchar('\n');
    for (i = 0; i < max && !found; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            findPatientIndexByPatientNum(patientNumber, patient, i);
            patientIndex = i;
            found = 1;
        }
    }

    if (found)
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);

        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn");
        if (selection == 'y')
        {
            // Set the patient information to a safe empty state
            patient[patientIndex].patientNumber = 0;
            strcpy(patient[patientIndex].name, "");
            strcpy(patient[patientIndex].phone.description, "");
            strcpy(patient[patientIndex].phone.number, "");
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;

    // Sorting the data in the array
    sortData(data->appointments, data->maxAppointments);

    // Displaying the patients
    displayScheduleTableHeader(NULL, 1);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber &&
                      data->patients[j].patientNumber)
            {
                if (data->appointments[i].patientNumber ==
                          data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j],
                                        &data->appointments[i], 1);
                }
            }
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int lastDay;
    int i, j;
    struct Date date;

    printf("Year        : ");
    date.year = inputIntPositive();

    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);


    if (date.month == 4 || date.month == 9 || date.month == 11)
    {
        lastDay = 30;
    }
    else if (date.month == 2)
    {
        if ((date.year % 4 == 0 && date.year % 100 != 0) ||
                                     (date.year % 400 == 0))
        {
            lastDay = 29;
        }
        else
        {
            lastDay = 28;
        }
    }
    else
    {
        lastDay = 31;
    }
    printf("Day (1-%d)  : ", lastDay);

    date.day = inputIntRange(1, lastDay);
    putchar('\n');

    // Sorting the data in the array
    sortData(data->appointments, data->maxAppointments);

    // Displaying the patients
    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber &&
                       data->patients[j].patientNumber)
            {
                if (data->appointments[i].patientNumber ==
                          data->patients[j].patientNumber)
                {
                    if (data->appointments[i].date.year == date.year &&
                        data->appointments[i].date.month == date.month &&
                        data->appointments[i].date.day == date.day) {
                        displayScheduleData(&data->patients[j],
                                            &data->appointments[i], 0);
                    }
                }
            }
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment *app, int maxAppointments,
                    struct Patient *pt, int maxPatients)
{
    struct Date date;
    struct Time time;
    int lastDay = 31; // Initialize the last day of the month to 31.
    int patientNumber, index, slotNotAvailable = 1;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);

    if (index >= 0)
    {
        while (slotNotAvailable)
        {
            printf("Year        : ");
            date.year = inputIntPositive();

            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            printf("Day (1-");
            if (date.month == 4 || date.month == 9 || date.month == 11)
            {
                lastDay = 30;
            }
            else if (date.month == 2)
            {
                lastDay = 28;
            }
            else if (date.year % 4 == 0 && date.month == 2)
            {
                lastDay = 29;
            }
            printf("%d)  : ", lastDay);
            date.day = inputIntRange(1, lastDay);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            // Checking whether the time slot is available
            if (timeSlotAvailable(date, time, app, maxAppointments))
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else
            {
                while ((time.hour < START_HR || time.hour > END_HR) ||
                       (time.hour == END_HR && time.min > 0) ||
                       (time.min % MINUTE_INTERVAL != 0))
                {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in "
                                  "%02d minute intervals.\n\n",START_HR, END_HR,
                                                               MINUTE_INTERVAL);

                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                slotNotAvailable = 0;
            }
        }

        // Assigning the values to the next available slot
        index = nextSlotAvailable(app, maxAppointments);
        app[index].date = date;
        app[index].time = time;
        app[index].patientNumber = patientNumber;
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment *app, int maxAppointments,
                                struct Patient *pt, int maxPatients)
{
    struct Date date;
    int index, patientNumber, lastDay = 0, appointmentIndex;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);

    if (index >= 0)
    {
        printf("Year        : ");
        date.year = inputIntPositive();

        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        if (date.month == 4 || date.month == 9 || date.month == 11)
        {
            lastDay = 30;
        }
        if (date.month == 2)
        {
            lastDay = 28;
        }
        if (date.year % 4 == 0 && date.month == 2)
        {
            lastDay = 29;
        }
        printf("Day (1-");
        printf("%d)  : ", lastDay);
        date.day = inputIntRange(1, lastDay);

        appointmentIndex = validAppointment(patientNumber, date, app, maxAppointments);

        if (appointmentIndex >= 0)
        {
            printf("\n");
            displayPatientData(&pt[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y')
            {
                app[appointmentIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }
            else
            {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber, i;
    // Initialize 'patientIndex' to -1 to indicate not found
    int patientIndex = -1;
    int found = 0;

    printf("\nSearch by patient number: ");

    patientNumber = inputIntPositive();
    for (i = 0; i < max && !found; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            findPatientIndexByPatientNum(patientNumber, patient, i);
            patientIndex = i;
            found = 1;
        }
    }

    if (found)
    {
        putchar('\n');
        displayPatientData(&patient[patientIndex], FMT_FORM);
    }
    else
    {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char patientPhoneNumber[PHONE_LEN + 1];
    int found = 0;
    int i;

    printf("\nSearch by phone number: ");
    inputCString(patientPhoneNumber, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, patientPhoneNumber) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int highestNumber = 0;
    int i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > highestNumber)
        {
            highestNumber = patient[i].patientNumber;
        }
    }

    return highestNumber + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    int index = -1; // Return -1 if not found

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            index = i;
        }
    }
    return index;
}

// Function to sort the values using bubble sort
void sortData(struct Appointment appoints[], int arrSize)
{
    int i, j, minIdx;
    struct Appointment temp = {0};

    for (i = 0; i < arrSize; i++)
    {
        minIdx = i; // set the smallest to compare against for this iteration

        for (j = i + 1; j < arrSize; j++)
        {
            if(compareDateTime(&appoints[j], &appoints[minIdx]) < 0)
            {
                minIdx = j;
            }
        }
        //Code for swap!
        if (minIdx != i)
        {
            temp = appoints[i];
            appoints[i] = appoints[minIdx];
            appoints[minIdx] = temp;
        }
    }
}

//Compare two dates and times values
int compareDateTime(const struct Appointment* appoints1,
                    const struct Appointment* appoints2)
{
    int result = 0;
    int date1 = appoints1->date.year * 10000 + appoints1->date.month * 100
                                             + appoints1->date.day;
    int date2 = appoints2->date.year * 10000 + appoints2->date.month * 100
                                             + appoints2->date.day;
    int time1 = appoints1->time.hour * 60 + appoints1->time.min;
    int time2 = appoints2->time.hour * 60 + appoints2->time.min;

    if (!((date1 == date2) && (time1 == time2)))
    {
        if (date1 < date2)
        {
            result = -1;
        }
        else if (date1 > date2)
        {
            result = 1;
        }
        else if (time1 < time2)
        {
            result = -1;
        }
        else
        {
            result = 1;
        }
    }

    return result;
}

// Checks to see whether a time slot is available
int timeSlotAvailable(struct Date date, struct Time time,
                      struct Appointment* appoints, int maxAppointments)
{
    int i, slotAvailable = 0;

    for (i = 0; i < maxAppointments; i++)
    {
        // Checking if the time slot is available
        if (date.year == appoints[i].date.year && date.month == appoints[i].date.month &&
            date.day == appoints[i].date.day && time.hour == appoints[i].time.hour &&
            time.min == appoints[i].time.min)
        {
            slotAvailable = 1;
        }
    }

    return slotAvailable;
}

// Checks to see which is the next slot that is available and returns the index
int nextSlotAvailable(struct Appointment* appoints, int maxAppointments)
{
    int i = 0, available = 0;

    while (available == 0 && i < maxAppointments)
    {
        if (appoints[i].patientNumber < 1)
        {
            available = 1;
        }
        i++;
    }
    return i;
}

// Checks to see if an appointment is valid
int validAppointment(int patientNumber, struct Date date,
                     struct Appointment *appoints, int maxAppointments)
{
    int i = 0, validAppt = 0;

    do
    {
        if ((appoints[i].patientNumber == patientNumber) &&
            (appoints[i].date.day == date.day) &&
            (appoints[i].date.month == date.month) &&
            (appoints[i].date.year == date.year))
        {
            validAppt = 1;
        }
        i++;
    } while (validAppt == 0 && i < maxAppointments);
    i--;

    return i;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
           "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, MIN_NAME_LEN, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);

}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int option;
    char contactNumber[PHONE_LEN + 1];
    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");

    option = inputIntRange(1, 4);

    switch (option)
    {
        case 1:
            printf("\nContact: CELL\n"
                   "Number : ");
            inputPhoneNumber(contactNumber);
            strcpy(phone->description, "CELL");
            strcpy(phone->number, contactNumber);
            break;
        case 2:
            printf("\nContact: HOME\n"
                   "Number : ");
            inputPhoneNumber(contactNumber);
            strcpy(phone->description, "HOME");
            strcpy(phone->number, contactNumber);
            break;
        case 3:
            printf("\nContact: WORK\n"
                   "Number : ");
            inputPhoneNumber(contactNumber);
            strcpy(phone->description, "WORK");
            strcpy(phone->number, contactNumber);
            break;
        case 4:
            strcpy(phone->description, "TBD");
            strcpy(phone->number, " ");
            break;
    }
    putchar('\n');
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile,
                   struct Patient patients[],int max)
{
    int i = 0;
    int valid;

    // Opening the file
    FILE *fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        valid = 0;
        i = 0;

        while (!valid && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber,
                      patients[i].name,
                      patients[i].phone.description,
                      patients[i].phone.number) != EOF)
        {
            i++;
            if (i >= max)
                valid = 1;
        }
        fclose(fp);
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile,
                       struct Appointment appoints[], int max)
{
    int i, count = 0;

    // Opening the file
    FILE *fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        for (i = 0; i < max && !feof(fp); i++)
        {
            // Reading values from the file and storing them
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber,
                   &appoints[i].date.year, &appoints[i].date.month,
                   &appoints[i].date.day, &appoints[i].time.hour,
                   &appoints[i].time.min);

            if (!feof(fp))
            {
                count++;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    return count;
}


