
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

#define EMP_USER "employee"
#define EMP_PASS "1234"

void loading();
void mainMenu();
void adminLogin();
void employeeLogin();
void adminPanel();
void employeePanel();

#endif


#include "functions.h"

void loading()
{
    int i;

    printf("\n\n");
    printf("=====================================\n");
    printf("         NUB CANTEEN SYSTEM\n");
    printf("=====================================\n");

    printf("\nLoading");

    for(i=0;i<8;i++)
    {
        printf(".");
        fflush(stdout);

        #ifdef _WIN32
        Sleep(250);
        #endif
    }

    printf("\n\n");
}

void mainMenu()
{
    int choice;

    while(1)
    {
        printf("\n=============================\n");
        printf("      MAIN MENU\n");
        printf("=============================\n");

        printf("1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Exit\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                adminLogin();
                break;

            case 2:
                employeeLogin();
                break;

            case 3:
                printf("\nThank You.\n");
                exit(0);

            default:
                printf("\nInvalid Choice\n");
        }
    }
}


void adminLogin()
{
    char username[30];
    char password[30];

    int attempt = 0;

    while(attempt < 3)
    {
        system("cls");

        printf("\n====================================\n");
        printf("         ADMIN LOGIN PANEL\n");
        printf("====================================\n");

        printf("\nUsername : ");
        scanf("%s", username);

        printf("Password : ");
        scanf("%s", password);

        if(strcmp(username, ADMIN_USER)==0 &&
           strcmp(password, ADMIN_PASS)==0)
        {
            printf("\n\nLogin Successful...\n");

            loading();

            adminPanel();

            return;
        }

        else
        {
            printf("\nWrong Username or Password\n");

            attempt++;

            printf("Remaining Attempt : %d\n",3-attempt);
        }

        system("pause");
    }

    printf("\nAccess Denied.\n");
    system("pause");
}



//adminpanel
void adminPanel()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("====================================\n");
        printf("         ADMIN DASHBOARD\n");
        printf("====================================\n");

        printf("1. Food Management\n");
        printf("2. Employee Management\n");
        printf("3. Customer Orders\n");
        printf("4. Daily Sales Report\n");
        printf("5. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("\nFood Management Module (Coming in Part-2)\n");
                break;

            case 2:
                printf("\nEmployee Management Module (Coming in Part-3)\n");
                break;

            case 3:
                printf("\nOrder Management Module (Coming in Part-4)\n");
                break;

            case 4:
                printf("\nSales Report Module (Coming in Part-7)\n");
                break;

            case 5:
                return;

            default:
                printf("\nInvalid Choice\n");
        }

        system("pause");
    }
}

void employeeLogin()
{
    char username[30];
    char password[30];

    int attempt = 0;

    while(attempt < 3)
    {
        system("cls");

        printf("=====================================\n");
        printf("       EMPLOYEE LOGIN PANEL\n");
        printf("=====================================\n");

        printf("\nUsername : ");
        scanf("%s", username);

        printf("Password : ");
        scanf("%s", password);

        if(strcmp(username, EMP_USER) == 0 &&
           strcmp(password, EMP_PASS) == 0)
        {
            printf("\nLogin Successful!\n");

            loading();

            employeePanel();

            return;
        }
        else
        {
            attempt++;

            printf("\nInvalid Username or Password!\n");
            printf("Remaining Attempts : %d\n", 3 - attempt);

            system("pause");
        }
    }

    printf("\nToo Many Failed Attempts!\n");
    printf("Returning to Main Menu...\n");

    system("pause");
}


void employeePanel()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("=====================================\n");
        printf("        EMPLOYEE DASHBOARD\n");
        printf("=====================================\n");

        printf("1. Display Food Menu\n");
        printf("2. Take Customer Order\n");
        printf("3. Print Receipt\n");
        printf("4. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("\nFood Menu Module (Part-2)\n");
                break;

            case 2:
                printf("\nCustomer Order Module (Part-4)\n");
                break;

            case 3:
                printf("\nReceipt Module (Part-5)\n");
                break;

            case 4:
                return;

            default:
                printf("\nInvalid Choice!\n");
        }

        system("pause");
    }
}

//Password Mask Function
void inputPassword(char password[])
{
    int i = 0;
    char ch;

    while(1)
    {
        ch = getch();

        if(ch == 13) // Enter
        {
            password[i] = '\0';
            break;
        }
        else if(ch == 8 && i > 0) // Backspace
        {
            i--;
            printf("\b \b");
        }
        else if(ch != 8)
        {
            password[i++] = ch;
            printf("*");
        }
    }
}

//Password Mask Function
inputPassword(password);
//Customer Panel
void customerPanel()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("=====================================\n");
        printf("         CUSTOMER PANEL\n");
        printf("=====================================\n");

        printf("1. View Food Menu\n");
        printf("2. Order Food\n");
        printf("3. Search Food\n");
        printf("4. Exit\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("\nFood Menu Module (Part-2)\n");
                break;

            case 2:
                printf("\nOrder Module (Part-4)\n");
                break;

            case 3:
                printf("\nSearch Module (Part-6)\n");
                break;

            case 4:
                return;

            default:
                printf("\nInvalid Choice!\n");
        }

        system("pause");
    }
}

//Main Menu Update
printf("1. Admin Login\n");
printf("2. Employee Login\n");
printf("3. Customer Panel\n");
printf("4. Exit\n");


case 1:
    adminLogin();
    break;

case 2:
    employeeLogin();
    break;

case 3:
    customerPanel();
    break;

case 4:
    exit(0);





