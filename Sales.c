
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALES_FILE "sales.dat"

typedef struct
{
    int billNo;
    char customer[50];
    float grandTotal;
    char dateTime[30];

} SalesRecord;



void salesStatisticsMenu();

void incomeSummary();
void dailySalesReport();
void monthlySalesReport();

void highestSale();
void lowestSale();
void averageSale();

void adminPanel()
{
    int choice;

    while(1)
    {
        system("cls");
        printf("          ADMIN DASHBOARD\n");
        printf("=====================================\n");

        printf("\n1. Customer Management\n");
        printf("2. Food Management\n");
        printf("3. Sales & Reports\n");
        printf("4. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1:

                printf("\nCustomer Management Module\n");
                system("pause");

                break;


            case 2:

                printf("\nFood Management Module\n");
                system("pause");

                break;


            case 3:

                salesStatisticsMenu();

                break;


            case 4:

                printf("\nAdmin Logged Out.\n");

                system("pause");

                return;


            default:

                printf("\nInvalid Choice!\n");

                system("pause");
        }
    }
}



void salesStatisticsMenu()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("       NUB CANTEEN SALES PANEL\n");
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


        switch(choice)
        {
            case 1:

                incomeSummary();

                system("pause");

                break;


            case 2:

                dailySalesReport();

                system("pause");

                break;


            case 3:

                monthlySalesReport();

                system("pause");

                break;


            case 4:

                highestSale();

                system("pause");

                break;


            case 5:

                lowestSale();

                system("pause");

                break;


            case 6:

                averageSale();

                system("pause");

                break;


            case 0:

                return;


            default:

                printf("\nInvalid Choice!\n");

                system("pause");
        }
    }
}


void incomeSummary()
{
    FILE *fp;

    SalesRecord sale;

    float totalIncome = 0;


    fp = fopen(SALES_FILE, "rb");


    if(fp == NULL)
    {
        printf("\nNo Sales Record Found.\n");

        return;
    }


    while(fread(&sale,
                sizeof(SalesRecord),
                1,
                fp))
    {
        totalIncome += sale.grandTotal;
    }


    fclose(fp);

    printf("        TOTAL INCOME REPORT\n");
    printf("=====================================\n");

    printf("\nOverall Income : %.2f BDT\n",
           totalIncome);
}


void dailySalesReport()
{
    FILE *fp;

    SalesRecord sale;

    char date[11];

    float total = 0;

    int count = 0;


    printf("\nEnter Date (DD-MM-YYYY): ");

    scanf("%10s", date);


    fp = fopen(SALES_FILE, "rb");


    if(fp == NULL)
    {
        printf("\nNo Sales Record Found.\n");

        return;
    }
    printf("          DAILY SALES REPORT\n");
    printf("=====================================\n");


    while(fread(&sale,
                sizeof(SalesRecord),
                1,
                fp))
    {

        if(strncmp(sale.dateTime,
                   date,
                   10) == 0)
        {
            printf("\nBill No   : %d",
                   sale.billNo);

            printf("\nCustomer  : %s",
                   sale.customer);

            printf("\nAmount    : %.2f BDT",
                   sale.grandTotal);

            printf("\nDate/Time : %s",
                   sale.dateTime);

            printf("\n-----------------------------");


            total += sale.grandTotal;

            count++;
        }
    }


    fclose(fp);


    printf("\n\n=====================================\n");

    printf("Total Bills : %d\n",
           count);

    printf("Total Sales : %.2f BDT\n",
           total);

    printf("=====================================\n");
}



