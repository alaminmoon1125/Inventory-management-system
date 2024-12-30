//Inventory management system

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxUsers 500
#define MaxItems 500
#define MaxOrders 500

typedef struct
{
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

typedef struct
{
    char username[50];
    char password[50];
} User;

typedef struct
{
    int itemId;
    int quantity;
    float totalCost;

} Order;
// Global Variables
Item inventory[MaxItems];
User users[MaxUsers];
Order orders[MaxOrders];

char adminUsername[50];
char adminPassword[50];

int itemCount = 0;
int userCount = 0;
int orderCount = 0;

// Function Prototypes
void registerUser();//masrafi
int userLogin();
int adminLogin();
void adminMenu();
void userMenu();
void loadUsers();
void saveUsers();
void addItem();
void viewItems();//masrafi
// payel
void loadItems();
void saveItems();
void searchItem();
void updateItem();
void deleteItem();
//Moon
void orderItem();
void displayorder();
void checkout();
void lowStockAlert();
void removeUser();
void salesReport();
void addUser();
void cancelOrder();

void clearScreen();
// Main Function
int main()
{
    int choice;



    // Load existing users from file
    loadUsers();

    while (1)
    {
        clearScreen();
        // Printing the menu
        printf("=========================== Inventory Management System ===========================\n");
        printf("=================================================================================\n");
        printf("%-25s 1. Register User\n", "");  // %s is replaced with "" (empty string) for formatting
        printf("%-25s 2. User Login\n", "");
        printf("%-25s 3. Admin Login\n", "");
        printf("%-25s 4. Exit\n", "");
        printf("\n----------------------------------------------------------------------------------\n");

        // Taking user input
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if (userLogin()) userMenu();
            break;
        case 3:
            if (adminLogin()) adminMenu();
            break;
        case 4:
            printf("Exiting program....\n\nPress Enter to Exit Properly");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }

    }

}


// Clear Screen Function
void clearScreen()
{

    system("cls");


}


// Load Users from File
void loadUsers()
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        return; // No users found, continue with an empty list
    }
    while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) != EOF)
    {
        userCount++;
    }
    fclose(file);
}

// Save Users to File
void saveUsers()
{
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("Error saving users.\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }
    fclose(file);
}

// Register a New User
void registerUser()
{
    char username[50], password[50];

    clearScreen();
    printf("\n--- Register User ---\n");
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    // Check if username already exists
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            clearScreen();
            printf("This username is already taken. Please choose another.\n\n");
            printf("press Enter to Back.......");

            getchar();
            getchar(); // Wait for Enter
            return;
        }
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    // Add new user to the array
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
    saveUsers();
    clearScreen();
    printf("User registered successfully!\n\n");
    printf("press Enter to Back.......");

    getchar();
    getchar(); // Wait for Enter
}

// User Login
int userLogin()
{
    char username[50], password[50];
    char buffer[100];

    clearScreen();
    printf("\n User Login \n");
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            clearScreen();
            printf("Login successful!\n ...Press Enter to continue...");
            getchar();
            return 1;
        }
    }
    clearScreen();
    printf("Invalid login. Try again.\n\n");
    printf("press Enter to Back.......");

    getchar();
    return 0;
}

// Admin Login
int adminLogin()
{
    char username[50], password[50];
    char buffer[100];

    clearScreen();
    printf("\n--- Admin Login ---\n");
    printf("Enter admin username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    // Open the admin.txt file to read credentials
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL)
    {
        printf("Error opening admin credentials file.\n");
        getchar();
        return 0;
    }

    char fileUsername[50], filePassword[50];
    fscanf(file, "%s %s", fileUsername, filePassword);
    fclose(file);

    // Compare input with file data
    if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
    {
        clearScreen();
        printf("\tAdmin login successful!\n\n Press Enter to continue...");
        getchar();
        return 1;
    }

    printf("Invalid admin credentials. Try again.\n");
    getchar();
    return 0;
}
// Load Admin Credentials from File


