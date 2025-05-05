/***********************************************************************
// OOP244 Project, Ordering Module
//
// File	Ordering.h
// Version 0.1
// Description
// header file for the Ordering module
// Revision History
// -----------------------------------------------------------
// Name Thai Hoa Nguyen            Date            Reason
// Student ID: 175752237
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include <iostream>
#include <fstream>
#include "Billable.h"
#include "Food.h"
#include "Drink.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"

namespace seneca
{
    class Ordering
    {
    private:
        // Counters
        unsigned int m_foodCounter{};
        
        unsigned int m_drinkCounter{};
        
        unsigned int m_billableCounter{};

        // Bill serial number
        unsigned int m_billNumber{ 1 };

        // Dynamic arrays
        Food* m_foodArray{ nullptr };
        Drink* m_drinkArray{ nullptr };

        // Array of Billable pointers
        Billable* m_billItems[MaximumNumberOfBillItems]{};

        // Private methods
        void billTitlePrint(std::ostream& os) const;
       
        void printTotals(std::ostream& os, double total) const;
        
        size_t countRecords(const char* file) const;

    public:
        // Constructor and Destructor
        Ordering(const char* drinkDataFile, const char* foodDataFile);
        
        //Destructor
        ~Ordering();

        /******************************/
        /******************************/
        /************Queries***********/
        operator bool() const;
        unsigned int noOfBillItems() const;
        bool hasUnsavedBill() const;
        /******************************/
        /******************************/

        // Methods for main application menu
        void listFoods() const;
        void listDrinks() const;

       
        /// ms4_tester_prof.cpp: In function ‘int main()’:
        /// ms4_tester_prof.cpp:45 : 8 : error : ‘class seneca::Ordering’ has no member named ‘ListDrinks’
        /// ord.ListDrinks();
        /// </summary>
        void ListDrinks() const 
        { 
       /// <summary>
       /// It allows the tester code to run without modifications 
       /// while maintaining your original method naming.
       /// </summary>
       /// <summary>
            listDrinks(); //Fix due to tester on Matrix 
        };
        /*************************************************/
        /*************************************************/

        void orderFood();
        void orderDrink();
        void printBill(std::ostream& os) const;
        void resetBill();
    };
}

#endif // !SENECA_ORDERING_H
