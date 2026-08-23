#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

void adminPanel();   // Function declaration

void adminLogin()
{
    char username[30];
    char password[20];
    int attempt = 0;

    while(attempt < 3)
    {
        printf("\n[ADMIN LOGIN]\n");

        printf("Username: ");
        scanf("%29s", username);

        printf("Password: ");
        scanf("%19s", password);

        if(strcmp(username, ADMIN_USER) == 0 &&
           strcmp(password, ADMIN_PASS) == 0)
        {
            printf("\nLogin Successful!\n");
            printf("Welcome to NUB Canteen\n");

            adminPanel();

            return;
        }
        else
        {
            attempt++;

            printf("\nWrong Username or Password\n");
            printf("Remaining Attempt: %d\n", 3 - attempt);
        }
    }

    printf("\nAccess Denied.\n");
    system("pause");
}

void employeePanel()
{
    printf("\n===== EMPLOYEE PANEL =====\n");
    printf("Welcome Employee!\n");

    system("pause");
}

int main()
{
    adminLogin();

    return 0;
}

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
