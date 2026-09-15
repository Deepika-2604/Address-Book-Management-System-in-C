#include <stdio.h>
#include<string.h>
#include "file.h"
#define file_name "contacts.txt"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL)
    {
    printf("ERROR OPENING FILE FOR WRITING/n");
    return;
    }
    for(int i=0;i<addressBook->count;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
    }
    fclose(fp);
  
}


void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        addressBook->count = 0;
        return;
    }

    addressBook->count = 0;

    while (fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->count].name,addressBook->contacts[addressBook->count].num, addressBook->contacts[addressBook->count].email) == 3)
    {
        addressBook->count++;
    }

    fclose(fp);
}