#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "validation.h"

static int findByPhone(AddressBook *addressBook, const char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            return i;
    return -1;
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf(RED "❌ Address Book is Full\n" RESET);
        return;
    }

    int i = addressBook->contactCount;  // finding the free slot

    printf("\n" CYAN BOLD "********** Create Contact **********\n\n" RESET);

    while (1)
    {
        printf(YELLOW "Enter the name : " RESET);

        scanf(" %49[^\n]", addressBook->contacts[i].name);

        if (validate_name(addressBook->contacts[i].name))
            break;

        printf(RED "❌ Invalid Name. Try Again.\n\n" RESET);
    }

    while (1)
    {
        printf(YELLOW "Enter the phone : " RESET);

        scanf("%19s", addressBook->contacts[i].phone);

        if (validate_phone(addressBook,
                           addressBook->contacts[i].phone, i))
            break;

        printf(RED "❌ Invalid Phone. Try Again.\n\n" RESET);
    }

    while (1)
    {
        printf(YELLOW "Enter the email : " RESET);

        scanf("%49s", addressBook->contacts[i].email);

        if (validate_email(addressBook,
                           addressBook->contacts[i].email, i))
            break;

        printf(RED "❌ Invalid Email. Try Again.\n\n" RESET);
    }

    addressBook->contactCount++;

    printf(GREEN BOLD"\n✅ Contact Added Successfully.\n"RESET);
}
void searchContact(AddressBook *addressBook)
{
    int choice;
    int found = 0;
    char name[50], phone[20], email[50];

    printf("\n" CYAN BOLD "********** Search Contact **********\n" RESET);

    printf(GREEN "1. 🔍 Search by Name\n"RESET);
    printf(GREEN "2. 🔍 Search by Phone\n"RESET);
    printf(GREEN "3. 🔍 Search by Email\n"RESET);

    printf(YELLOW "\nEnter your choice : " RESET);
    scanf("%d", &choice);

    printf("\n" CYAN "+------+----------------------+--------------+-------------------------------+\n" RESET);
    printf(WHITE "| S.No | " RESET
           BOLD "Name" RESET
           "                  "
           WHITE "| " RESET
           BOLD "Phone" RESET
           "        "
           WHITE "| " RESET
           BOLD "Email" RESET
           "                        "
           WHITE "|\n" RESET);

    printf(CYAN "+------+----------------------+--------------+-------------------------------+\n" RESET);

    switch (choice)
    {
        case 1:

            printf(YELLOW "Enter Name : " RESET);
            scanf(" %49[^\n]", name);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(name, addressBook->contacts[i].name) == 0)
                {
                    printf(GREEN "%d\t%s\t\t%s\t%s\n" RESET,
                           i + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    found = 1;
                }
            }
            break;

        case 2:

            printf(YELLOW "Enter Phone : " RESET);
            scanf("%19s", phone);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(phone, addressBook->contacts[i].phone) == 0)
                {
                    printf(GREEN "%d\t%s\t\t%s\t%s\n" RESET,
                           i + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    found = 1;
                }
            }
            break;

        case 3:

            printf(YELLOW "Enter Email : " RESET);
            scanf("%49s", email);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(email, addressBook->contacts[i].email) == 0)
                {
                    printf(GREEN "%d\t%s\t\t%s\t%s\n" RESET,
                           i + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    found = 1;
                }
            }
            break;

        default:

            printf(RED "\n❌ Invalid Choice\n" RESET);
            return;
    }

    printf(CYAN "+------+----------------------+--------------+-------------------------------+\n" RESET);

    if (!found)
    {
        printf(RED "\n⚠️  Contact Not Found\n" RESET);
    }
}