// Admin Menu
void adminMenu()
{
    int choice;
    while (1)
    {
        clearScreen();
        printf("\n---------------------------Admin Menu ----------------------------\n");
        printf("\n------------------------------------------------------------------\n");

        printf("%-25s 1. View Items\n", "");
        printf("%-25s 2. Add Item\n", "");
        printf("%-25s 3. Update Item\n", "");
        printf("%-25s 4. Delete Item\n", "");
        printf("%-25s 5. Search Item\n", "");
        printf("%-25s 6. Low Stock Alert\n", "");
        printf("%-25s 7. Remove User\n", "");
        printf("%-25s 8. Sales Report\n", "");
        printf("%-25s 9. Add user\n", "");
        printf("%-25s 10. Logout\n", "");

        printf("\n------------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewItems();
            break;
        case 2:
            addItem();
            break;
        case 3:
            updateItem();
            break;
        case 4:
            deleteItem();
            break;
        case 5:
            searchItem();
            break;
        case 6:
            lowStockAlert();
            break;
        case 7:
            removeUser();
            break;
        case 8:
            salesReport();
            break;
        case 9:
            addUser();
            break;

        case 10:
            return;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

void userMenu()
{
    int choice;
    while (1)
    {
        clearScreen();
        printf("\n-------------------------------- User Menu------------------------------------\n");
        printf("\n-------------------------------------------------------------------------------\n");

        printf("%-25s 1. View Items\n", "");
        printf("%-25s 2. Order Items\n", "");
        printf("%-25s 3. Display Order\n", "");
        printf("%-25s 4. Cancel Order\n", "");  // Added option to cancel orders
        printf("%-25s 5. Return to Main Menu\n", "");

        printf("\n------------------------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewItems();
            break;
        case 2:
            orderItem();
            break;
        case 3:
            displayorder();
            break;
        case 4:
            cancelOrder(); // Call cancelOrder function
            break;
        case 5:
            return;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}
void viewItems()
{
    clearScreen();
    loadItems();
    if (itemCount == 0)
    {
        printf("No items in inventory.\n");
        getchar();
        getchar();
        return;
    }

    printf("\n--- Inventory Items ---\n");
    printf("ID\tName\t\t\tQuantity\tPrice\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < itemCount; i++)
    {
        printf("%-10d %-20s %-10d %-10.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);

    }
    printf("\nPlease Enter to continue.......");
    getchar();
    getchar();
}


// Add Item Function (Unchanged)
void addItem()
{
    clearScreen();

    // Display current inventory before adding an item
    viewItems();

    // Open file in append mode
    FILE *file = fopen("items.txt", "a");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Check if the inventory is full
    if (itemCount >= MaxItems)
    {
        printf("Inventory is full. Cannot add more items.\n");
        getchar();

        return;
    }

    // Prompt user for item details
    printf("\n--- Add Item ---\n");

    printf("Enter item ID: ");
    scanf("%d", &inventory[itemCount].id);
    getchar();  // Consume the newline character left by scanf

    printf("Enter item name: ");
    gets(inventory[itemCount].name);// Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &inventory[itemCount].quantity);

    printf("Enter price: ");
    scanf("%f", &inventory[itemCount].price);

    // Save the new item to the file
    fprintf(file, "%d %s %d %.2f\n", inventory[itemCount].id, inventory[itemCount].name, inventory[itemCount].quantity, inventory[itemCount].price);
    fclose(file);

    // Increase the item count
    itemCount++;

    clearScreen();
    printf("Item added successfully!\n\n");
    printf("Press Enter to Back.......");

    getchar();
    getchar(); // Wait for user input before returning to the menu
}

void loadItems()
{
    FILE *file = fopen("items.txt", "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    itemCount = 0;
    while (fscanf(file, "%d %s %d %f", &inventory[itemCount].id, inventory[itemCount].name, &inventory[itemCount].quantity, &inventory[itemCount].price) == 4)
    {
        itemCount++;
        if (itemCount >= MaxItems) break;  // Avoid overflow
    }

    fclose(file);
}
void saveItems()
{
    FILE *file = fopen("items.txt", "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Write all items back to the file
    for (int i = 0; i < itemCount; i++)
    {
        fprintf(file, "%d %s %d %.2f\n",
                inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
}
void updateItem()
{

    clearScreen();
    loadItems();
    viewItems();


    int id, found = 0;

    printf("\n--- Update Item ---\n");
    printf("Enter item ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == id)
        {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", inventory[i].name);
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);
            saveItems();
            clearScreen();
            printf("Item updated successfully!\n");
            break;
        }

    }

    if (!found)
    {
        printf("Item with ID %d not found.\n", id);
    }
    printf("\nPlease Enter to Back.......");
    getchar();
    getchar();
}
void deleteItem()
{
    clearScreen();
    viewItems();
    // Load items from file
    loadItems();

    int idToDelete;
    int found = 0;
    printf("\n--- Delete Item ---\n");
    printf("Enter the ID of the item you want to delete: ");
    scanf("%d", &idToDelete);

    // Search for the item by ID
    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == idToDelete)
        {
            // Item found, remove it
            for (int j = i; j < itemCount - 1; j++)
            {
                inventory[j] = inventory[j + 1]; // Shift all items left by one
            }
            itemCount--; // Decrease the item count
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Item with ID %d not found.\n", idToDelete);
        getchar();
        return;
    }

    // Open the file in write mode to overwrite it
    FILE *file = fopen("items.txt", "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Save the updated inventory to the file
    for (int i = 0; i < itemCount; i++)
    {
        fprintf(file, "%d %s %d %.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    clearScreen();
    printf("Item deleted successfully!\n\n");
    printf("Press Enter to go back....");
    getchar();
    getchar(); // Wait for user input before returning to the menu
}


void searchItem()
{
    clearScreen();
    char searchName[50];
    int found = 0;

    printf("\n--- Search Item ---\n");
    printf("Enter item name: ");
    scanf("%s", searchName);

    for (int i = 0; i < itemCount; i++)
    {
        if (strstr(inventory[i].name, searchName))
        {
            printf("| %-10s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Quantity", "Price");
            printf("|------------|----------------------|------------|------------|\n");
            printf("| %-10d | %-20s | %-10d | %-9.2f |\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No items found matching '%s'.\n", searchName);
    }
    printf("\nPlease Enter to Back.......");
    getchar();
    getchar();
}


// MOON



void removeUser()
{
    clearScreen();
    char username[50];
    int found = 0;

    printf("\n--- Remove User ---\n");
    printf("Enter username to remove: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove trailing newline character

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            found = 1;
            for (int j = i; j < userCount - 1; j++)
            {
                users[j] = users[j + 1];
            }
            userCount--;
            saveUsers();
            printf("User removed successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("User '%s' not found.\n", username);
    }
    printf("\nPress Enter to Back.......");
    getchar();
}

void lowStockAlert()
{
    clearScreen();
    printf("\n--- Low Stock Alert ---\n");

    int alertFound = 0;
    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].quantity < 5)
        {
            printf("ID: %d, Name: %s, Quantity: %d\n", inventory[i].id, inventory[i].name, inventory[i].quantity);
            alertFound = 1;
        }
    }

    if (!alertFound)
    {
        printf("No low stock items.\n");
    }
    printf("\nPress Enter to Back.......");

    getchar();
    getchar();
}
// Sales report function with no orders check
void salesReport()
{
    clearScreen();

    // Open the sales report file for appending (to keep previous data)
    FILE *salesFile = fopen("sales_report.txt", "a");
    if (salesFile == NULL)
    {
        printf("Error: Unable to open sales report file.\n");
        return;
    }

    // Check if there are any orders
    if (orderCount == 0)
    {
        printf("\nNo Sales\n");
        fclose(salesFile);
        printf("\nPress Enter to Return to Menu...\n");
        getchar();
        getchar();  // Wait for user input
        return;
    }

    float totalSales = 0;  // Variable to track the total sales amount
    // Print and write sales details
    printf("\n\n--- Sales Report ---\n\n");
    printf("Sales Summary:\n");
    printf("-----------------------------------------------\n");


    // Loop through all orders to calculate and print sales details
    for (int i = 0; i < orderCount; i++)
    {
        for (int j = 0; j < itemCount; j++)
        {
            if (orders[i].itemId == inventory[j].id)
            {
                // Calculate the total cost for the current order
                float total = inventory[j].price * orders[i].quantity;

                // Print to the console
                printf("+-------------------+-------------------+-------------------+-------------------+\n");
                printf("| %-17s | %-17s | %-17s | %-17s |\n", "ID", "Name", "Quantity", "Total");
                printf("+-------------------+-------------------+-------------------+-------------------+\n");
                printf("| %-17d | %-17s | %-17d | %-17.2f |\n",
                       inventory[j].id, inventory[j].name, orders[i].quantity, total);

                // Write to the file
                fprintf(salesFile, "%d\t%s\t%d\t%.2f\n\n",
                        inventory[j].id, inventory[j].name, orders[i].quantity, total);

                // Accumulate total sales
                totalSales += total;
            }
        }
    }

    // Print and write the total sales to the file
    printf("-----------------------------------------------\n");
    printf("Total Sales: %.2f\n", totalSales);

    fprintf(salesFile, "------------------------------------------------\n");
    fprintf(salesFile, "Total Sales: %.2f\n", totalSales);

    // Close the sales report file
    fclose(salesFile);

    printf("\nPress Enter to Return to Menu...\n");
    getchar();
    getchar();  // Wait for user input to return to the menu
}
void addUser()
{
    clearScreen();
    if (userCount >= MaxUsers)
    {
        printf("User limit reached!\n");
        return;
    }

    printf("Enter username: ");
    scanf("%49s", users[userCount].username);

    printf("Enter password: ");
    scanf("%49s", users[userCount].password);

    userCount++;  //
    printf("User added successfully!\n\n");

    printf("press to Back.......!\n");

    getchar();
    getchar();


}
void orderItem()
{
    clearScreen();
    viewItems();

    int id, quantity, found = 0;
    char mobileNum[12]; // Allow for the null terminator
    char customerName[50];
    const char *paymentMethod;

    printf("\n--- Order Item ---\n");
    printf("Enter item ID: ");
    scanf("%d", &id);
    getchar();  // Consume the newline character left by scanf

    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == id)
        {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            getchar();

            if (quantity > inventory[i].quantity)
            {
                printf("Not enough stock available.\n");
                break;
            }

            printf("Enter your name: ");
            fgets(customerName, sizeof(customerName), stdin);
            customerName[strcspn(customerName, "\n")] = '\0';

            printf("Enter your mobile number: ");
            scanf("%s", mobileNum);
            getchar();

            // Store order details
            float totalCost = quantity * inventory[i].price;
            orders[orderCount].itemId = id;
            orders[orderCount].quantity = quantity;
            orders[orderCount].totalCost = totalCost;
            orderCount++;

            // Update inventory
            inventory[i].quantity -= quantity;

            // Payment Method Prompt
            clearScreen();
            printf("\n--- Order placed successfully! ---\n\n");
            printf("Please, choose a payment method to complete the order.\n");
            printf("1. Bkash\n");
            printf("2. Nagad\n");
            printf("3. Rocket\n");
            printf("4. Bank Card\n");
            printf("Enter your choice (1-4): ");
            int paymentChoice;
            scanf("%d", &paymentChoice);
            getchar();

            switch (paymentChoice)
            {
            case 1:
                paymentMethod = "Bkash";
                break;
            case 2:
                paymentMethod = "Nagad";
                break;
            case 3:
                paymentMethod = "Rocket";
                break;
            case 4:
                paymentMethod = "Bank Card";
                break;
            default:
                printf("Invalid payment method. \n");
                return;
            }

            clearScreen();
            printf("\nPayment Method: %s\n", paymentMethod);
            printf("\t|| Payment Successful ||\n\n");
            printf(")>> Thank you for your purchase! <<(\n\n");

            // Save order to file
            FILE *orderFile = fopen("orders.txt", "a");
            if (orderFile == NULL)
            {
                printf("Error: Unable to open orders file.\n");
                return;
            }
            fprintf(orderFile, "Name: %s | Mobile: %s | Item ID: %d | Name: %s | Quantity: %d | Total Cost: %.2f | Payment: %s\n",
                    customerName, mobileNum, id, inventory[i].name, quantity, totalCost, paymentMethod);
            fclose(orderFile);
            // Save updated inventory
            saveItems();
            break;
        }
    }

    if (!found)
    {
        printf("Item with ID %d not found.\n", id);
    }
    printf("\nPress Enter to go back to the menu...");
    getchar();  // Wait for user input to return
}



// Cancel an Order
void cancelOrder()
{
    clearScreen();
    displayorder();
    int orderId, found = 0;

    printf("\n--- Cancel Order ---\n");
    printf("Enter your order ID to cancel: ");
    scanf("%d", &orderId);

    // Loop through the orders to find the one to cancel
    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].itemId == orderId)
        {
            found = 1;

            // Find the item in inventory to restore the quantity
            for (int j = 0; j < itemCount; j++)
            {
                if (inventory[j].id == orders[i].itemId)
                {
                    inventory[j].quantity += orders[i].quantity; // Restore inventory quantity
                    break;
                }
            }

            // Remove the order by shifting remaining orders
            for (int k = i; k < orderCount - 1; k++)
            {
                orders[k] = orders[k + 1];
            }

            orderCount--; // Decrease order count after removal
            clearScreen();

            printf("Order cancelled successfully!\n");


            // Update inventory file as well
            saveItems();

            break;
        }
    }

    if (!found)
    {
        printf("Order with ID %d not found.\n", orderId);
    }

    printf("\nPress Enter to Back.......\n");
    getchar();
    getchar(); // Wait for user input to return
}



void displayorder()
{

    clearScreen();

    if (orderCount == 0)
    {
        printf("\nNo Orders to checkout.\n");
        printf("\nPress Enter to Return to Menu...\n");
        getchar();
        getchar();  // Wait for user input
        return;
    }


    float total = 0;

    printf("\n--- Display Your Order ---\n");

    // Print each order's details and calculate total cost
    printf("| %-10s | %-10s | %-10s |\n", "Item ID", "Quantity", "Total Cost");
    printf("|------------|------------|------------|\n");

    for (int i = 0; i < orderCount; i++)
    {
        printf("| %-10d | %-10d | %-9.2f |\n", orders[i].itemId, orders[i].quantity, orders[i].totalCost);
        total += orders[i].totalCost;
    }

    printf("|------------|------------|------------|\n");
    printf("Total Cost: %.2f\n", total);


    printf("\nTotal Cost: %.2f taka only\n", total);
    printf("\n\t|| Payment Successful ||\n\n");
    printf(")>> Thank you for your purchase! <<(\n\n");

    printf("\nPress Enter to Continue.......");

    getchar();
    getchar();

}








