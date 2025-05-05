/***********************************************************************
// OOP244 Project, Main Application
// Milestone 5
// File main.cpp
// Version 5.1
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
    
    // Added options to  main menu
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
                // will be implemented in 5.2
                break; 
                
            case 2: // Print Bill
                // will be implemented in 5.2
                break;
                
            case 3: // Start a New Bill
                // will be implemented in 5.2
                break;
                
            case 4: // List Foods
                ordering.listFoods();
                break;
                
            case 5: // List Drinks
                ordering.listDrinks();
                break;
                
            case 0: // Exit
                done = true;
                break;
        }
    }
    
    return 0;
} 