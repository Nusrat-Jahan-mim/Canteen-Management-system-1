
//NUB CANTEEN MANAGEMENT SYSTEM


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#ifdef _WIN32
#endif

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

#define EMP_USER "employee"
#define EMP_PASS "1234"

#define MAX_CUSTOMERS 100
#define MAX_ORDER_ITEMS 20


typedef struct
{
    int id;
    char name[50];
    char phone[20];

} Customer;


typedef struct Order
{
    int orderID;

    char customerName[50];

    char foodName[50];

    int quantity;

    float unitPrice;

    float totalPrice;

    struct Order *next;

} Order;





Customer customers[MAX_CUSTOMERS];

int customerCount = 0;

Order *front = NULL;
Order *rear = NULL;

int nextOrderID = 1001;





void mainMenu();

void adminLogin();
void employeeLogin();

void adminPanel();
void employeePanel();
void customerPanel();

void inputPassword(char password[]);

void addFood();
void displayFood();
void deleteFood();
void updateFood();

void customerRegistration();
int validPhone(char phone[]);
int generateCustomerID();
int customerLogin();

void customerOrder();

void billing();
void printReceipt(Order *order);

void salesStatisticsMenu();

void incomeSummary();
void dailySalesReport();
void monthlySalesReport();

void highestSale();
void lowestSale();
void averageSale();

void pauseScreen();





int main()
{
    mainMenu();

    return 0;
}





void pauseScreen()
{
    printf("\nPress Enter to continue...");

    getchar();
}





void mainMenu()
{
    int choice;

    while(1)
    {
        system("cls");


        printf("       [[[NUB CANTEEN SYSTEM]]]\n");
        printf("=====================================\n");

        printf("\n1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Customer Panel\n");
        printf("4. Exit\n");

        printf("\nEnter Choice : ");

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                adminLogin();
                break;


            case 2:
                employeeLogin();
                break;


            case 3:
                customerPanel();
                break;


            case 4:
                printf("\nThank You!\n");
                exit(0);


            default:
                printf("\nInvalid Choice!\n");

                pauseScreen();
        }
    }
}


void adminLogin()       //ADMIN
{
    char username[30];
    char password[30];
    int attempt = 0;

    while(attempt < 3)
    {
        system("cls");

        printf("         ==ADMIN LOGIN==\n");
        printf("=====================================\n");


        printf("\nUsername : ");
        scanf("%29s", username);
        getchar();


        printf("Password : ");
        inputPassword(password);
        printf("\n");


        if(strcmp(username, ADMIN_USER) == 0 &&
           strcmp(password, ADMIN_PASS) == 0)
        {
            printf("\nLogin Successful!\n");
            pauseScreen();
            adminPanel();

            return;
        }

        attempt++;
        printf("\nWrong Username or Password!\n");
        printf("Remaining Attempt : %d\n",
               3 - attempt);

        pauseScreen();
    }

    printf("\nAccess Denied!\n");
    pauseScreen();
}



void employeeLogin()       //EMPLOYEE
{
    char username[30];
    char password[30];
    int attempt = 0;

    while(attempt < 3)
    {
        system("cls");
        printf("         ==EMPLOYEE LOGIN==\n");
        printf("=====================================\n");

        printf("\nUsername : ");
        scanf("%29s", username);
        getchar();


        printf("Password : ");
        inputPassword(password);
        printf("\n");


        if(strcmp(username, EMP_USER) == 0 &&
           strcmp(password, EMP_PASS) == 0)
        {
            printf("\nLogin Successful!\n");
            pauseScreen();
            employeePanel();

            return;
        }

        attempt++;
        printf("\nWrong Username or Password!\n");
        printf("Remaining Attempt : %d\n",
               3 - attempt);

        pauseScreen();
    }
    printf("\nAccess Denied!\n");
    pauseScreen();
}




