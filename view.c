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
    if (fp == NULL) {
        printf("Error opening menu.\n");
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
        printf("\nNo items found in the menu.\n");
        return 0;
    }

    printf("\n%-10s %-20s %-10s\n", "ID", "Name", "Price");
    printf("-----------------------------------------\n");

    for (int i = 0; i < foodCount; i++) 
    {
        printf("%-10d %-20s %-10.2f\n",
               menu[i].id,
               menu[i].name,
               menu[i].price);
    }

    return 0;
}