/***********************************************************************
// OOP244 Project, Ordering Module
//
// File	Ordering.cpp
// Version 0.1
// Description
// implementation file for the Ordering module
// Revision History
// -----------------------------------------------------------
// Name Thai Hoa Nguyen            Date            Reason
// Student ID: 175752237
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Ordering.h"
#include "Billable.h"
#include "Food.h"
#include "Drink.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca
{
    // Private Methods

    // Helper function to format items with dots
    void printItemWithDots(const char* name, double price)
    {
        cout << name;
        int nameLength = 0;
        while (name[nameLength])
            nameLength++;

        int dotsNeeded = 33 - nameLength; // 33 is the total width for name + dots
        for (int i = 0; i < dotsNeeded; i++)
        {
            cout << '.';
        }

        cout << setw(7) << fixed << setprecision(2) << price << endl;
    }

    // Print the bill title
    void Ordering::billTitlePrint(std::ostream& os) const
    {
        os << "Bill # " << setw(3) << setfill('0') << m_billNumber << " =============================" << endl;
    }

    // Print the bill totals
    void Ordering::printTotals(std::ostream& os, double total) const
    {
        double tax = total * Tax;
        double grandTotal = total + tax;

        os << "                     Total:        " << fixed << setprecision(2) << total << endl;
        os << "                     Tax:           " << tax << endl;
        os << "                     Total+Tax:    " << grandTotal << endl;
        os << "========================================" << endl;
    }

    // Count the number of records in a file
    size_t Ordering::countRecords(const char* file) const
    {
        size_t newlineCounter = 0;
        ifstream inFile(file);
        char ch;

        while (inFile)
        {
            inFile.get(ch);
            if (inFile && ch == '\n')
            {
                newlineCounter++;
            }
        }

        return newlineCounter;
    }

    // Constructor with file names
    Ordering::Ordering(const char* drinkDataFile, const char* foodDataFile)
    {
        // Count records in both files
        size_t drinkRecords = countRecords(drinkDataFile);
        size_t foodRecords = countRecords(foodDataFile);

        // Open both files
        ifstream drinkFile(drinkDataFile);
        ifstream foodFile(foodDataFile);

        // Allocate dynamic arrays for both food and drinks if both files open successfully
        if (drinkFile && foodFile)
        {
            m_drinkArray = new Drink[drinkRecords];
            m_foodArray = new Food[foodRecords];

            // Read drink records
            unsigned int drinkCount = 0;
            while (drinkCount < drinkRecords && m_drinkArray[drinkCount].read(drinkFile))
            {
                drinkCount++;
            }

            // Read food records
            unsigned int foodCount = 0;
            while (foodCount < foodRecords && m_foodArray[foodCount].read(foodFile))
            {
                foodCount++;
            }

            // Check if all records were read successfully
            if (drinkCount != drinkRecords || foodCount != foodRecords)
            {
                // Clean up if there was an error
                delete[] m_drinkArray;
                delete[] m_foodArray;
                m_drinkArray = nullptr;
                m_foodArray = nullptr;
            }
            else
            {
                // Store counters if successful
                m_drinkCounter = drinkCount;
                m_foodCounter = foodCount;
            }
        }
    }

    // Destructor
    Ordering::~Ordering()
    {
        // Delete dynamic arrays
        delete[] m_drinkArray;
        delete[] m_foodArray;

        // Delete billable items
        for (unsigned int i = 0; i < m_billableCounter; i++)
        {
            delete m_billItems[i];
        }
    }
    
    /********************************************************/
                        /******Query*****/
    /********************************************************/
    
    // Boolean conversion operator
    Ordering::operator bool() const
    {
        return (m_drinkArray != nullptr && m_foodArray != nullptr);
    }

    // Number of bill items
    unsigned int Ordering::noOfBillItems() const
    {
        return m_billableCounter;
    }

    // Check if there is an unsaved bill
    bool Ordering::hasUnsavedBill() const
    {
        return m_billableCounter > 0;
    }

    /********************************************************/
    /********************************************************/


    // Methods for the main application's menu

    // List food items
    void Ordering::listFoods() const
    {
        cout << "List Of Avaiable Meals" << endl;
        cout << "========================================" << endl;

        for (unsigned int i = 0; i < m_foodCounter; i++)
        {
            printItemWithDots((const char*)m_foodArray[i], m_foodArray[i].price());
        }

        cout << "========================================" << endl;
    }

    // List drink items
    void Ordering::listDrinks() const
    {
        cout << "List Of Avaiable Drinks" << endl;
        cout << "========================================" << endl;

        for (unsigned int i = 0; i < m_drinkCounter; i++)
        {
            printItemWithDots((const char*)m_drinkArray[i], m_drinkArray[i].price());
        }

        cout << "========================================" << endl;
    }

    // Order food
    void Ordering::orderFood()
    {
        // Create menu with food items
        Menu foodMenu("Food Menu", "Back to Order", 2);

        // Add food items to menu
        for (unsigned int i = 0; i < m_foodCounter; i++)
        {
            foodMenu << (const char*)m_foodArray[i];
        }

        // Display menu and get selection
        size_t selection = foodMenu.select();

        if (selection != 0)
        {
            // Create a dynamic copy of the selected food item
            Food* food = new Food(m_foodArray[selection - 1]);

            // Assign to bill items array
            m_billItems[m_billableCounter] = food;

            // Customize the order
            if (food->order())
            {
                // Order was successful, increment counter
                m_billableCounter++;
            }
            else
            {
                // Order was cancelled, delete the allocated food item
                delete food;
            }
        }
    }

    // Order drink
    void Ordering::orderDrink()
    {
        // Create menu with drink items
        Menu drinkMenu("Drink Menu", "Back to Order", 2);

        // Add drink items to menu
        for (unsigned int i = 0; i < m_drinkCounter; i++)
        {
            drinkMenu << (const char*)m_drinkArray[i];
        }

        // Display menu and get selection
        size_t selection = drinkMenu.select();

        if (selection != 0)
        {
            // Create a dynamic copy of the selected drink item
            Drink* drink = new Drink(m_drinkArray[selection - 1]);

            // Assign to bill items array
            m_billItems[m_billableCounter] = drink;

            // Customize the order
            if (drink->order())
            {
                // Order was successful, increment counter
                m_billableCounter++;
            }
            else
            {
                // Order was cancelled, delete the allocated drink item
                delete drink;
            }
        }
    }

    // Print bill
    void Ordering::printBill(std::ostream& os) const
    {
        double total = 0.0;

        // Print bill title
        billTitlePrint(os);

        // Print each item in the bill
        for (unsigned int i = 0; i < m_billableCounter; i++)
        {
            m_billItems[i]->print(os);
            os << endl; // Add a line break after each item
            total += m_billItems[i]->price();
        }

        // Print totals
        printTotals(os, total);
    }

    // Reset bill
    void Ordering::resetBill()
    {
        char filename[100] = { 0 };

        // Create bill file name
        ut.makeBillFileName(filename, m_billNumber);

        // Open file for writing
        ofstream file(filename);

        // Print bill to file
        printBill(file);

        // Display message
        cout << "Saved bill number " << m_billNumber << endl;
        cout << "Starting bill number " << m_billNumber + 1 << endl;

        // Delete billable items
        for (unsigned int i = 0; i < m_billableCounter; i++)
        {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }

        // Increment bill number and reset bill item counter
        m_billNumber++;
        m_billableCounter = 0;
    }
}
