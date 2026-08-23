// ============================================================
//              NUB CANTEEN MANAGEMENT SYSTEM
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <conio.h>
#endif

// ============================================================
// CONSTANTS
// ============================================================

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

#define EMP_USER "employee"
#define EMP_PASS "1234"

#define MAX_FOOD 100
#define MAX_CUSTOMERS 100

#define MENU_FILE "menuTest.txt"
#define CUSTOMER_FILE "Customer_Data.txt"
#define SALES_FILE "Sales_Data.txt"

// ============================================================
// STRUCTURES
// ============================================================

typedef struct
{
    int id;
    char name[50];
    float price;
} Food;

typedef struct
{
    int id;
    char name[50];
    char phone[20];
} Customer;

typedef struct Order
{
    int orderID;
    int customerID;

    char customerName[50];
    char foodName[50];

    int quantity;
    float unitPrice;
    float totalPrice;

    struct Order *next;

} Order;

// ============================================================
// GLOBAL VARIABLES
// ============================================================

Food menu[MAX_FOOD];
int foodCount = 0;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

Order *front = NULL;
Order *rear = NULL;

int nextOrderID = 1001;

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

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

void loadMenu();
void saveMenu();

void clearInputBuffer();
void pauseScreen();
void clearScreen();

int findFoodByID(int id);
int findFoodByName(char name[]);

void saveSale(Order *order, float grandTotal);

// ============================================================
// MAIN
// ============================================================

int main()
{
    loadMenu();

    mainMenu();

    return 0;
}

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* clear buffer */
    }
}

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    getchar();
}

// ============================================================
// LOAD MENU FROM FILE
// ============================================================

void loadMenu()
{
    FILE *fp;

    foodCount = 0;

    fp = fopen(MENU_FILE, "r");

    if (fp == NULL)
    {
        return;
    }

    while (foodCount < MAX_FOOD &&
           fscanf(fp,
                  "%d %49s %f",
                  &menu[foodCount].id,
                  menu[foodCount].name,
                  &menu[foodCount].price) == 3)
    {
        foodCount++;
    }

    fclose(fp);
}

// ============================================================
// SAVE MENU TO FILE
// ============================================================

void saveMenu()
{
    FILE *fp;
    int i;

    fp = fopen(MENU_FILE, "w");

    if (fp == NULL)
    {
        printf("\nError opening menu file!\n");
        return;
    }

    for (i = 0; i < foodCount; i++)
    {
        fprintf(fp,
                "%d %s %.2f\n",
                menu[i].id,
                menu[i].name,
                menu[i].price);
    }

    fclose(fp);
}

// ============================================================
// FIND FOOD BY ID
// ============================================================

