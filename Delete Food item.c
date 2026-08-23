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

    int choice;

    fp=fopen("menuTest.txt", "r");
    if(fp!=NULL)
    {
        while(fscanf(fp, "%d %s %f",
                     &menu[foodCount].id,
                     menu[foodCount].name,
                     &menu[foodCount].price) ==3)
        {
            foodCount++;
        }
        fclose(fp);
    }

                int id, found = 0;

                printf("Enter Food ID to Delete: ");
                scanf("%d", &id);

                for (int i = 0; i < foodCount; i++) {

                    if (menu[i].id == id) {

                        menu[i] = menu[foodCount - 1];
                        foodCount--;

                        found = 1;

                        printf("Food Deleted Successfully!\n");
                        break;
                    }
                }

                if (!found) {
                    printf("Food ID Not Found!\n");
                }
                else
                {
                    fp=fopen("menuTest.txt", "w");
                    if (fp==NULL)
                    {
                        printf("Error opening menu.\n");
                    }
                    else
                    {
                        for(int i=0; i< foodCount; i++)
                        {
                            fprintf(fp, "%d %s %.2f\n",
                                    menu[i].id,
                                    menu[i].name,
                                    menu[i].price);
                        }
                        fclose(fp);
                    }
                }

return 0;
    }
