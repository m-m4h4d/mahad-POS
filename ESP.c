/*
    Name: MUHAMMAD MAHAD
    Class: BSCS-12-B-2K22
    Qalam Address: mmahad.bscs22seecs
    CMS ID: 408576
    Roll No: 11528522
*/

// Including Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// Defining Constants
#define MAX_PRODUCTS 500
#define MAX_NAME_LEN 100
#define FILE_NAME "Data.txt"

// Data Structure
typedef struct
{
    char name[MAX_NAME_LEN];
    float price;
    int stock;
    int quantity;
} Product;

// Global Variables
Product products[MAX_PRODUCTS];
int num_products = 0;

// Function declarations
int is_product_exist(char product_name[]);
void read_data_from_file();
void write_data_to_file();
void add_new_product();
void cart();
void remove_product();
void show_product_list();
void checkout();
void stock_check();

// Main Program
int main()
{
    read_data_from_file();
    while (1)
    {
        printf("1. Add a product\n");
        printf("2. Customer cart\n");
        printf("3. Remove a product\n");
        printf("4. Show product list\n");
        printf("5. Checkout\n");
        printf("6. Check Stock\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        // Calling Functions
        switch (choice)
        {
        case 1:
            add_new_product();
            break;
        case 2:
            cart();
            break;
        case 3:
            remove_product();
            break;
        case 4:
            show_product_list();
            break;
        case 5:
            checkout();
            break;
        case 6:
            stock_check();
            break;
        case 7:
            for (int i = 0; i < num_products; i++)
                products[i].quantity = 0;
            write_data_to_file();
            puts("\nThank you for shopping with us!\n");
            return 0;
        default:
            puts("\nInvalid choice. Please try again.\n");
        }
    }
}

/*      Function Definitions        */

// Checks if a product already exists and returns its index
int is_product_exist(char product_name[])
{
    for (int i = 0; i < num_products; i++)
    {
        if (strcmp(products[i].name, product_name) == 0)
            return i;
    }
    return -1;
}

// Reads the contents of file and saves then in a data structure
void read_data_from_file()
{
    FILE *file;
    file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        puts("\nError: File not found.\n");
        return;
    }

    while (fscanf(file, "%s %f %d %d", products[num_products].name, &products[num_products].price, &products[num_products].stock, &products[num_products].quantity) != EOF)
        num_products++;

    puts("\nData Loaded Successfully\n");
    fclose(file);
}

// Writes the contents of data structure into the file
void write_data_to_file()
{
    FILE *file;
    file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        puts("\nError: File not found.\n");
        return;
    }

    for (int i = 0; i < num_products; i++)
        fprintf(file, "%s %.2f %d %d\n", products[i].name, products[i].price, products[i].stock, products[i].quantity);

    puts("\nData Saved Successfully\n");
    fclose(file);
}

// Adds a new product or edits an existing product
void add_new_product()
{
    if (num_products == MAX_PRODUCTS)
    {
        puts("\nError: Can't add more products. Maximum limit reached.\n");
        return;
    }

    char product_name[MAX_NAME_LEN];
    puts("\nCaution: Write '_' instead of spaces in names.\n");
    printf("\nEnter product name: ");
    scanf("%s", product_name);

    int product_index = is_product_exist(product_name);
    if (product_index != -1)
    {
        printf("Product already exists! Updating.....\n");

        printf("Enter product price: ");
        scanf("%f", &products[product_index].price);

        printf("Enter product stock: ");
        scanf("%d", &products[product_index].stock);

        puts("\nProduct updated successfully!\n");
    }

    else
    {
        product_name[0] = toupper(product_name[0]);
        strcpy(products[num_products].name, product_name);
        printf("Enter product price: ");
        scanf("%f", &products[num_products].price);

        printf("Enter product stock: ");
        scanf("%d", &products[num_products].stock);

        printf("\nProduct added successfully!\n");
        num_products++;
    }

    write_data_to_file();
}

// Takes the number of particular items a customer wants to purchase and updates stock
void cart()
{
    char product_name[MAX_NAME_LEN];
    printf("\nEnter product name: ");
    scanf("%s", product_name);

    int product_index = is_product_exist(product_name);
    if (product_index != -1)
    {
        int new_quantity = 0;
        printf("Enter new quantity: ");
        scanf("%d", &new_quantity);

        if (new_quantity <= products[product_index].stock)
        {
            products[product_index].quantity = new_quantity;
            num_products++;
        }

        else
            puts("\nNot enough stock!\n");
    }

    else if (products[product_index].stock == 0)
        puts("\nOut of Stock!\n");

    else
        printf("\nThe product does not exist!\n");

    printf("\nQuantity updated successfully!\n");
    products[product_index].stock -= products[product_index].quantity;
    write_data_to_file();
}

// Removes an item from the file
void remove_product()
{
    if (num_products == 0)
    {
        printf("\nError: No products found.\n");
        return;
    }

    char product_name[MAX_NAME_LEN];
    printf("\nEnter product name: ");
    scanf("%s", product_name);

    int product_index = is_product_exist(product_name);
    if (product_index != -1)
    {
        for (int i = product_index; i < num_products - 1; i++)
            products[i] = products[i + 1];

        num_products--;
        printf("\nProduct removed successfully!\n");
    }

    else
        printf("\nProduct not found\n");

    write_data_to_file();
}

// Shows the list of items currently in customer's cart
void show_product_list()
{
    int o = 0;
    for (int i = 0; i < num_products; i++)
    {
        if (products[i].quantity > 0)
            o++;
    }

    if (num_products == 0 || o == 0)
    {
        puts("\nError: No products found.\n");
        return;
    }

    puts("\nProduct List:\n");
    for (int i = 0; i < num_products; i++)
    {
        if (products[i].quantity != 0)
            printf("%s\tRs.%.2f\tQty: %d\n", products[i].name, products[i].price, products[i].quantity);
    }
}

// Calculates total amount and discount (if any)
void checkout()
{
    if (num_products == 0)
    {
        puts("\nError: No products found.\n");
        return;
    }

    float total_price = 0, discount = 0, paid = 0, recieved = 0, discountA = 0;
    for (int i = 0; i < num_products; i++)
        total_price += products[i].price * products[i].quantity;

    printf("\nTotal amount to be paid: Rs. %.2f\n", total_price);

    if (total_price > 5000)
    {
        discount = 0.2 * total_price;
        printf("\nFlat twenty percent off discount Price: Rs. %.2f\n", discount);
    }

    printf("Additional discount: Rs. ");
    scanf("%f", &discountA);
    discount += discountA;
    total_price -= discount;
    printf("Net amount to be paid: Rs. %.2f\n", total_price);

    puts("\nRecieved amount: Rs. ");
    scanf("%f", &recieved);
    printf("Amount to be returned: Rs. %.2f", recieved - total_price);
}

// Checks the amount of all products left in stock
void stock_check()
{
    puts("\nRemaining stock:\n");
    for (int i = 0; i < num_products; i++)
        printf("%s\tRs. %.2f\tQty: %d\n\n", products[i].name, products[i].price, products[i].stock);
}