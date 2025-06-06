#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include "Drink.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca
{

    // Declare the Utils object
    extern Utils ut;

    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /*********************OVERIDE METHOD********************/

    // Override print method
    ostream& Drink::print(ostream& ostr) const
    {
        if (this)
        {
            // Print name (left-justified, padded with dots)
            ostr.width(28);
            ostr.fill('.');
            ostr.setf(ios::left);
            ostr << static_cast<const char*>(*this);
            ostr.unsetf(ios::left);

            // Print size
            if (ordered())
            {
                if (m_size == 'S')
                    ostr << "SML..";
                else if (m_size == 'M')
                    ostr << "MID..";
                else if (m_size == 'L')
                    ostr << "LRG..";
                else if (m_size == 'X')
                    ostr << "XLR..";
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
        }

        return ostr;
    }

    // Override order method
    bool Drink::order()
    {
        // Create menu with correct indentation and also using "Drink Size Selection" as title for subMenu
        Menu drinkMenu("Drink Size Selection", "Back", 3);

        // Display Size
        drinkMenu << "Small" << "Medium" << "Larg" << "Extra Large";

        // Display menu and get selection
        int selection = drinkMenu.select();

        if (selection == 1)
            m_size = 'S';
        else if (selection == 2)
            m_size = 'M';
        else if (selection == 3)
            m_size = 'L';
        else if (selection == 4)
            m_size = 'X';
        else
            m_size = 0; // Back option selected, set to unordered state

        return ordered();
    }

    // Override ordered method
    bool Drink::ordered() const
    {
        return m_size == 'S' || m_size == 'M' || m_size == 'L' || m_size == 'X';
    }

    // Override read method
    ifstream& Drink::read(ifstream& file)
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

            // Default size value
            m_size = 0;
        }

        return file;
    }

    // Override price method
    double Drink::price() const
    {
        double basePrice = Billable::price();

        if (!ordered() || m_size == 'L')
        {
            return basePrice;
        }
        else if (m_size == 'S')
        {
            return basePrice * 0.5; // Half price for small
        }
        else if (m_size == 'M')
        {
            return basePrice * 0.75; // 3/4 price for medium
        }
        else if (m_size == 'X')
        {
            return basePrice * 1.5; // 1.5x price for extra large
        }

        return basePrice; // Default
    }

    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/

    // Insertion operator for easy printing
    ostream& operator<<(ostream& ostr, const Drink& drink)
    {
        // Just output the name for the regular insertion operator
        return ostr << static_cast<const char*>(drink);
    }

}