void editContact(AddressBook *addressBook)
{
    char phone[20];
    int index, choice;
    char newName[50], newPhone[20], newEmail[50];

    printf(GREEN "Enter the phone number of the contact to edit : " RESET);
    scanf("%19s", phone);

    index = findByPhone(addressBook, phone);

    if (index == -1)
    {
        printf(RED "\n⚠️  Contact Not Found\n" RESET);
        return;
    }

    while (1)
    {
        printf("\n" CYAN BOLD "********** EDIT CONTACT **********\n" RESET);

        printf(MAGENTA "1. ✏️   Edit Name\n"RESET);
        printf(MAGENTA "2. ✏️   Edit Phone Number\n"RESET);
        printf(MAGENTA "3.✏️   Edit Email ID\n"RESET);
        printf(RED "4. ❌ Exit\n"RESET);

        printf(YELLOW "\nEnter your choice : " RESET);
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                while (1)
                {
                    printf(YELLOW "Enter New Name : " RESET);

                    if (scanf(" %49[^\n]", newName) != 1)
                        return;

                    if (validate_name(newName))
                    {
                        strcpy(addressBook->contacts[index].name, newName);

                        printf(GREEN"\n✅  Name Updated Successfully.\n"RESET);
                        break;
                    }

                    printf(RED "❌  Invalid Name. Try Again.\n" RESET);
                }
                break;

            case 2:

                while (1)
                {
                    printf(YELLOW "Enter New Phone Number : " RESET);

                    if (scanf("%19s", newPhone) != 1)
                        return;

                    if (validate_phone(addressBook, newPhone, index))
                    {
                        strcpy(addressBook->contacts[index].phone, newPhone);

                        printf(GREEN"\n✅  Phone Number Updated Successfully.\n"RESET);
                        break;
                    }

                    printf(RED "❌  Invalid Phone. Try Again.\n" RESET);
                }
                break;

            case 3:

                while (1)
                {
                    printf(YELLOW "Enter New Email ID : " RESET);

                    if (scanf("%49s", newEmail) != 1)
                        return;

                    if (validate_email(addressBook, newEmail, index))
                    {
                        strcpy(addressBook->contacts[index].email, newEmail);

                        printf(GREEN"\n✅  Email Updated Successfully.\n"RESET);
                        break;
                    }

                    printf(RED "❌  Invalid Email. Try Again.\n" RESET);
                }
                break;

            case 4:
                return;

            default:
                printf(RED "\n❌  Invalid Choice.\n" RESET);
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
    char phone[20];
    int index;

    printf(YELLOW"Enter the phone number of the contact to delete : "RESET);

    scanf("%19s", phone);

    index = findByPhone(addressBook, phone);

    if (index == -1)
    {
        printf(RED "\n⚠️  Contact Not Found\n" RESET);
        return;
    }

    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] =
            addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf(GREEN"\n✅  Contact Deleted Successfully.\n"RESET);
}

void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf(RED "\n❌  No Contacts Available!\n" RESET);
        return;
    }

    // Sort contacts by name
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcasecmp(addressBook->contacts[j].name,
                           addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp;

                temp = addressBook->contacts[j];

                addressBook->contacts[j] =
                    addressBook->contacts[j + 1];

                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Display contacts

    printf("\n"WHITE
           "+-------+----------------------+-----------------+------------------------------+\n"
           RESET);

    printf(CYAN BOLD
           "| %-5s | %-20s | %-15s | %-28s |\n"
           RESET,
           "Index", "Name", "Phone", "Email");

    printf(WHITE
           "+-------+----------------------+-----------------+------------------------------+\n"
           RESET);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf(WHITE
               "| %-5d | %-20s | %-15s | %-28s |\n"
               RESET,
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf(WHITE
           "+-------+----------------------+-----------------+------------------------------+\n"
           RESET);

    printf(GREEN BOLD
           "|   [TOTAL CONTACT = %d]                                                        |\n"
           RESET,
           addressBook->contactCount);

    printf(WHITE
           "+-------+----------------------+-----------------+------------------------------+\n"
           RESET);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}