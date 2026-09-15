#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#define pf printf
#define sf scanf
#include "contact.h"
#include "file.h"


void listContacts(AddressBook *addressBook) 
{
    pf("---------------------------------------------------------\n");
    pf("\t\t%s\n","CONTACTS LIST");
    pf("---------------------------------------------------------\n");
    pf("%-5s %-20s %-15s %-25s\n\n","S.NO","Name","Phone number","Email");
     for(int i=0;i<addressBook->count;i++)

        pf("%-5d %-20s %-15s %-25s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
pf("\n");
    
}

void initialize(AddressBook *addressBook)
 {
 addressBook->count=0;
 loadContactsFromFile(addressBook); 
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	
    pf("---------------------------------------------------------\n");
    pf("\t\t%s\n","CREATE CONTACT");
    pf("---------------------------------------------------------\n");
    int valid;
    char str[100];
    do{
     valid=1;
    pf("Enter name:");
    sf(" %[^\n]",str);
    for(int i=0;str[i]!='\0';i++)
    {
        if(!( isalpha(str[i])||str[i]==' '||str[i]=='.') )
        {
            valid=0;
            break;
        }
    }
    if(valid)
        strcpy((addressBook->contacts[addressBook->count].name),str);

    else
    pf("Enter a correct name\n");

    }
    while(!valid);
    
    do{
        valid=1;
     pf("Enter Mobile Number:");
        sf(" %[^\n]",str);
        if(strlen(str)!=10)
        {
            valid=0;
        }
        else
        {
        for(int i=0;str[i]!='\0';i++)
        {
            if(!isdigit(str[i]))
            {
                valid=0;
                break;
            }
        }
        }
        if(valid)
        {
        if((addressBook->count)>0)
        {
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].num,str))
                {
                    valid=0;
                pf("Number already exists,");
                }
            }
        }
       }
        if(valid)
        
        strcpy((addressBook->contacts[addressBook->count].num),str);

        else
        pf("Enter a correct number\n");
    }
     while(!valid);

    do
    {
        valid=1;
        int count1=0,count2=0;
        pf("Enter Email ID:");
        sf(" %[^\n]",str);
        for(int i=0;str[i]!='\0';i++)
        {
            if(str[i]=='@')
            {
                if(count1==0)
                count1++;
            else
            {
                valid=0;
                break;
            }
            }
            else if(str[i]=='.')
            {
                if(count2==0)
                count2++;
            else
            {
                valid=0;
                break;
            }
            }
        }
        if(valid)
        {
        for(int i=0;str[i]!='\0';i++)
        {
            if(! (islower(str[i])||isdigit(str[i])||str[i]=='@'||str[i]=='.') )
            {
                valid=0;
                break;
            }
        }
         if(!(strstr(str,".com")&& strchr(str,'@')))
        valid=0;

        if(valid)
        {
        if((addressBook->count)>0)
        {
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].email,str))
                {
                    valid=0;
                pf("Email already exists,");
                }
            }
        }
       }
    }
       
    if(valid)
            strcpy((addressBook->contacts[addressBook->count].email),str);
        else
        pf("Enter correct Email\n");
    }
    while(!valid);

        addressBook->count++;
}


void searchContact(AddressBook *addressBook) 
{
 pf("---------------------------------------------------------\n");
    pf("\t\t%s\n","CONTACTS SEARCH");
    pf("---------------------------------------------------------\n");
    char choice;
    char str[50];
    int found;
    do
    {
        found=0;
     pf("1:SEARCH BY NAME\n");
     pf("2:SEARCH BY NUMBER\n");
     pf("3:SEARCH BY EMAIL\n");
     pf("4:EXIT\n");
     sf(" %c",&choice);
     switch(choice)
     {
        case'1':
        {
            pf("ENTER THE NAME:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].name,str) )
                {
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                }
            }
            if(!found)
            pf("NAME IS NOT FOUND\n");
                pf("\n");
        }
     break;
       
        case'2':
        {
            pf("ENTER THE NUMBER:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].num,str) )
                {
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                }
            }
            if(!found)
            pf("NUMBER IS NOT FOUND\n");
        pf("\n");
        }
        break;
         case'3':
        {
            pf("ENTER THE EMAIL:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].email,str) )
                {
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                }
            }
            if(!found)
            pf("EMAIL IS NOT FOUND\n");
        pf("\n");
        }
        break;
        default:pf("ENTER VALID CHOICE\n");
     }
     
    } 
    while(choice!='4');
}

