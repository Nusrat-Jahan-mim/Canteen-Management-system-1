
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

#define EMP_USER "employee"
#define EMP_PASS "1234"

void loading();
void mainMenu();
void adminLogin();
void employeeLogin();
void adminPanel();
void employeePanel();

#endif


void employeeLogin();
void employeePanel();

#include <conio.h>
void inputPassword(char password[]);
void customerPanel();

#define FOOD_FILE "food.dat"

typedef struct
{
    int id;
    char name[50];
    float price;
    int quantity;
} Food;

void addFood();
void displayFood();


