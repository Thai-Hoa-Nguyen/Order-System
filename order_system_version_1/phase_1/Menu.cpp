#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <cstring>
#include "constants.h"
#include "Utils.h"
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


        //Using Deep Copy in Constructor (only if validations pass)
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

    //Destructor
    MenuItem::~MenuItem()
    {
        //Prevent memory leaks
        delete[] menuItemContent;
        menuItemContent = nullptr;
        /*If someone try item.~menuItem(); in main.It won't crash*/
    }

    // Copy Constructor (Deep Copy) ( Already prevented ) (Keep this for the future project)
    //menuItem::menuItem(const menuItem& menuItem_copy)
    //{
    //    menuItemContent = nullptr;
    //    indentNumber = menuItem_copy.indentNumber;
    //    indentSize = menuItem_copy.indentSize;
    //    menuObject = menuItem_copy.menuObject;

    //    if (menuItem_copy.menuItemContent != nullptr)
    //    {
    //        menuItemContent = new char[strlen(menuItem_copy.menuItemContent) + 1];
    //        strcpy(menuItemContent, menuItem_copy.menuItemContent);
    //    }
    //};

    // Copy Assignment Operator ( Already prevented ) (Keep this for the future project)
    //menuItem& menuItem::operator=(const menuItem& menuItem_copyOperator)
    //{
    //    if (this != &menuItem_copyOperator)
    //    {
    //        delete[] menuItemContent;

    //        indentNumber = menuItem_copyOperator.indentNumber;
    //        indentSize = menuItem_copyOperator.indentSize;
    //        menuObject = menuItem_copyOperator.menuObject;

    //        if (menuItem_copyOperator.menuItemContent != nullptr)
    //        {
    //            menuItemContent = new char[strlen(menuItem_copyOperator.menuItemContent) + 1];
    //            strcpy(menuItemContent, menuItem_copyOperator.menuItemContent);
    //        }
    //        else
    //        {
    //            menuItemContent = nullptr;
    //        }
    //    }
    //    return *this;
    //}


    // Overloaded bool operator
    MenuItem::operator bool() const
    {
        return (menuItemContent != nullptr && ut.strlen(menuItemContent) > 0);
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
                output << ' ';
            }

            // Print row number if available
            if (menuObject >= 0)
            {
                output.width(2);
                output.fill(' ');
                output << menuObject << "- ";
            }

            // Print the content (skip leading whitespace)
            const char* content = menuItemContent;
            while (*content && ut.isspace(*content))
            {
                content++;
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