void editContact(AddressBook *addressBook)
{
	    pf("---------------------------------------------------------\n");
    pf("\t\t%s\n","CONTACTS EDIT");
    pf("---------------------------------------------------------\n");
    char choice;
    char str[50];
    int found;
    int set=0;
    int valid;
    do
    {
        found=0;
     pf("1:SEARCH BY NAME AND EDIT THE NAME\n");
     pf("2:SEARCH BY NUMBER AND EDIT THE NUMBER\n");
     pf("3:SEARCH BY EMAIL AND EDIT THE EMAIL\n");
     pf("4:EXIT\n");
     sf(" %c",&choice);
     switch(choice)
     {
        case'1':
        {
            pf("ENTER THE NAME TO SEARCH:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].name,str) )
                {
                    pf("%-20s %-15s %-25s\n\n","NAME","PHONE NUMBER","EMAIL");
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                    set=i;
                }
            }
            if(!found)
            pf("NAME IS NOT FOUND\n");
        else
        {
             valid=1;
            do{
     valid=1;
    pf("ENTER NEW NAME:");
    sf(" %[^\n]",str);
    for(int i=0;str[i]!='\0';i++)
    {
        if(!( isalpha(str[i])||str[i]==' '||str[i]=='.') )
        {
            valid=0;
            break;
        }
    }
    if(valid)
    {
        strcpy((addressBook->contacts[set].name),str);

        pf("\n\t\tAFTER EDITING\n\n");
         pf("%-20s %-15s %-25s\n\n","NAME","PHONE NUMBER","EMAIL");

        pf("%-20s %-15s %-25s\n",addressBook->contacts[set].name,addressBook->contacts[set].num,addressBook->contacts[set].email);

                pf("\n");
    }

    else
    pf("ENTER A CORRECT NAME\n");

    }
    while(!valid);
        }
         pf("\n");
        }
     break;
       
        case'2':
        {
            pf("ENTER THE NUMBER TO SEARCH:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].num,str) )
                {
                    pf("%-20s %-15s %-25s\n\n","NAME","PHONE NUMBER","EMAIL");
                    pf("%-20s %-15s %-25s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                    set=i;
                }
            }
            if(!found)
            pf("NUMBER IS NOT FOUND\n");
        else
        {
            
    do{
        valid=1;
     pf("ENTER A NEW PHONE NUMBER:");
        sf(" %[^\n]",str);
        if(strlen(str)!=10)
        {
            valid=0;
        }
        else
        {
        for(int i=0;str[i]!='\0';i++)
        {
            if(!isdigit(str[i]))
            {
                valid=0;
                break;
            }
        }
        }
        if(valid)
        {
        if((addressBook->count)>0)
        {
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].num,str))
                {
                    valid=0;
                pf("\nNUMBER IS ALREADY EXISTS,");
                }
            }
        }
       }
        if(valid)
        {
        strcpy((addressBook->contacts[set].num),str);
         pf("\n\t\tAFTER EDITING\n");
         pf("%-20s %-15s %-25s\n\n","NAME","PHONE NUMBER","EMAIL");

        pf("%-20s %-15s %-25s\n",addressBook->contacts[set].name,addressBook->contacts[set].num,addressBook->contacts[set].email);

                pf("\n");
        }

        else
        pf("ENTER A CORRECT NUMBER\n\n");
    }
     while(!valid);

        }
        pf("\n");
        }
        break;

         case'3':
        {
            pf("ENTER THE EMAIL TO SEARCH:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].email,str) )
                {
                     pf("%-20s %-15s %-25s\n\n","NAME","PHONE NUMBER","EMAIL");
                    pf("%-20s %-15s %-25s\n\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                    set=i;
                }
            }
            if(!found)
            pf("EMAIL IS NOT FOUND\n");
        else
        {
            do{

            
            valid=1;
        pf("ENTER NEW EMAIL ID:");
        sf(" %[^\n]",str);
        int count1=0,count2=0;
        for(int i=0;str[i]!='\0';i++)
        {
            if(str[i]=='@')
            {
                if(count1==0)
                count1++;
            else
            {
                valid=0;
                break;
            }
            }
            else if(str[i]=='.')
            {
                if(count2==0)
                count2++;
            else
            {
                valid=0;
                break;
            }
            }
        }
        if(valid)
        {
        for(int i=0;str[i]!='\0';i++)
        {
            if(! (islower(str[i])||isdigit(str[i])||str[i]=='@'||str[i]=='.') )
            {
                valid=0;
                break;
            }
        }
         if(!strstr(str,".com"))
        valid=0;

        if(valid)
        {
        if((addressBook->count)>0)
        {
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].email,str))
                {
                    valid=0;
                pf("EMAIL ALREADY EXISTS,");
                }
            }
        }
       }
    }
       
    if(valid)
    {
            strcpy((addressBook->contacts[set].email),str);
              pf("\n\t\tAFTER EDITING\n\n");
         pf("%-20s %-15s %-25s\n\n","NAME","PHONE NUMBER","EMAIL");

        pf("%-20s %-15s %-25s\n",addressBook->contacts[set].name,addressBook->contacts[set].num,addressBook->contacts[set].email);

                pf("\n");
    }
        else
        pf("ENTER A CORRECT EMAIL\n");
    }
    while(!valid);
}
    pf("\n");
        }
        
        break;

        default:pf("ENTER VALID CHOICE\n");
     }
     
}
    while(choice!='4');
    
}

