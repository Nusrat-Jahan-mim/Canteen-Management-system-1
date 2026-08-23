
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
