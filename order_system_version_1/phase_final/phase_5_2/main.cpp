/***********************************************************************
// OOP244 Project, Main Application
// Milestone 5
// File main.cpp
// Version 5.2
// Description
// Main application
// Revision History
// -----------------------------------------------------------
// Name Thai Hoa Nguyen            Date            Reason
// Student ID: 175752237
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;

// Function prototype for the order menu
void orderMenu(Ordering& ordering);

// Order menu implementation
void orderMenu(Ordering& ordering) 
{
    // Created order menu
    Menu orderMenu("Order Menu", "Back to main menu", 1);
    orderMenu << "Food" << "Drink";
    
    bool back = false;
    while (!back) {
        int selection = orderMenu.select();
        
        switch (selection) 
        {
            // Food
            case 1:
                ordering.orderFood();
                break;
                
            // Drink
            case 2:
                ordering.orderDrink();
                break;
                
            // Back to main menu
            case 0:
                back = true;
                break;
        }
    }
} 

int main() 
{
    // Initialize Ordering system with excel files
    Ordering ordering("drinks.csv", "foods.csv");
    
    // Checking if the order system was initialized properly
    if (!ordering) 
    {
        cout << "Error: Failed to initialize the ordering system." << endl;
        return 1;
    }
    
    // Main menu
    Menu mainMenu("Seneca Restaurant", "End Program");
    
    // Added options to main menu
    mainMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";
    
    bool done = false;
    
    // While loop for Main application
    while (!done) 
    {
        // Display menu and get user selection
        int selection = mainMenu.select();
        switch (selection) 
        {
            // Order
            case 1:
                orderMenu(ordering);
                break; 
                
            case 2: // Print Bill
                // will be implemented in later milestones
                break;
                
            case 3: // Start a New Bill
                // will be implemented in later milestones
                break;
                
            case 4: // List Foods
                ordering.listFoods();
                break;
                
            case 5: // List Drinks
                ordering.listDrinks();
                break;
                
            case 0: // Exit
                // Check if there are unsaved bills
                if (ordering.hasUnsavedBill()) 
                {
                    // Confirmation for menu
                    Menu exitConfirmMenu("You have bills that are not saved, are you sue you want to exit?", "No", 0, 0);
                    exitConfirmMenu << "Yes";
                    
                    // Get user confirmation
                    int confirmExit = exitConfirmMenu.select();
                    
                    if (confirmExit == 1)
                    {
                        // User confirmed exit
                        done = true;
                    }
                    // If confirmExit is 0, continue the main loop (don't exit)
                } 
                else 
                {
                    // No unsaved bills, safe to exit
                    done = true;
                }
                break;
        }
    }
    
    return 0;
}