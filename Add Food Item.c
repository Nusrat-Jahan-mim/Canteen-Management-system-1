#include <stdio.h>
#include <string.h>

struct Food {
    int id;
    char name[30];
    float price;
};

struct Food menu[100];
int foodCount = 0;

int main() {

    FILE *fp;

    fp = fopen("menuTest.txt", "a");
    if (fp==NULL)
    {
        printf("Error opening menu.\n");

    }

    printf("\nEnter Food ID: ");
    scanf("%d", &menu[foodCount].id);

    printf("\nEnter Food Name: ");
    scanf("%s", menu[foodCount].name);

    printf("\nEnter Food Price: ");
    scanf("%f", &menu[foodCount].price);

    fprintf(fp, "%d %s %.2f\n",
            menu[foodCount].id,
            menu[foodCount].name,
            menu[foodCount].price);

    foodCount++;

    printf("\nFood Added Successfully!\n");

    fclose(fp);

return 0;


    }
