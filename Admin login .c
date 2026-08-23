#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

void employeePanel();   // Function declaration

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

            employeePanel();

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
