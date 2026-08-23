
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



