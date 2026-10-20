#include <stdio.h>
#include <string.h>
#include "file.h"

#define DATA_FILE "contacts.txt"
/*DATA_FILE is a macro defined using #define. It stores the filename as a string
 and makes it easier to change or reuse the filename throughout the program.*/
//Both functions use this macro to access the same file.

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp==NULL)
    {
        printf("❌  Could not open %s for writing.\n", DATA_FILE);
        return;
    }
    fprintf(fp,"#%d\n",addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("Saved %d contact(s) to %s.\n", addressBook->contactCount, DATA_FILE);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp==NULL)
        return;

    char line[256];

    fscanf(fp,"#%d\n",&addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}