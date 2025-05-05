/***********************************************************************
// OOP244 Project, Menu Module
//
// File	Menu.cpp
// Version 5.3
// started by Fardad
// Description
// 
// Revision History
// -----------------------------------------------------------
// Name Thai Hoa Nguyen            Date            Reason
// Student ID: 175752237
/////////////////////////////////////////////////////////////////
***********************************************************************/
/*---------------------------------------------------------- -
- Inside Constructor with deep copy -> Using Deep Copy in Constructor (only if validations pass)
- Menu Constructor -> Initialize title (MenuItem)
                   -> Initialize exit option (MenuItem)
                   -> Initialize selection prompt (MenuItem) to "> "
                   -> set all MenuItem pointer to nullptr
Source: From last Milestone, Workshop and Researching on Internet

- I created the The display Main and Sub title to get the correct format.
---------------------------------------------------------- - */
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <cstring>
#include "constants.h"
#include "Utils.h"

#include <string>
#include <cctype>  // For isdigit()

using namespace std;

namespace seneca
{

    //Constructor with deep copy
    MenuItem::MenuItem(const char* menu_ItemContent, unsigned int indent_Number, unsigned int indent_Size, unsigned int menu_Object)
    {
        //Avoid Shallow Copy for menu_ItemContent;
        indentNumber = indent_Number;
        indentSize = indent_Size;
        menuObject = menu_Object;

        // Validate content
        bool isValidContent = menu_ItemContent && ut.strlen(menu_ItemContent) > 0 && !ut.isspace(menu_ItemContent);

        // Validate indentation
        bool isValidIndent = indent_Number <= 4 && indent_Size <= 4;

        // Validate row number (only check if it's non-negative)
        // Dont need to validate row number against MaximumNumberOfMenuItems
        bool isValidRow = true;


        //Using Deep Copy in Constructor only if validations pass
        if (isValidContent && isValidIndent && isValidRow)
        {
            menuItemContent = new char[ut.strlen(menu_ItemContent) + 1];
            ut.strcpy(menuItemContent, menu_ItemContent);
        }
        else
        {
            // Set to safe empty state if validations fail
            menuItemContent = nullptr;
            indentNumber = 0;
            indentSize = 0;
            menuObject = 0;
        }

    }

    //Menu Constructor
    Menu::Menu(const char* c_title, const char* exit_Option, unsigned int indent_Number , unsigned int indent_Size)
    {
        indentNumber = indent_Number;
        indentSize = indent_Size;

        // No item initially
        numItem = 0; // the menu starts empty

        // Initialize title (MenuItem)
        title.menuItemContent = nullptr; // avoid dangling pointer 
        if (c_title != nullptr && strlen(c_title) > 0) // check validation of c_tile
        {
            // allocates memory dynamically
            title.menuItemContent = new char[strlen(c_title) + 1];
            strcpy(title.menuItemContent, c_title);
        }

        //Initialize exit option (MenuItem)
        exitOption.menuItemContent = nullptr; //  prevents invalid memory access.
        if (exit_Option != nullptr && strlen(exit_Option) > 0)
        {
            // allocates memory dynamically and copies
            exitOption.menuItemContent = new char[strlen(exit_Option) + 1];
            strcpy(exitOption.menuItemContent, exit_Option);
        }

        // Initialize selection prompt (MenuItem) to "> "
        //Allocates memory
        entryPrompt.menuItemContent = new char[3]; // for "> " + null terminator
        strcpy(entryPrompt.menuItemContent, "> ");

        //Initialize all menu item pointers to nullptr
        for (unsigned int i = 0; i < seneca::MaximumNumberOfMenuItems; i++)
        {
            item[i] = nullptr;
        }
    }

    //Destructor of MenuItem
    MenuItem::~MenuItem()
    {
        //Prevent memory leaks
        delete[] menuItemContent;
        menuItemContent = nullptr;
        /*If someone try item.~menuItem(); in main.It will not crash*/
    };

    //Destructor of Menu
    Menu::~Menu()
    {
        //Iterate through the item array
        for (unsigned int i = 0; i < numItem; i++)
        {
            //Free allocated memory
            delete item[i];
            //Prevent dangling pointers
            item[i] = nullptr;
        }
    };

