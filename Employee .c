#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#endif

#define EMP_USER "employee"
#define EMP_PASS "1234"


/* Function Declaration */
void employeeLogin();
void employeePanel();
void inputPassword(char password[]);

int main()
{
    employeeLogin();

    return 0;
}

void employeeLogin()
{
    char username[30];
    char password[30];

    int attempt = 0;

    while(attempt < 3)
    {
        system("cls");
        printf("       EMPLOYEE LOGIN \n");


        printf("\nUsername : ");
        scanf("%29s", username);

        printf("Password : ");
        inputPassword(password);

        printf("\n");

        if(strcmp(username, EMP_USER) == 0 &&
           strcmp(password, EMP_PASS) == 0)
        {
            printf("\nLogin Successful!\n");
            system("pause");

            employeePanel();

            return;
        }
        else
        {
            attempt++;

            printf("\nWrong Username or Password!\n");
            printf("Remaining Attempt : %d\n", 3 - attempt);

            system("pause");
        }
    }

    printf("\nAccess Denied!\n");
    system("pause");
}

void employeePanel()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("       [ EMPLOYEE DASHBOARD]\n");

        printf("\n1. Display Food Menu\n");
        printf("2. Take Customer Order\n");
        printf("3. Print Receipt\n");
        printf("4. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nFood Menu Module\n");
                system("pause");
                break;

            case 2:
                printf("\nCustomer Order Module\n");
                system("pause");
                break;

            case 3:
                printf("\nReceipt Module\n");
                system("pause");
                break;

            case 4:
                printf("\nEmployee Logged Out.\n");
                system("pause");
                return;

            default:
                printf("\nInvalid Choice!\n");
                system("pause");
        }
    }
}


void inputPassword(char password[])
{
    int i = 0;
    char ch;

#ifdef _WIN32

    while(1)
    {
        ch = getch();

        /* ENTER */
        if(ch == 13)
        {
            password[i] = '\0';
            break;
        }

        /* BACKSPACE */
        else if(ch == 8)
        {
            if(i > 0)
            {
                i--;
                printf("\b \b");
            }
        }

        /* Normal character */
        else
        {
            if(i < 29)
            {
                password[i] = ch;
                i++;

                printf("*");
            }
        }
    }

#else

    scanf("%29s", password);

#endif
}