void deleteContact(AddressBook *addressBook)
{
	pf("---------------------------------------------------------\n");
    pf("\t\t%s\n","CONTACTS DELETE");
    pf("---------------------------------------------------------\n");
    char choice;
    char str[50];
    int found;
    int set;
    char confirm;
    do
    {
        found=0;
     pf("1:SEARCH BY NAME\n");
     pf("2:SEARCH BY NUMBER\n");
     pf("3:SEARCH BY EMAIL\n");
     pf("4:EXIT\n");
     sf(" %c",&choice);
     switch(choice)
     {
        case'1':
        {
            pf("ENTER THE NAME:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].name,str) )
                {
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                    set=i;
                }
            }
            if(!found)
            pf("NAME IS NOT FOUND\n");
        else
        {
            pf("YOU NEED TO DELETE THE CONTACT y/n:\n");
            sf(" %c",&confirm);
            if(confirm=='y')
            {
                for(int i=set;i<addressBook->count-1;i++)
                {
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                addressBook->count--;
                pf("CONTACTS DELETED\n");

            }
        }
                pf("\n");
        }
     break;
       
        case'2':
        {
            pf("ENTER THE NUMBER:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].num,str) )
                {
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                    set=i;
                }
            }
            if(!found)
            pf("NUMBER IS NOT FOUND\n");
        else
        {
            pf("YOU NEED TO DELETE THE CONTACT y/n:\n");
            sf(" %c",&confirm);
            if(confirm=='y')
            {
                for(int i=set;i<addressBook->count-1;i++)
                {
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                addressBook->count--;
                pf("CONTACTS DELETED\n");

            }
        }
        
        pf("\n");
        }
        break;
         case'3':
        {
            pf("ENTER THE EMAIL:");
            sf(" %[^\n]",str);
            for(int i=0;i<addressBook->count;i++)
            {
                if(!strcmp(addressBook->contacts[i].email,str) )
                {
                    pf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].num,addressBook->contacts[i].email);
                    found=1;
                    set=i;
                }
            }
            if(!found)
            pf("EMAIL IS NOT FOUND\n");
        else
        {
            pf("YOU NEED TO DELETE THE CONTACT y/n:\n");
            sf(" %c",&confirm);
            if(confirm=='y')
            {
                for(int i=set;i<addressBook->count-1;i++)
                {
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                addressBook->count--;
                pf("CONTACTS DELETED\n");

            }
        }
        
        pf("\n");
        }
        break;
        default:pf("ENTER VALID CHOICE\n");
     }
     
    } 
    while(choice!='4');   

   
}
