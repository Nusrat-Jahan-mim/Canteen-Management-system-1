
#include <stdio.h>
#include <string.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

void adminLogin()
{
    char username[30];
    char password[20];

    printf("\n========== ADMIN LOGIN ==========\n");

    printf("Username: ");
    scanf("%29s", username);

    printf("Password: ");
    scanf("%19s", password);

    if(strcmp(username, ADMIN_USER) == 0 &&
       strcmp(password, ADMIN_PASS) == 0)
    {
        printf("\nLogin Successful!\n");
        printf("Welcome, Admin!\n");
    }
    else
    {
        printf("\nInvalid Username or Password!\n");
    }
}

int main()
{
    adminLogin();

    return 0;
}
