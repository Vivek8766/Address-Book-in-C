#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validation.h"


// Validate name
int validate_name(char *str)
{
    // Check each character
    for (int i = 0; str[i] != '\0'; i++)
    {
        // Only alphabets and spaces allowed
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ')
        {
            printf(RED"⚠️  Name should contain only alphabets.\n"RESET);
            return 0;
        }
    }

    return 1;
}

// Validate phone number
int validate_phone(AddressBook *addressBook, char *str, int currentIndex)
{
    // Check phone length
    if (strlen(str) != 10)
    {
        printf(RED"⚠️  Phone number must contain exactly 10 digits.\n"RESET);
        return 0;
    }

    // Check for digits
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        {
            printf(RED"⚠️  Phone number should contain only digits.\n"RESET);
            return 0;
        }
    }

    // Check duplicate phone number
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Skip current contact while editing
        if (i != currentIndex &&
            strcmp(str, addressBook->contacts[i].phone) == 0)
        {
            printf(RED"❌  Phone Number Already Exists.\n"RESET);
            return 0;
        }
    }

    return 1;
}


// Validate email
int validate_email(AddressBook *addressBook, char *str, int currentIndex)
{
    // Find '@'
    char *at = strchr(str, '@');

    // Check email format
    if (at == NULL || at == str)
    {
        printf(RED"❌  Invalid Email ID.\n"RESET);
        return 0;
    }

    // First character cannot be a digit
    if (isdigit((unsigned char)str[0]))
    {
        printf(RED"⚠️  Email username cannot start with a digit.\n"RESET);
        return 0;
    }

    // Check characters before '@'
    for (char *p = str; p < at; p++)
    {
        // Only lowercase letters and digits allowed
        if (!islower((unsigned char)*p) && !isdigit((unsigned char)*p))
        {
            printf(RED"⚠️  Email username must contain only lowercase letters and digits.\n"RESET);
            return 0;
        }
    }

    // Check domain ends with ".com"
    if (strstr(at, ".com") == NULL)
    {
        printf(RED"⚠️  Email must end with .com\n"RESET);
        return 0;
    }

    // Check duplicate email
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Skip current contact while editing
        if (i != currentIndex &&
            strcmp(str, addressBook->contacts[i].email) == 0)
        {
            printf(RED"❌  Email Already Exists.\n"RESET);
            return 0;
        }
    }

    return 1;
}