void inputPassword(char password[])
{
    int i = 0;
    char ch;

#ifdef _WIN32
    while(1)
    {
        ch = getch();
        if(ch == 13)
        {
            password[i] = '\0';
            break;
        }else if(ch == 8)
        {
            if(i > 0)
            {
                i--;
                printf("\b \b");
            }
        }else{
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




void adminPanel()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("         ==ADMIN DASHBOARD==\n");
        printf("=====================================\n");
        printf("\n1. Food Management\n");
        printf("2. Customer Management\n");
        printf("3. Sales & Reports\n");
        printf("4. Pending Orders\n");
        printf("5. Logout\n");
        printf("\nEnter Choice : ");

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                printf("\nFood Management Module\n");
                pauseScreen();
                break;

            case 2:
                printf("\nCustomer Management Module\n");
                printf("Total Customers : %d\n",
                       customerCount);

                pauseScreen();
                break;

            case 3:
                salesStatisticsMenu();
                break;

            case 4:
                printf("\nPending Orders Module\n");
                if(front == NULL)
                {
                    printf("No Pending Orders.\n");
                }else{
                    printf("Pending Order Available.\n");
                }

                pauseScreen();
                break;

            case 5:
                printf("\nAdmin Logged Out.\n");
                pauseScreen();
                return;

            default:
                printf("\nInvalid Choice!\n");
                pauseScreen();
        }
    }
}



void employeePanel()
{
    int choice;


    while(1)
    {
        system("cls");
        printf("       ==EMPLOYEE DASHBOARD==\n");
        printf("=====================================\n");
        printf("\n1. Add Food\n");
        printf("\n2. Delete Food\n");
        printf("\n3. Update Food\n");
        printf("\n4. Display Food Menu\n");
        printf("\n5. Take Customer Order\n");
        printf("\n6. Print Receipt\n");
        printf("\n7. Logout\n");
        printf("\nEnter Choice : ");

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                addFood();
                break;

            case 2:
                deleteFood();
                break;

            case 3:
                updateFood();
                break;

            case 4:
                displayFood();
                break;

            case 5:
                customerOrder();
                break;

            case 6:
                billing();
                break;

            case 7:
                printf("\nEmployee Logged Out.\n");
                pauseScreen();
                return;

            default:
                printf("\nInvalid Choice!\n");

                pauseScreen();
        }
    }
}


struct Food {
    int id;
    char name[30];
    float price;
};

struct Food menu[100];
struct Order orders[100];
int foodCount = 0;
int totalOrders = 0;


void addFood()
{
    FILE *fp;

    fp = fopen("menuTest.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d %s %f", &menu[foodCount].id, menu[foodCount].name, &menu[foodCount].price) == 3)
        {
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
            return 0 ;
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

    fp = fopen("menuTest.txt", "a");
    if (fp==NULL)
    {
        printf("Error opening menu.\n");

    }

    fprintf(fp, "%d %s %.2f\n",
            item.id,
            item.name,
            item.price);

    menu[foodCount] = item;
    foodCount++;

    printf("\nFood Added Successfully!\n");

    fclose(fp);

    return 0;

}


int displayFood()
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

struct Order
{
    char name[50];
    char phone[20];
    char item[30];
    int quantity;
    float totalPrice;
};


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