    // Overloaded bool operator
    MenuItem::operator bool() const
    {
        return (menuItemContent != nullptr && ut.strlen(menuItemContent) > 0);
    }

    // Overloaded << operator to add MenuItems dynamically
    Menu& Menu::operator<<(const char* menuItemContent)
    {
        if (numItem < seneca::MaximumNumberOfMenuItems)
        {
            // Dynamically create a new MenuItem
            item[numItem] = new MenuItem(menuItemContent, indentNumber, indentSize, numItem + 1);

            // Increment numItems to reflect the addition
            numItem++;
        }

        return *this;
    }

    //Users selection 
    size_t Menu::select() const
    {
        // Display the Menu Title 
        //make sure the menu title will move forward depends on each table
        if (indentNumber == 0)
        {
            // Main menu: display title without indentation
            displayMainTitle();
        }
        else
        {
            // Submenu: display title with indentation
            displaySubTitle();
        }

        // Display the Menu Items for each folder
        for (unsigned int i = 0; i < numItem; i++)
        {
            if (item[i] != nullptr)
            {    
                item[i]->display(cout) << endl;
            }
        }

        //Display the exit button like 0- return for each folder
        for (unsigned int i = 0; i < indentNumber * indentSize; i++)
        {
            // Ensure consistent spacing before 0- Return
            cout << " ";
        }
        cout << " 0- " << exitOption.menuItemContent << endl;


        //It will make the arrow prompt following each folder
        for (unsigned int i = 0; i < indentNumber * indentSize; i++)
        {
            cout << " ";
        }
        // Display the Selection Prompt
        cout << entryPrompt.menuItemContent;

        // Get a valid selection from the user
        return ut.getInt(0, numItem);
    }

    // Display mainTitle
    void Menu::displayMainTitle() const
    {
        if (title.menuItemContent != nullptr)
        {
            if (strstr(title.menuItemContent, "you want to exit?") != nullptr) {
                cout << title.menuItemContent << endl;
            } else {
                cout << title.menuItemContent << " " << endl;
            }
        }
    }

    // Display subTitle 
    void Menu::displaySubTitle() const
    {
        if (title.menuItemContent != nullptr)
        {
            // Use fixed indentation based on the menu's level to ensure exact output
            if (indentNumber == 1) {
                // Level 1 - exactly 3 spaces for Order Menu 
                cout << "   " << title.menuItemContent << endl;
            }
            else if (indentNumber == 2) {
                // Level 2 - exactly 6 spaces for Drink/Food Menu
                cout << "      " << title.menuItemContent << endl;
            }
            else if (indentNumber == 3) {
                // Level 3 - exactly 9 spaces for Size Selection menus
                cout << "         " << title.menuItemContent << endl;
            }
            else {
                // Default case - fall back to calculated indentation
                for (unsigned int i = 0; i < indentNumber * indentSize; i++) {
                    cout << " ";
                }
                cout << title.menuItemContent << endl;
            }
        }
    }

    // Insertion operator overload for Menu
    size_t operator<<(std::ostream& ostr, const Menu& m)
    {
        // If the ostream is std::cout, invoke the select method
        if (&ostr == &std::cout)
        {
            return m.select();
        }

        // For any other ostream and return 0
        return 0;
    }

    // Display with argument
    std::ostream& MenuItem::display(std::ostream& output) const
    {

        if (menuItemContent == nullptr || ut.strlen(menuItemContent) == 0 || ut.isspace(menuItemContent))
        {
            output << "??????????";
        }
        else
        {

            // Print indentation (indentNumber * indentSize spaces)
            for (unsigned i = 0; i < indentNumber * indentSize; i++)
            {
                output << " ";
            }

            // Print row number if it's not the exit option
            if (menuObject > 0)
            {
                // want to make all of the menutile from > 10 will move to the right 1 space
                if (menuObject < 10)
                {
                    output << " ";
                };
                output << menuObject << "- ";
            }

           
            // Print menu content (trim leading spaces manually)
            const char* content = menuItemContent;
            while (*content && ut.isspace(*content))
            {
                content++; // Skip leading spaces
            }
            output << content;
        }
        return output;
    }

    // Display without argument (defaults to std::cout)
    std::ostream& MenuItem::display() const
    {
        // Call the display function with std::cout
        return display(cout);
    }

}