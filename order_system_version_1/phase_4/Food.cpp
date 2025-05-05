/***********************************************************************
// OOP244 Project, Food Module
//
// File	Food.cpp
// Version 0.1
// started by Fardad
// Description
//
// Revision History
// -----------------------------------------------------------
// Name Thai Hoa Nguyen            Date            Reason
// Student ID: 175752237
/////////////////////////////////////////////////////////////////
***********************************************************************/
/* Citation and Sources...
Final Project Milestone 3
Module: Food
Filename: Food.cpp
Version 1.0
Author: Thai Hoa Nguyen
Revision History
-----------------------------------------------------------
Date      Reason
2024/?/?  Preliminary release
2024/?/?  Debugged DMA
-----------------------------------------------------------
Function:
All override method (same with Drink.cpp)
Source:
- https://www.geeksforgeeks.org/function-overriding-in-cpp/
- https://www.upgrad.com/blog/function-overriding-in-c-plus-plus/
- https://www.geeksforgeeks.org/override-keyword-c
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <string>
#include "Food.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca
{

    // Declare the Utils object
    extern Utils ut;

    // Copy constructor
    Food::Food(const Food& src) : m_ordered(false), m_child(false), m_customize(nullptr)
    {
        *this = src;
    }

    // Destructor
    Food::~Food()
    {
        delete[] m_customize;
        m_customize = nullptr;
    }

    // Copy assignment operator
    Food& Food::operator=(const Food& src)
    {
        if (this != &src)
        {
            // Call base class assignment operator
            Billable::operator=(src);

            // Copy Food-specific members
            m_ordered = src.m_ordered;
            m_child = src.m_child;

            // Handle dynamic memory
            ut.alocpy(m_customize, src.m_customize);
        }
        return *this;
    }

    /***************************************************************/
    /***************************************************************/
    /*OVERIVE METHOD*/

    // Override print method
    ostream& Food::print(ostream& ostr) const
    {
        if (this)
        {
            // Print name (left-justified, padded with dots)
            ostr.width(28);
            ostr.fill('.');
            ostr.setf(ios::left);
            ostr << static_cast<const char*>(*this);
            ostr.unsetf(ios::left);

            // Print portion type (Child/Adult)
            if (ordered())
            {
                if (m_child)
                {
                    ostr << "Child";
                }
                else
                {
                    ostr << "Adult";
                }
            }
            else
            {
                ostr << ".....";
            }

            // Print price (right-justified with 2 decimal places)
            ostr.width(7);
            ostr.fill(' ');
            ostr.setf(ios::right);
            ostr.setf(ios::fixed);
            ostr.precision(2);
            ostr << price();
            ostr.unsetf(ios::right);

            // Print customization (only if printing to cout)
            if (&ostr == &cout && m_customize && m_customize[0] != '\0')
            {
                ostr << " >> ";
                // Print first 30 characters of customization
                char temp[31] = {};
                strncpy(temp, m_customize, 30);
                temp[30] = '\0';
                ostr << temp;
            }
        }
        return ostr;
    }

    // Override order method
    bool Food::order()
    {
        // Create menu with proper indentation for "Food Size Selection" for subMenu
        Menu foodMenu("Food Size Selection", "Back", 3);
        foodMenu << "Adult" << "Child";

        // Display menu and get selection
        int selection = foodMenu.select();

        if (selection == 1)
        {
            m_child = false;
            m_ordered = true;
        }
        else if (selection == 2)
        {
            m_child = true;
            m_ordered = true;
        }
        else
        {
            // Back option selected
            m_ordered = false;
            delete[] m_customize;
            m_customize = nullptr;
            return false;
        }

        // Prompt for customization
        cout << "Special instructions" << endl;
        cout << "> ";

        string instructions;
        getline(cin, instructions);

        // If user entered customization
        if (!instructions.empty())
        {
            ut.alocpy(m_customize, instructions.c_str());
        }
        else
        {
            delete[] m_customize;
            m_customize = nullptr;
        }

        return true;
    }

    // Override ordered method
    bool Food::ordered() const
    {
        return m_ordered;
    }

    // Override read method
    ifstream& Food::read(ifstream& file)
    {
        char name[256] = {};
        double price = 0.0;

        if (file.getline(name, 256, ','))
        {
            file >> price;
            file.ignore(1000, '\n'); // Skip to next line

            // Set values to the object
            Billable::name(name);
            Billable::price(price);

            // Reset Food-specific attributes
            m_ordered = false;
            m_child = false;
            delete[] m_customize;
            m_customize = nullptr;
        }

        return file;
    }

    // Override price method
    double Food::price() const
    {
        double basePrice = Billable::price();

        if (ordered() && m_child)
        {
            return basePrice * 0.5; // Half price for child portion
        }

        return basePrice; // Regular price for adult portion or if not ordered
    }

    /***************************************************************/
    /***************************************************************/

    // Insertion operator for easy printing
    ostream& operator<<(ostream& ostr, const Food& food)
    {
        // Just output the name for the regular insertion operator
        return ostr << static_cast<const char*>(food);
    }

}