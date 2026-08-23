#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Food {
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

int main() {

    FILE *fp;

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

    if (foodCount == 0)
    {
        printf("No Food Available In Menu!\n");
        return 0;
    }

    printf("\nCustomer Name: ");
    scanf("%s", orders[totalOrders].name);

    printf("\nPhone Number: ");
    scanf("%s", orders[totalOrders].phone);

    if (!isNumValid(orders[totalOrders].phone))
    {
        printf("Invalid phone number. Phone number must be 11 digits.\n");
        return 0;
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
        printf("Item not found in menu!\n");
        return 0;
    }

    orders[totalOrders].totalPrice = itemPrice * orders[totalOrders].quantity;

    fp = fopen("Customer_Data.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening customer data file.\n");
        return 1;
    }

    fprintf(fp, "%s %s %.2f\n",
            orders[totalOrders].name,
            orders[totalOrders].phone,
            orders[totalOrders].totalPrice);

    
    fclose(fp);

    totalOrders++;

    printf("\nOrder Taken Successfully!\n");

    return 0;

}