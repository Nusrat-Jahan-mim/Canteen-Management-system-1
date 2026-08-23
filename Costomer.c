
      #define MAX_CUSTOMERS 100
      #define MAX_ORDER_ITEMS 20

        printf("       [ EMPLOYEE DASHBOARD ]\n");
  
   

        printf("\n1. Add Food\n");
        printf("2. Display Food Menu\n");
        printf("3. Take Customer Order\n");
        printf("4. Print Receipt\n");
        printf("5. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("\nAdd Food Module\n");
                printf("Employee will add food here.\n");

                system("pause");

                break;


            case 2:

                system("cls");

                printf("             FOOD MENU\n");
               

                for(int i = 0; i < foodCount; i++)
                {
                    printf("\n%d. %s - %.2f BDT",
                           foodMenu[i].id,
                           foodMenu[i].name,
                           foodMenu[i].price);
                }

                printf("\n");

                system("pause");

                break;


            case 3:

                customerOrder();

                break;


            case 4:

                printf("\nPrint Receipt Module\n");
                printf("Receipt is printed after customer order.\n");

                system("pause");

                break;


            case 5:

                printf("\nEmployee Logged Out.\n");

                system("pause");

                return;


            default:

                printf("\nInvalid Choice!\n");

                system("pause");
        }
    }
}



void customerRegistration()
{
    char phone[30];

    system("cls");


    printf("        [CUSTOMER REGISTRATION]\n");
   

    if(customerCount >= MAX_CUSTOMERS)
    {
        printf("\nCustomer limit reached!\n");

        system("pause");

        return;
    }


    printf("\nCustomer Name : ");

    scanf(" %[^\n]", customers[customerCount].name);


    printf("Mobile Number : ");

    scanf("%29s", phone);


    //CHECK PHONE 

    if(!validPhone(phone))
    {
        printf("       REGISTRATION DECLINED\n");
        printf("        Please try again\n");

        printf("\nPhone number must be exactly 11 digits.\n");

        system("pause");

        return;
    }


    strcpy(
        customers[customerCount].phone,
        phone
    );

    customers[customerCount].id =
        generateCustomerID();


 
    printf("     REGISTRATION SUCCESSFUL\n");
    printf("=====================================\n");

    printf("\nCustomer Name : %s\n",
           customers[customerCount].name);

    printf("Customer ID   : %d\n",
           customers[customerCount].id);

    printf("Phone Number  : %s\n",
           customers[customerCount].phone);


    customerCount++;


    system("pause");
}


int validPhone(char phone[])        //validation    
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

    printf("          CUSTOMER LOGIN\n");
    printf("=====================================\n");


    if(customerCount == 0)
    {
        printf("\nNo customer registered yet.\n");

        system("pause");

        return -1;
    }


    printf("\nEnter Customer ID : ");

    scanf("%d", &id);


    for(i = 0; i < customerCount; i++)
    {
        if(customers[i].id == id)
        {
            printf("\nLogin Successful!\n");

            printf("Welcome, %s!\n",
                   customers[i].name);

            system("pause");

            return id;
        }
    }


    printf("\nCustomer ID not found!\n");

    system("pause");

    return -1;
}

void customerOrder()        //order through employee
{
    int customerID;
    int choice;

    Order orders[MAX_ORDER_ITEMS];

    int orderCount = 0;

    int foodID;
    int quantity;

    int i;
    int found;

    float grandTotal = 0;

    system("cls");


    printf("          CUSTOMER ORDER\n");
    printf("=====================================\n");

    printf("\n1. New Customer Registration\n");
    printf("2. Existing Customer Login\n");

    printf("\nEnter Choice : ");

    scanf("%d", &choice);



    if(choice == 1)
    {
        int oldCount = customerCount;

        customerRegistration();


    

        if(customerCount == oldCount)
        {
            return;
        }


        customerID =
            customers[customerCount - 1].id;
    }



    else if(choice == 2)
    {
        customerID = customerLogin();


        if(customerID == -1)
        {
            return;
        }
    }


    else
    {
        printf("\nInvalid Choice!\n");

        system("pause");

        return;
    }
