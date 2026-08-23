#include <stdio.h>
#include <string.h>

struct Food 
{
    int id;
    char name[30];
    float price;
};

struct Food menu[100];
int foodCount = 0;

int main() 
{

    FILE *fp;

    fp = fopen("menuTest.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening menu file (it may not exist yet).\n");
        return 1;
    }

    while (fscanf(fp, "%d %s %f",
                   &menu[foodCount].id,
                   menu[foodCount].name,
                   &menu[foodCount].price) == 3) 
    {
        foodCount++;
    }
    fclose(fp);

    if (foodCount == 0) 
    {
        printf("No items found in the menu.\n");
        return 0;
    }

    int searchId, found = -1;
    printf("Enter Food ID to edit: ");
    scanf("%d", &searchId);

    for (int i = 0; i < foodCount; i++) 
    {
        if (menu[i].id == searchId) 
        {
            found = i;
            break;
        }
    }

    if (found == -1) 
    {
        printf("Food ID %d not found.\n", searchId);
        return 0;
    }

    printf("\nCurrent Name: %s\n", menu[found].name);
    printf("Current Price: %.2f\n", menu[found].price);

    char choice;
    printf("\nDo you want to edit the name? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') 
    {
        printf("Enter new name: ");
        scanf("%s", menu[found].name);
    }

    printf("Do you want to edit the price? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') 
    {
        printf("Enter new price: ");
        scanf("%f", &menu[found].price);
    }
    else
    {
        return 0;
    }

    fp = fopen("menuTest.txt", "w");
    if (fp == NULL) {
        printf("Error opening menu file for writing.\n");
        return 1;
    }

    for (int i = 0; i < foodCount; i++) 
    {
        fprintf(fp, "%d %s %.2f\n",
                menu[i].id,
                menu[i].name,
                menu[i].price);
    }

    fclose(fp);

    printf("\nFood item updated successfully!\n");

    return 0;
}