int findFoodByID(int id)
{
    int i;

    for (i = 0; i < foodCount; i++)
    {
        if (menu[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// ============================================================
// FIND FOOD BY NAME
// ============================================================

int findFoodByName(char name[])
{
    int i;

    for (i = 0; i < foodCount; i++)
    {
        if (strcmp(menu[i].name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

// ============================================================
// MAIN MENU
// ============================================================

void mainMenu()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("=====================================\n");
        printf("       NUB CANTEEN MANAGEMENT\n");
        printf("=====================================\n");

        printf("\n1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Customer Panel\n");
        printf("4. Exit\n");

        printf("\nEnter Choice : ");

        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();

            printf("\nInvalid input!\n");
            pauseScreen();
            continue;
        }

        clearInputBuffer();

        switch (choice)
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

// ============================================================
// PASSWORD INPUT
// ============================================================

void inputPassword(char password[])
{
    int i = 0;
    char ch;

#ifdef _WIN32

    while (1)
    {
        ch = getch();

        if (ch == 13)
        {
            password[i] = '\0';
            break;
        }

        if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            if (i < 29)
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

// ============================================================
// ADMIN LOGIN
// ============================================================

void adminLogin()
{
    char username[30];
    char password[30];

    int attempt = 0;

    while (attempt < 3)
    {
        clearScreen();

        printf("=====================================\n");
        printf("             ADMIN LOGIN\n");
        printf("=====================================\n");

        printf("\nUsername : ");
        scanf("%29s", username);
        clearInputBuffer();

        printf("Password : ");
        inputPassword(password);

        printf("\n");

        if (strcmp(username, ADMIN_USER) == 0 &&
            strcmp(password, ADMIN_PASS) == 0)
        {
            printf("\nLogin Successful!\n");
            pauseScreen();

            adminPanel();

            return;
        }

        attempt++;

        printf("\nWrong Username or Password!\n");
        printf("Remaining Attempts : %d\n", 3 - attempt);

        pauseScreen();
    }

    printf("\nAccess Denied!\n");
    pauseScreen();
}

// ============================================================
// EMPLOYEE LOGIN
// ============================================================

void employeeLogin()
{
    char username[30];
    char password[30];

    int attempt = 0;

    while (attempt < 3)
    {
        clearScreen();

        printf("=====================================\n");
        printf("           EMPLOYEE LOGIN\n");
        printf("=====================================\n");

        printf("\nUsername : ");
        scanf("%29s", username);
        clearInputBuffer();

        printf("Password : ");
        inputPassword(password);

        printf("\n");

        if (strcmp(username, EMP_USER) == 0 &&
            strcmp(password, EMP_PASS) == 0)
        {
            printf("\nLogin Successful!\n");
            pauseScreen();

            employeePanel();

            return;
        }

        attempt++;

        printf("\nWrong Username or Password!\n");
        printf("Remaining Attempts : %d\n", 3 - attempt);

        pauseScreen();
    }

    printf("\nAccess Denied!\n");
    pauseScreen();
}

// ============================================================
// ADMIN PANEL
// ============================================================

void adminPanel()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("=====================================\n");
        printf("          ADMIN DASHBOARD\n");
        printf("=====================================\n");

        printf("\n1. Food Management\n");
        printf("2. Customer Management\n");
        printf("3. Sales & Reports\n");
        printf("4. Pending Orders\n");
        printf("5. Logout\n");

        printf("\nEnter Choice : ");

        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();

            printf("\nInvalid input!\n");
            pauseScreen();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
            {
                int foodChoice;

                while (1)
                {
                    clearScreen();

                    printf("=====================================\n");
                    printf("          FOOD MANAGEMENT\n");
                    printf("=====================================\n");

                    printf("\n1. Add Food\n");
                    printf("2. Display Food\n");
                    printf("3. Update Food\n");
                    printf("4. Delete Food\n");
                    printf("5. Back\n");

                    printf("\nEnter Choice : ");
                    scanf("%d", &foodChoice);
                    clearInputBuffer();

                    switch (foodChoice)
                    {
                        case 1:
                            addFood();
                            break;

                        case 2:
                            displayFood();
                            break;

                        case 3:
                            updateFood();
                            break;

                        case 4:
                            deleteFood();
                            break;

                        case 5:
                            break;

                        default:
                            printf("\nInvalid Choice!\n");
                            pauseScreen();
                            continue;
                    }

                    if (foodChoice == 5)
                        break;
                }

                break;
            }

            case 2:

                clearScreen();

                printf("=====================================\n");
                printf("        CUSTOMER MANAGEMENT\n");
                printf("=====================================\n");

                printf("\nTotal Customers : %d\n", customerCount);

                pauseScreen();

                break;

            case 3:

                salesStatisticsMenu();

                break;

            case 4:

                clearScreen();

                printf("=====================================\n");
                printf("          PENDING ORDERS\n");
                printf("=====================================\n");

                if (front == NULL)
                {
                    printf("\nNo Pending Orders.\n");
                }
                else
                {
                    Order *temp = front;

                    printf("\nPending Orders:\n\n");

                    while (temp != NULL)
                    {
                        printf("Order ID : %d\n", temp->orderID);
                        printf("Customer : %s\n", temp->customerName);
                        printf("Food     : %s\n", temp->foodName);
                        printf("Quantity : %d\n", temp->quantity);
                        printf("Total    : %.2f BDT\n",
                               temp->totalPrice);

                        printf("-------------------------------------\n");

                        temp = temp->next;
                    }
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

// ============================================================
// EMPLOYEE PANEL
// ============================================================

void employeePanel()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("=====================================\n");
        printf("        EMPLOYEE DASHBOARD\n");
        printf("=====================================\n");

        printf("\n1. Add Food\n");
        printf("2. Delete Food\n");
        printf("3. Update Food\n");
        printf("4. Display Food Menu\n");
        printf("5. Take Customer Order\n");
        printf("6. Print Receipt\n");
        printf("7. Logout\n");

        printf("\nEnter Choice : ");

        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();

            printf("\nInvalid input!\n");
            pauseScreen();
            continue;
        }

        clearInputBuffer();

        switch (choice)
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

// ============================================================
// ADD FOOD
// ============================================================

void addFood()
{
    Food item;

    clearScreen();

    printf("=====================================\n");
    printf("              ADD FOOD\n");
    printf("=====================================\n");

    loadMenu();

    if (foodCount >= MAX_FOOD)
    {
        printf("\nFood menu is full!\n");
        pauseScreen();
        return;
    }

    printf("\nEnter Food ID : ");
    scanf("%d", &item.id);
    clearInputBuffer();

    if (findFoodByID(item.id) != -1)
    {
        printf("\nFood ID already exists!\n");
        pauseScreen();
        return;
    }

    printf("Enter Food Name : ");
    scanf("%49s", item.name);
    clearInputBuffer();

    if (findFoodByName(item.name) != -1)
    {
        printf("\nFood name already exists!\n");
        pauseScreen();
        return;
    }

    printf("Enter Food Price : ");
    scanf("%f", &item.price);
    clearInputBuffer();

    if (item.price < 0)
    {
        printf("\nPrice cannot be negative!\n");
        pauseScreen();
        return;
    }

    menu[foodCount] = item;
    foodCount++;

    saveMenu();

    printf("\nFood Added Successfully!\n");

    pauseScreen();
}

// ============================================================
// DISPLAY FOOD
// ============================================================

void displayFood()
{
    int i;

    clearScreen();

    printf("============================================\n");
    printf("                 FOOD MENU\n");
    printf("============================================\n");

    loadMenu();

    if (foodCount == 0)
    {
        printf("\nNo food available.\n");
        pauseScreen();
        return;
    }

    printf("\n%-10s %-20s %-10s\n",
           "ID",
           "Food Name",
           "Price");

    printf("--------------------------------------------\n");

    for (i = 0; i < foodCount; i++)
    {
        printf("%-10d %-20s %.2f BDT\n",
               menu[i].id,
               menu[i].name,
               menu[i].price);
    }

    printf("--------------------------------------------\n");

    pauseScreen();
}

// ============================================================
// DELETE FOOD
// ============================================================

void deleteFood()
{
    int id;
    int index;
    int i;

    clearScreen();

    printf("=====================================\n");
    printf("             DELETE FOOD\n");
    printf("=====================================\n");

    loadMenu();

    if (foodCount == 0)
    {
        printf("\nNo food available.\n");
        pauseScreen();
        return;
    }

    printf("\nEnter Food ID to Delete : ");
    scanf("%d", &id);
    clearInputBuffer();

    index = findFoodByID(id);

    if (index == -1)
    {
        printf("\nFood ID Not Found!\n");
        pauseScreen();
        return;
    }

    for (i = index; i < foodCount - 1; i++)
    {
        menu[i] = menu[i + 1];
    }

    foodCount--;

    saveMenu();

    printf("\nFood Deleted Successfully!\n");

    pauseScreen();
}

// ============================================================
// UPDATE FOOD
// ============================================================

void updateFood()
{
    int id;
    int index;
    int choice;

    clearScreen();

    printf("=====================================\n");
    printf("             UPDATE FOOD\n");
    printf("=====================================\n");

    loadMenu();

    if (foodCount == 0)
    {
        printf("\nNo food available.\n");
        pauseScreen();
        return;
    }

    printf("\nEnter Food ID to Update : ");
    scanf("%d", &id);
    clearInputBuffer();

    index = findFoodByID(id);

    if (index == -1)
    {
        printf("\nFood ID Not Found!\n");
        pauseScreen();
        return;
    }

    printf("\nCurrent Food Name : %s\n",
           menu[index].name);

    printf("Current Price : %.2f BDT\n",
           menu[index].price);

    printf("\n1. Update Name\n");
    printf("2. Update Price\n");
    printf("3. Update Both\n");
    printf("4. Cancel\n");

    printf("\nEnter Choice : ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1 || choice == 3)
    {
        char newName[50];

        printf("\nEnter New Food Name : ");
        scanf("%49s", newName);
        clearInputBuffer();

        if (findFoodByName(newName) != -1 &&
            strcmp(menu[index].name, newName) != 0)
        {
            printf("\nFood name already exists!\n");
            pauseScreen();
            return;
        }

        strcpy(menu[index].name, newName);
    }

    if (choice == 2 || choice == 3)
    {
        float newPrice;

        printf("Enter New Price : ");
        scanf("%f", &newPrice);
        clearInputBuffer();

        if (newPrice < 0)
        {
            printf("\nInvalid Price!\n");
            pauseScreen();
            return;
        }

        menu[index].price = newPrice;
    }

    if (choice == 4)
    {
        return;
    }

    if (choice < 1 || choice > 4)
    {
        printf("\nInvalid Choice!\n");
        pauseScreen();
        return;
    }

    saveMenu();

    printf("\nFood Updated Successfully!\n");

    pauseScreen();
}

// ============================================================
// CUSTOMER PANEL
// ============================================================

void customerPanel()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("=====================================\n");
        printf("           CUSTOMER PANEL\n");
        printf("=====================================\n");

        printf("\n1. View Food Menu\n");
        printf("2. Customer Registration\n");
        printf("3. Customer Login & Order\n");
        printf("4. Exit\n");

        printf("\nEnter Choice : ");

        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();

            printf("\nInvalid input!\n");
            pauseScreen();
            continue;
        }

        clearInputBuffer();

        switch (choice)
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

// ============================================================
// PHONE VALIDATION
// ============================================================

int validPhone(char phone[])
{
    int i;

    if (strlen(phone) != 11)
    {
        return 0;
    }

    for (i = 0; i < 11; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }
    }

    return 1;
}

// ============================================================
// GENERATE CUSTOMER ID
// ============================================================

int generateCustomerID()
{
    return 1001 + customerCount;
}

// ============================================================
// CUSTOMER REGISTRATION
// ============================================================

void customerRegistration()
{
    char phone[20];

    clearScreen();

    printf("=====================================\n");
    printf("        CUSTOMER REGISTRATION\n");
    printf("=====================================\n");

    if (customerCount >= MAX_CUSTOMERS)
    {
        printf("\nCustomer limit reached!\n");
        pauseScreen();
        return;
    }

    printf("\nCustomer Name : ");

    scanf(" %49[^\n]", customers[customerCount].name);
    clearInputBuffer();

    printf("Mobile Number : ");

    scanf("%19s", phone);
    clearInputBuffer();

    if (!validPhone(phone))
    {
        printf("\nREGISTRATION DECLINED\n");
        printf("Phone number must contain exactly 11 digits.\n");

        pauseScreen();
        return;
    }

    strcpy(customers[customerCount].phone, phone);

    customers[customerCount].id =
        generateCustomerID();

    printf("\n=====================================\n");
    printf("       REGISTRATION SUCCESSFUL\n");
    printf("=====================================\n");

    printf("\nCustomer Name : %s",
           customers[customerCount].name);

    printf("\nCustomer ID   : %d",
           customers[customerCount].id);

    printf("\nPhone Number  : %s\n",
           customers[customerCount].phone);

    customerCount++;

    pauseScreen();
}

// ============================================================
// CUSTOMER LOGIN
// ============================================================

int customerLogin()
{
    int id;
    int i;

    clearScreen();

    printf("=====================================\n");
    printf("           CUSTOMER LOGIN\n");
    printf("=====================================\n");

    if (customerCount == 0)
    {
        printf("\nNo customer registered yet.\n");
        pauseScreen();

        return -1;
    }

    printf("\nEnter Customer ID : ");
    scanf("%d", &id);
    clearInputBuffer();

    for (i = 0; i < customerCount; i++)
    {
        if (customers[i].id == id)
        {
            printf("\nLogin Successful!\n");
            printf("Welcome, %s!\n",
                   customers[i].name);

            pauseScreen();

            return id;
        }
    }

    printf("\nCustomer ID Not Found!\n");

    pauseScreen();

    return -1;
}

// ============================================================
// CUSTOMER ORDER
// ============================================================

void customerOrder()
{
    int choice;
    int customerID;
    int customerIndex;

    int foodID;
    int foodIndex;

    int quantity;

    Order *newOrder;

    clearScreen();

    printf("=====================================\n");
    printf("           CUSTOMER ORDER\n");
    printf("=====================================\n");

    printf("\n1. New Customer Registration\n");
    printf("2. Existing Customer Login\n");

    printf("\nEnter Choice : ");

    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1)
    {
        int oldCount = customerCount;

        customerRegistration();

        if (customerCount == oldCount)
        {
            return;
        }

        customerID =
            customers[customerCount - 1].id;
    }
    else if (choice == 2)
    {
        customerID = customerLogin();

        if (customerID == -1)
        {
            return;
        }
    }
    else
    {
        printf("\nInvalid Choice!\n");
        pauseScreen();

        return;
    }

    customerIndex = customerID - 1001;

    if (customerIndex < 0 ||
        customerIndex >= customerCount)
    {
        printf("\nInvalid Customer ID!\n");
        pauseScreen();

        return;
    }

    loadMenu();

    if (foodCount == 0)
    {
        printf("\nNo food available in menu!\n");
        pauseScreen();

        return;
    }

    displayFood();

    printf("\nEnter Food ID : ");

    scanf("%d", &foodID);
    clearInputBuffer();

    foodIndex = findFoodByID(foodID);

    if (foodIndex == -1)
    {
        printf("\nFood ID Not Found!\n");
        pauseScreen();

        return;
    }

    printf("Enter Quantity : ");

    scanf("%d", &quantity);
    clearInputBuffer();

    if (quantity <= 0)
    {
        printf("\nInvalid Quantity!\n");
        pauseScreen();

        return;
    }

    newOrder = (Order *)malloc(sizeof(Order));

    if (newOrder == NULL)
    {
        printf("\nMemory Allocation Error!\n");
        pauseScreen();

        return;
    }

    newOrder->orderID = nextOrderID++;

    newOrder->customerID = customerID;

    strcpy(newOrder->customerName,
           customers[customerIndex].name);

    strcpy(newOrder->foodName,
           menu[foodIndex].name);

    newOrder->quantity = quantity;

    // Price is taken automatically from menu
    newOrder->unitPrice =
        menu[foodIndex].price;

    newOrder->totalPrice =
        newOrder->unitPrice *
        newOrder->quantity;

    newOrder->next = NULL;

    // QUEUE INSERT
    if (front == NULL)
    {
        front = newOrder;
        rear = newOrder;
    }
    else
    {
        rear->next = newOrder;
        rear = newOrder;
    }

    printf("\n=====================================\n");
    printf("          ORDER SUCCESSFUL\n");
    printf("=====================================\n");

    printf("\nOrder ID : %d",
           newOrder->orderID);

    printf("\nCustomer : %s",
           newOrder->customerName);

    printf("\nFood     : %s",
           newOrder->foodName);

    printf("\nQuantity : %d",
           newOrder->quantity);

    printf("\nUnit Price : %.2f BDT",
           newOrder->unitPrice);

    printf("\nTotal    : %.2f BDT\n",
           newOrder->totalPrice);

    pauseScreen();
}

// ============================================================
// BILLING
// ============================================================

void billing()
{
    Order *temp;

    clearScreen();

    printf("=====================================\n");
    printf("              BILLING\n");
    printf("=====================================\n");

    if (front == NULL)
    {
        printf("\nNo Pending Order!\n");
        pauseScreen();

        return;
    }

    temp = front;

    printReceipt(temp);

    // SAVE SALE
    {
        float vat = temp->totalPrice * 0.05;
        float grandTotal = temp->totalPrice + vat;

        saveSale(temp, grandTotal);
    }

    // DEQUEUE
    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);

    printf("\nOrder removed from pending queue.\n");

    pauseScreen();
}

// ============================================================
// PRINT RECEIPT
// ============================================================

void printReceipt(Order *order)
{
    float vat;
    float discount = 0;
    float grandTotal;

    vat = order->totalPrice * 0.05;

    grandTotal =
        order->totalPrice +
        vat -
        discount;

    printf("\n=====================================\n");
    printf("            NUB CANTEEN\n");
    printf("               RECEIPT\n");
    printf("=====================================\n");

    printf("\nOrder ID      : %d",
           order->orderID);

    printf("\nCustomer      : %s",
           order->customerName);

    printf("\nFood          : %s",
           order->foodName);

    printf("\nQuantity      : %d",
           order->quantity);

    printf("\nUnit Price    : %.2f BDT",
           order->unitPrice);

    printf("\n-------------------------------------");

    printf("\nSubtotal      : %.2f BDT",
           order->totalPrice);

    printf("\nVAT (5%%)      : %.2f BDT",
           vat);

    printf("\nDiscount      : %.2f BDT",
           discount);

    printf("\n-------------------------------------");

    printf("\nGrand Total   : %.2f BDT",
           grandTotal);

    printf("\n=====================================\n");
    printf("        ORDER COMPLETED!\n");
    printf("=====================================\n");
}

// ============================================================
// SAVE SALES DATA
// ============================================================

void saveSale(Order *order, float grandTotal)
{
    FILE *fp;

    fp = fopen(SALES_FILE, "a");

    if (fp == NULL)
    {
        return;
    }

    fprintf(fp,
            "%d %s %s %d %.2f %.2f\n",
            order->orderID,
            order->customerName,
            order->foodName,
            order->quantity,
            order->totalPrice,
            grandTotal);

    fclose(fp);
}

// ============================================================
// SALES STATISTICS MENU
// ============================================================

void salesStatisticsMenu()
{
    int choice;

    while (1)
    {
        clearScreen();

        printf("=====================================\n");
        printf("        NUB CANTEEN SALES PANEL\n");
        printf("=====================================\n");

        printf("\n1. Total Income Report\n");
        printf("2. Daily Sales Report\n");
        printf("3. Monthly Sales Report\n");
        printf("4. Highest Sale\n");
        printf("5. Lowest Sale\n");
        printf("6. Average Sale\n");
        printf("0. Back\n");

        printf("\nEnter Choice : ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
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

// ============================================================
// TOTAL INCOME
// ============================================================

void incomeSummary()
{
    FILE *fp;

    int orderID;
    char customerName[50];
    char foodName[50];

    int quantity;

    float subtotal;
    float grandTotal;

    float totalIncome = 0;

    int count = 0;

    clearScreen();

    printf("=====================================\n");
    printf("         TOTAL INCOME REPORT\n");
    printf("=====================================\n");

    fp = fopen(SALES_FILE, "r");

    if (fp == NULL)
    {
        printf("\nNo sales data available.\n");
        pauseScreen();

        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %d %f %f",
                  &orderID,
                  customerName,
                  foodName,
                  &quantity,
                  &subtotal,
                  &grandTotal) == 6)
    {
        totalIncome += grandTotal;
        count++;
    }

    fclose(fp);

    printf("\nTotal Completed Orders : %d",
           count);

    printf("\nTotal Income           : %.2f BDT\n",
           totalIncome);

    pauseScreen();
}

// ============================================================
// DAILY SALES REPORT
// ============================================================

void dailySalesReport()
{
    FILE *fp;

    int orderID;
    char customerName[50];
    char foodName[50];

    int quantity;

    float subtotal;
    float grandTotal;

    float total = 0;
    int count = 0;

    clearScreen();

    printf("=====================================\n");
    printf("          DAILY SALES REPORT\n");
    printf("=====================================\n");

    printf("\nNote: This report uses all recorded sales\n");
    printf("because the current sales file does not store dates.\n");

    fp = fopen(SALES_FILE, "r");

    if (fp == NULL)
    {
        printf("\nNo sales data available.\n");
        pauseScreen();

        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %d %f %f",
                  &orderID,
                  customerName,
                  foodName,
                  &quantity,
                  &subtotal,
                  &grandTotal) == 6)
    {
        total += grandTotal;
        count++;
    }

    fclose(fp);

    printf("\nSales Count : %d",
           count);

    printf("\nSales Total : %.2f BDT\n",
           total);

    pauseScreen();
}

// ============================================================
// MONTHLY SALES REPORT
// ============================================================

void monthlySalesReport()
{
    FILE *fp;

    int orderID;
    char customerName[50];
    char foodName[50];

    int quantity;

    float subtotal;
    float grandTotal;

    float total = 0;
    int count = 0;

    clearScreen();

    printf("=====================================\n");
    printf("         MONTHLY SALES REPORT\n");
    printf("=====================================\n");

    printf("\nNote: Date/month information is not currently\n");
    printf("stored in Sales_Data.txt.\n");

    fp = fopen(SALES_FILE, "r");

    if (fp == NULL)
    {
        printf("\nNo sales data available.\n");
        pauseScreen();

        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %d %f %f",
                  &orderID,
                  customerName,
                  foodName,
                  &quantity,
                  &subtotal,
                  &grandTotal) == 6)
    {
        total += grandTotal;
        count++;
    }

    fclose(fp);

    printf("\nRecorded Sales : %d",
           count);

    printf("\nRecorded Income : %.2f BDT\n",
           total);

    pauseScreen();
}

// ============================================================
// HIGHEST SALE
// ============================================================

void highestSale()
{
    FILE *fp;

    int orderID;
    char customerName[50];
    char foodName[50];

    int quantity;

    float subtotal;
    float grandTotal;

    float highest = 0;

    int highestOrder = 0;

    clearScreen();

    printf("=====================================\n");
    printf("             HIGHEST SALE\n");
    printf("=====================================\n");

    fp = fopen(SALES_FILE, "r");

    if (fp == NULL)
    {
        printf("\nNo sales data available.\n");
        pauseScreen();

        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %d %f %f",
                  &orderID,
                  customerName,
                  foodName,
                  &quantity,
                  &subtotal,
                  &grandTotal) == 6)
    {
        if (grandTotal > highest)
        {
            highest = grandTotal;
            highestOrder = orderID;
        }
    }

    fclose(fp);

    if (highestOrder == 0)
    {
        printf("\nNo sales found.\n");
    }
    else
    {
        printf("\nHighest Sale : %.2f BDT",
               highest);

        printf("\nOrder ID     : %d\n",
               highestOrder);
    }

    pauseScreen();
}

// ============================================================
// LOWEST SALE
// ============================================================

void lowestSale()
{
    FILE *fp;

    int orderID;
    char customerName[50];
    char foodName[50];

    int quantity;

    float subtotal;
    float grandTotal;

    float lowest = 0;

    int lowestOrder = 0;

    int first = 1;

    clearScreen();

    printf("=====================================\n");
    printf("              LOWEST SALE\n");
    printf("=====================================\n");

    fp = fopen(SALES_FILE, "r");

    if (fp == NULL)
    {
        printf("\nNo sales data available.\n");
        pauseScreen();

        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %d %f %f",
                  &orderID,
                  customerName,
                  foodName,
                  &quantity,
                  &subtotal,
                  &grandTotal) == 6)
    {
        if (first)
        {
            lowest = grandTotal;
            lowestOrder = orderID;

            first = 0;
        }
        else if (grandTotal < lowest)
        {
            lowest = grandTotal;
            lowestOrder = orderID;
        }
    }

    fclose(fp);

    if (first)
    {
        printf("\nNo sales found.\n");
    }
    else
    {
        printf("\nLowest Sale : %.2f BDT",
               lowest);

        printf("\nOrder ID    : %d\n",
               lowestOrder);
    }

    pauseScreen();
}

// ============================================================
// AVERAGE SALE
// ============================================================

void averageSale()
{
    FILE *fp;

    int orderID;
    char customerName[50];
    char foodName[50];

    int quantity;

    float subtotal;
    float grandTotal;

    float total = 0;

    int count = 0;

    float average;

    clearScreen();

    printf("=====================================\n");
    printf("              AVERAGE SALE\n");
    printf("=====================================\n");

    fp = fopen(SALES_FILE, "r");

    if (fp == NULL)
    {
        printf("\nNo sales data available.\n");
        pauseScreen();

        return;
    }

    while (fscanf(fp,
                  "%d %49s %49s %d %f %f",
                  &orderID,
                  customerName,
                  foodName,
                  &quantity,
                  &subtotal,
                  &grandTotal) == 6)
    {
        total += grandTotal;
        count++;
    }

    fclose(fp);

    if (count == 0)
    {
        printf("\nNo sales found.\n");
    }
    else
    {
        average = total / count;

        printf("\nTotal Sales : %.2f BDT",
               total);

        printf("\nNumber of Orders : %d",
               count);

        printf("\nAverage Sale : %.2f BDT\n",
               average);
    }

    pauseScreen();
}
