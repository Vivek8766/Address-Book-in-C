#ifndef VALIDATION_H
#define VALIDATION_H

#include "contact.h"

int validate_name(char *str);
int validate_phone(AddressBook *addressBook, char *str, int currentIndex);
int validate_email(AddressBook *addressBook, char *str, int currentIndex);

#endif