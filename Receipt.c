#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Order *front = NULL;
Order *rear = NULL;

void printReceipt(Order *order);
void billing();
void printReceipt(Order *order)
{
    FILE *fp;

    float vat;
    float discount = 0;
    float grandTotal;

    fp = fopen("sales.dat", "a");

    if(fp == NULL)
    {
        printf("\nSales File Error!\n");
        return;
    }
    vat = order->totalPrice * 0.05;

    grandTotal =
        order->totalPrice + vat - discount;

    printf("\n");
    printf("          NUB CANTEEN\n");
    printf("             RECEIPT\n");
    printf("=====================================\n");

    printf("Order ID      : %d\n",
           order->orderID);

    printf("Customer      : %s\n",
           order->customerName);

    printf("Food          : %s\n",
           order->foodName);

    printf("Quantity      : %d\n",
           order->quantity);

    printf("Unit Price    : %.2f BDT\n",
           order->unitPrice);

    printf("-------------------------------------\n");

    printf("Subtotal      : %.2f BDT\n",
           order->totalPrice);

    printf("VAT (5%%)      : %.2f BDT\n",
           vat);

    printf("Discount      : %.2f BDT\n",
           discount);

    printf("-------------------------------------\n");

    printf("Grand Total   : %.2f BDT\n",
           grandTotal);

    printf("=====================================\n");

    printf("       ORDER SUCCESSFUL!\n");
    printf("       Thank You For Ordering!\n");

    printf("=====================================\n");



    fprintf(fp,
            "%d|%s|%s|%d|%.2f|%.2f|%.2f\n",

            order->orderID,
            order->customerName,
            order->foodName,
            order->quantity,
            order->unitPrice,
            order->totalPrice,
            grandTotal
           );


    fclose(fp);
}


void billing()
{
    Order *temp;



    if(front == NULL)
    {
        printf("\nNo Pending Order!\n");

        system("pause");

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

    system("pause");
}
