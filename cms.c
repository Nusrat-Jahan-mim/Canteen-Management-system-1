#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Food 
{
    int id;
    char name[30];
    float price;
};

struct Order 
{
    char name[50];
    char phone[20];
    char item[30];
    int quantity;
    float totalPrice;
};

struct Food menu[100];
struct Order orders[100];

int foodCount = 0;
int totalOrders = 0;
float totalSales = 0;

int isNumValid(char *phone)
{
    int len = strlen(phone);

    if (len != 11)
    {
        return 0;
    }

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }

    return 1;
}

int main() 
{

    FILE *fp;

    int choice;
    fp=fopen("menu.txt", "r");
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

    while (1) 
    {

        printf("\n====================================\n");
        printf("      CANTEEN MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf(" NUB Canteen \n");

        printf("1. Food Management\n");
        printf("2. Take Order\n");
        printf("3. Display Menu\n");
        printf("4. Daily Sales Report\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {

        case 1: 
            int subChoice;

            printf("\n------ FOOD MANAGEMENT ------\n");
            printf("1. Add Food\n");
            printf("2. Delete Food\n");
            printf("3. Update Food\n");
            printf("4. Back\n");
            printf("Enter Choice: ");
            scanf("%d", &subChoice);

            if (subChoice == 1) 
            {
                fp = fopen("menu.txt", "r");
                if (fp != NULL) {
                    while (fscanf(fp, "%d %s %f",
                                &menu[foodCount].id,
                                menu[foodCount].name,
                                &menu[foodCount].price) == 3) {
                        foodCount++;
                    }
                    fclose(fp);
                }
                
                struct Food item;

                printf("\nEnter Food ID: ");
                scanf("%d", &item.id);

                for (int i = 0; i < foodCount; i++)
                {
                    if (menu[i].id == item.id)
                    {
                        printf("ID %d already exists in menu.\n", item.id);
                        return 1;
                    }
                }

                printf("\nEnter Food Name: ");
                scanf("%s", item.name);

                for (int i = 0; i < foodCount; i++)
                {
                    if (strcmp(menu[i].name, item.name) == 0)
                    {
                        printf("Name \"%s\" already exists in menu.\n", item.name);
                        return 1;
                    }
                }

                printf("\nEnter Food Price: ");
                scanf("%f", &item.price);

                fp = fopen("menu.txt", "a");
                
                if (fp==NULL)
                {
                    printf("Error opening menu.\n");
                    break;
                }
                
                fprintf(fp, "%d %s %.2f\n",
                        item.id,
                        item.name,
                        item.price);

                menu[foodCount] = item;
                foodCount++;

                printf("\nFood Added Successfully!\n");

                fclose(fp);
                
                break;
            }

            else if (subChoice == 2)
            {
                int id, found = 0;

                printf("Enter Food ID to Delete: ");
                scanf("%d", &id);

                for (int i = 0; i < foodCount; i++) 
                {

                    if (menu[i].id == id) 
                    {

                        menu[i] = menu[foodCount - 1];
                        foodCount--;

                        found = 1;

                        printf("Food Deleted Successfully!\n");
                        break;
                    }
                }

                if (!found)
                {
                    printf("Food ID Not Found!\n");
                }
                else
                {
                    fp=fopen("menu.txt", "w");
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
                break;
            }

            else if (subChoice == 3) 
            {
                fp = fopen("menu.txt", "r");

                if (fp == NULL)
                {
                    printf("Error opening menu.\n");
                    return 1;
                }

                fclose(fp);

                if (foodCount == 0)
                {
                    printf("\nNo items found in the menu. \n");
                    break;
                }

                int sID, found = -1;
                
                printf("Enter Food ID to edit: ");
                scanf("%d", &sID);

                for (int i = 0; i < foodCount; i++)
                {
                    if (menu[i].id == sID)
                    {
                        found = i;
                        break;
                    }
                }

                if (found == -1)
                {
                    printf("Food ID %d not found.\n", sID);
                    break;
                }

                printf("\nCurrent Name of Item: %s\n", menu[found].name);
                printf("\nCurrent Price of Item: %.2f\n", menu[found].price);

                char ch;
                printf("\nDo you want to edit the name? [Y/N]: ");
                scanf("%s", &ch);

                if (ch == 'Y' || ch == 'y')
                {
                    printf("Enter new name: ");
                    scanf("%s", menu[found].name);
                }

                printf("\nDo you want to edit the price? [Y/N]: ");
                scanf("%s", &ch);

                if (ch == 'Y' || ch == 'y')
                {
                    printf("Enter new price: ");
                    scanf("%f", &menu[found].price);
                }
                else
                {
                    break;
                }

                fp = fopen("menu.txt", "w");

                if (fp == NULL)
                {
                    printf("Menu could not be opened for editing.\n");
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
            
            }

        break;

        case 2: 

            if (foodCount == 0) 
            {
                printf("No Food Available In Menu!\n");
                break;
            }

            printf("\nCustomer Name: ");
            scanf("%s", orders[totalOrders].name);

            printf("\nPhone Number: ");
            scanf("%s", orders[totalOrders].phone);

            if (!isNumValid(orders[totalOrders].phone))
            {
                printf("Invalid phone number. Phone number must be 11 digits.\n");
                break;
            }

            printf("\nItem Name: ");
            scanf("%s", orders[totalOrders].item);

            printf("\nQuantity: ");
            scanf("%d", &orders[totalOrders].quantity);

            int found = 0;
            float itemPrice = 0;

            for (int i = 0; i < foodCount; i++) 
            {

                if (strcmp(menu[i].name, orders[totalOrders].item) == 0) 
                {
                    itemPrice = menu[i].price;
                    found = 1;
                    break;
                }
            }

            if (!found) 
            {
                printf("Item Not Found In Menu!\n");
                break;
            }

            orders[totalOrders].totalPrice = itemPrice * orders[totalOrders].quantity;

            fp = fopen("Customer_Data.txt", "a");
            if (fp == NULL)
            {
                printf("Error opening customer data file.\n");
                break;
            }

            fprintf(fp, "%s %s %.2f\n",
                    orders[totalOrders].name,
                    orders[totalOrders].phone,
                    orders[totalOrders].totalPrice);

            fclose(fp);
            
            totalSales += orders[totalOrders].totalPrice;

            totalOrders++;

            break;
        

        case 3: 

            fp = fopen("menu.txt", "r");
            if(fp == NULL)
            {
                printf("Error opening menu.\n");
                return 1;
            }
            
            fclose(fp);

            if (foodCount == 0)
            {
                printf("\nMenu currently empty.\n");
                break;
            }

            printf("\n================= MENU =================\n");
            printf("\n%-10s %-20s %-10s\n", "ID", "Name", "Price");
            printf("----------------------------------------\n");

            for (int i = 0; i < foodCount; i++)
            {
                printf("%-10d %-20s %-10.2f\n",
                        menu[i].id,
                        menu[i].name,
                        menu[i].price);
            }

            break;

        

        case 4: 

            printf("\n========== DAILY SALES ==========\n");
            printf("Total Orders : %d\n", totalOrders);
            printf("Total Sales  : %.2f Tk\n", totalSales);

            break;
        

        case 5:
            printf("\nThank You For Using The System!\n");
            return 0;

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}
//NUB