int customerOrder()
{

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

int deleteFood()
{

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

int updateFood()
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

void customerPanel()
{
    int choice;


    while(1)
    {
        system("cls");
        printf("        ==CUSTOMER PANEL==\n");
        printf("=====================================\n");
        printf("\n1. View Food Menu\n");
        printf("2. Customer Registration\n");
        printf("3. Customer Login & Order\n");
        printf("4. Exit\n");
        printf("\nEnter Choice : ");

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                displayFood();
                break;

            case 2:
                customerRegistration();
                break;

            case 3:
                customerOrder();
                break;

            case 4:
                return;

            default:
                printf("\nInvalid Choice!\n");

                pauseScreen();
        }
    }
}



void addFood()
{
    system("cls");
    printf("              ADD FOOD\n");
    printf("=====================================\n");
    printf("\n HEHEHE\n");
    printf("Employee will add food here.\n");

    pauseScreen();
}

void displayFood()
{
    system("cls");
    printf("              FOOD MENU\n");
    printf("=====================================\n");
    printf("\nMEOw\n");
    printf("Food display will be implemented here.\n");

    pauseScreen();
}


void customerRegistration()
{
    char phone[30];
    system("cls");
    printf("     ==CUSTOMER REGISTRATION==\n");
    printf("=====================================\n");

    if(customerCount >= MAX_CUSTOMERS)
    {
        printf("\nCustomer limit reached!\n");
        pauseScreen();
        return;
    }
    printf("\nCustomer Name : ");
    scanf(" %[^\n]",
          customers[customerCount].name);
    printf("Mobile Number : ");
    scanf("%29s", phone);
    getchar();

    if(!validPhone(phone))
    {
        printf("\nREGISTRATION DECLINED\n");
        printf("Phone number must be exactly 11 digits.\n");
        pauseScreen();
        return;
    } strcpy(customers[customerCount].phone,
           phone);
    customers[customerCount].id =
        generateCustomerID();

    printf("      REGISTRATION SUCCESSFUL\n");
    printf("===============Welcome===================\n");
    printf("\nCustomer Name : %s",
           customers[customerCount].name);
    printf("\nCustomer ID   : %d",
           customers[customerCount].id);
    printf("\nPhone Number  : %s\n",
           customers[customerCount].phone);

    customerCount++;
    pauseScreen();
}

int validPhone(char phone[])
{
    int i;
    if(strlen(phone) != 11)
    {
        return 0;
    }
    for(i = 0; i < 11; i++)
    {
        if(phone[i] < '0' ||
           phone[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

int generateCustomerID()
{
    return 1001 + customerCount;
}

int customerLogin()
{
    int id;
    int i;
    system("cls");
    printf("        ==CUSTOMER LOGIN==\n");
    printf("=====================================\n");


    if(customerCount == 0)
    {
        printf("\nNo customer registered yet.\n");
        pauseScreen();
        return -1;
    }

    printf("\nEnter Customer ID : ");
    scanf("%d", &id);
    getchar();


    for(i = 0; i < customerCount; i++)
    {
        if(customers[i].id == id)
        {
            printf("\nLogin Successful!\n");

            printf("Welcome, %s!\n",
                   customers[i].name);

            pauseScreen();
            return id;
        }
    }
    printf("\nCustomer ID not found!\n");
    pauseScreen();
    return -1;
}


void customerOrder()
{
    int customerID;
    int choice;
    Order *newOrder;
    system("cls");
    printf("          CUSTOMER ORDER\n");
    printf("=====================================\n");
    printf("\n1. New Customer Registration\n");
    printf("2. Existing Customer Login\n");
    printf("\nEnter Choice : ");

    scanf("%d", &choice);
    getchar();

    if(choice == 1)
    {
        int oldCount = customerCount;
        customerRegistration();
        if(customerCount == oldCount)
        {
            return;
        }
        customerID = customers[customerCount - 1].id;
    }else if(choice == 2)
    {
        customerID = customerLogin();
        if(customerID == -1)
        {
            return;
        }
    }else{
        printf("\nInvalid Choice!\n");
        pauseScreen();
        return;
    }
    newOrder =(Order *)malloc(sizeof(Order));
    if(newOrder == NULL)
    {
        printf("\nMemory Allocation Error!\n");
        pauseScreen();
        return;
    }
    newOrder->orderID = nextOrderID++;
    strcpy(newOrder->customerName, customers[customerID - 1001].name);

    printf("\nFood Name : ");
    scanf(" %[^\n]", newOrder->foodName);

    printf("Quantity : ");
    scanf("%d",&newOrder->quantity);

    printf("Unit Price : ");
    scanf("%f",&newOrder->unitPrice);

    getchar();

    if(newOrder->quantity <= 0 || newOrder->unitPrice < 0)
    {
        printf("\nInvalid Order Information!\n");
        free(newOrder);
        pauseScreen();
        return;
    }
    newOrder->totalPrice = newOrder->quantity * newOrder->unitPrice;
    newOrder->next = NULL;

    if(front == NULL)
    {
        front = newOrder;
        rear = newOrder;
    }else{
        rear->next = newOrder;
        rear = newOrder;
    }
    printf("        ORDER SUCCESSFUL\n");
    printf("=====================================\n");
    printf("\nOrder ID : %d", newOrder->orderID);
    printf("\nCustomer : %s", newOrder->customerName);
    printf("\nFood     : %s", newOrder->foodName);
    printf("\nQuantity : %d", newOrder->quantity);
    printf("\nTotal    : %.2f BDT\n", newOrder->totalPrice);

    pauseScreen();
}


void billing()
{
    Order *temp;
    system("cls");
    printf("             BILLING\n");
    printf("=====================================\n");

    if(front == NULL)
    {
        printf("\nNo Pending Order!\n");
        pauseScreen();
        return;
    }

    printReceipt(front);
    temp = front;
    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }

    free(temp);
    printf("\nOrder removed from pending queue.\n");

    pauseScreen();
}

void printReceipt(Order *order)
{
    float vat;
    float discount = 0;
    float grandTotal;
    vat = order->totalPrice * 0.05;
    grandTotal = order->totalPrice + vat -discount;

    printf("\n=====================================\n");
    printf("          NUB CANTEEN\n");
    printf("             RECEIPT\n");
    printf("=====================================\n");
    printf("\nOrder ID      : %d", order->orderID);
    printf("\nCustomer      : %s", order->customerName);
    printf("\nFood          : %s", order->foodName);
    printf("\nQuantity      : %d", order->quantity);
    printf("\nUnit Price    : %.2f BDT", order->unitPrice);
    printf("\n-------------------------------------");
    printf("\nSubtotal      : %.2f BDT", order->totalPrice);
    printf("\nVAT (5%%)      : %.2f BDT", vat);
    printf("\nDiscount      : %.2f BDT", discount);
    printf("\n-------------------------------------");
    printf("\nGrand Total   : %.2f BDT", grandTotal);
    printf("\n=====================================\n");
    printf("       ORDER SUCCESSFUL!\n");
    printf("       Thank You For Ordering!\n");
    printf("=====================================\n");
}

void salesStatisticsMenu()
{
    int choice;
    while(1)
    {
        system("cls");
        printf("       NUB CANTEEN SALES PANEL\n");
        printf("=====================================\n");
        printf("\n1. Total Income Report");
        printf("\n2. Daily Sales Report");
        printf("\n3. Monthly Sales Report");
        printf("\n4. Highest Sale");
        printf("\n5. Lowest Sale");
        printf("\n6. Average Sale");
        printf("\n0. Back");
        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                incomeSummary();
                break;

            case 2:
                dailySalesReport();
                break;

            case 3:
                monthlySalesReport();
                break;

            case 4:
                highestSale();
                break;

            case 5:
                lowestSale();
                break;

            case 6:
                averageSale();
                break;

            case 0:
                return;

            default:
                printf("\nInvalid Choice!\n");

                pauseScreen();
        }
    }
}


//sales
void incomeSummary()
{
     printf("        TOTAL INCOME REPORT\n");
    printf("=====================================\n");
    printf("\nIncome Report Module\n");
    printf("Sales calculation will be implemented here.\n");

    pauseScreen();
}


void dailySalesReport()
{
    printf("         DAILY SALES REPORT\n");
    printf("=====================================\n");
    printf("\nDaily Sales Report Module\n");
    printf("Daily sales calculation will be implemented here.\n");

    pauseScreen();
}

void monthlySalesReport()
{
    printf("        MONTHLY SALES REPORT\n");
    printf("=====================================\n");
    printf("\nMonthly Sales Report Module\n");
    printf("Monthly sales calculation will be implemented here.\n");

    pauseScreen();
}

void highestSale()
{
    printf("\n=====================================\n");
    printf("            HIGHEST SALE\n");
    printf("=====================================\n");
    printf("\nHighest Sale Module\n");
    printf("Highest sale calculation will be implemented here.\n");

    pauseScreen();
}


void lowestSale()
{
    printf("             LOWEST SALE\n");
    printf("=====================================\n");
    printf("\nLowest Sale Module\n");
    printf("Lowest sale calculation will be implemented here.\n");

    pauseScreen();
}
void averageSale()
{
    printf("\n=====================================\n");
    printf("             AVERAGE SALE\n");
    printf("=====================================\n");
    printf("\nAverage Sale Module\n");
    printf("Average sale calculation will be implemented here.\n");

    pauseScreen();
}


//NUB