void monthlySalesReport()
{
    FILE *fp;

    SalesRecord sale;

    char month[3];
    char year[5];

    float total = 0;

    int billCount = 0;


    printf("\nEnter Month (MM): ");

    scanf("%2s", month);


    printf("Enter Year (YYYY): ");

    scanf("%4s", year);


    fp = fopen(SALES_FILE, "rb");


    if(fp == NULL)
    {
        printf("\nNo Sales Record Found.\n");

        return;
    }


    printf("\n=====================================\n");
    printf("          MONTHLY SALES REPORT\n");
    printf("=====================================\n");


    while(fread(&sale,
                sizeof(SalesRecord),
                1,
                fp))
    {
        char fileMonth[3];

        char fileYear[5];



        strncpy(fileMonth,
                sale.dateTime + 3,
                2);

        fileMonth[2] = '\0';


        strncpy(fileYear,
                sale.dateTime + 6,
                4);

        fileYear[4] = '\0';


        if(strcmp(fileMonth, month) == 0 &&
           strcmp(fileYear, year) == 0)
        {
            printf("\nBill No  : %d",
                   sale.billNo);

            printf("\nCustomer : %s",
                   sale.customer);

            printf("\nAmount   : %.2f BDT",
                   sale.grandTotal);

            printf("\nDate     : %s",
                   sale.dateTime);

            printf("\n-----------------------------");


            total += sale.grandTotal;

            billCount++;
        }
    }


    fclose(fp);


    printf("\n\n=====================================\n");

    printf("Total Bills    : %d\n",
           billCount);

    printf("Monthly Income : %.2f BDT\n",
           total);

    printf("=====================================\n");
}

void highestSale()
{
    FILE *fp;

    SalesRecord sale;
    SalesRecord highest;


    fp = fopen(SALES_FILE, "rb");


    if(fp == NULL)
    {
        printf("\nNo Sales Record Found.\n");

        return;
    }


    if(fread(&highest,
             sizeof(SalesRecord),
             1,
             fp) != 1)
    {
        printf("\nSales File is Empty.\n");

        fclose(fp);

        return;
    }


    while(fread(&sale,
                sizeof(SalesRecord),
                1,
                fp))
    {
        if(sale.grandTotal >
           highest.grandTotal)
        {
            highest = sale;
        }
    }


    fclose(fp);


    printf("\n=====================================\n");
    printf("           HIGHEST SALE\n");
    printf("=====================================\n");

    printf("\nBill No  : %d\n",
           highest.billNo);

    printf("Customer : %s\n",
           highest.customer);

    printf("Amount   : %.2f BDT\n",
           highest.grandTotal);

    printf("Date     : %s\n",
           highest.dateTime);
}



void lowestSale()
{
    FILE *fp;

    SalesRecord sale;
    SalesRecord lowest;


    fp = fopen(SALES_FILE, "rb");


    if(fp == NULL)
    {
        printf("\nNo Sales Record Found.\n");

        return;
    }


    if(fread(&lowest,
             sizeof(SalesRecord),
             1,
             fp) != 1)
    {
        printf("\nSales File is Empty.\n");

        fclose(fp);

        return;
    }


    while(fread(&sale,
                sizeof(SalesRecord),
                1,
                fp))
    {
        if(sale.grandTotal <
           lowest.grandTotal)
        {
            lowest = sale;
        }
    }


    fclose(fp);


   
    printf("            LOWEST SALE\n");
    printf("=====================================\n");

    printf("\nBill No  : %d\n",
           lowest.billNo);

    printf("Customer : %s\n",
           lowest.customer);

    printf("Amount   : %.2f BDT\n",
           lowest.grandTotal);

    printf("Date     : %s\n",
           lowest.dateTime);
}



void averageSale()
{
    FILE *fp;

    SalesRecord sale;

    float total = 0;

    int count = 0;


    fp = fopen(SALES_FILE, "rb");


    if(fp == NULL)
    {
        printf("\nNo Sales Record Found.\n");

        return;
    }


    while(fread(&sale,
                sizeof(SalesRecord),
                1,
                fp))
    {
        total += sale.grandTotal;

        count++;
    }


    fclose(fp);


    if(count == 0)
    {
        printf("\nNo Sales Available.\n");

        return;
    }


    printf("            AVERAGE SALE\n");
    printf("=====================================\n");

    printf("\nTotal Bills  : %d\n",
           count);

    printf("Average Sale : %.2f BDT\n",
           total / count);
}
