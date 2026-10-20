#include <stdio.h>
#include "contact.h"
#include "file.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook);

    do
    {
        printf("\n");
        printf(BOLD WHITE BG_RED"          ADDRESS BOOK MENU          "RESET "\n\n");
        printf(GREEN "1. 👤 Create contact\n" RESET);
        printf(MAGENTA  "2. 🔍 Search contact\n" RESET);
        printf(BLUE  "3. ✏️  Edit contact\n" RESET);
        printf(RED   "4. 🗑️  Delete contact\n" RESET);
        printf(YELLOW "5. 📋 List all contacts\n" RESET);
        printf(BOLD GREEN   "6. 💾🚪 Save & Exit\n" RESET);
        printf(BOLD RED "-------------------------------------\n"RESET);

        printf(YELLOW"Enter your choice: "RESET);

        if (scanf("%d", &choice) != 1)
        {
            printf(RED"❌  Invalid input. Exiting.\n"RESET);
            break;
        }

        switch (choice)
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf(GREEN"Saving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);
                break;
            default:
                printf(RED"❌  Invalid choice. Please try again.\n"RESET);
        }
    } while (choice != 6);

    return 0;
}