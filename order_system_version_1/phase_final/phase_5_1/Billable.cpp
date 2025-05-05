/***********************************************************************
// OOP244 Project, Billable Module
//
// File	Billable.cpp
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
Module: Billable
Filename: Billable.cpp
Version 1.0
Author: Thai Hoa Nguyen
Revision History
-----------------------------------------------------------
Date      Reason
2024/?/?  Preliminary release
2024/?/?  Debugged DMA
-----------------------------------------------------------
Function: 
Overloaded + operator to add the price of a Billable item to a double value.
AND 
Overloaded += operator to add the price of a Billable item to a double variable.
Source: 
- https://www.geeksforgeeks.org/operator-overloading-cpp/
- https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
- https://www.geeksforgeeks.org/cpp-assignment-operator-overloading/
- https://cplusplus.com/forum/beginner/6331/
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Billable.h"
#include "Utils.h"
#include <cstring>

namespace seneca
{
    /************************/
    /************************/
    // Protected methods
    void Billable::price(double value)
    {
        m_price = value;
    }

    void Billable::name(const char *name)
    {
        ut.alocpy(m_name, name);
    }
    /************************/
   /************************/


   /************************/
   /************************/
   //CONSTRUCTOR & DESTRUCTOR//
   
  // Copy constructor to create a deep copy of another Billable object.
    Billable::Billable(const Billable &other) : m_name(nullptr), m_price(0.0)
    {
        *this = other;
    }

    // Copy assignment operator to assign the contents of another Billable object to this one.
    Billable &Billable::operator=(const Billable &other)
    {
        if (this != &other)
        {
            ut.alocpy(m_name, other.m_name);
            m_price = other.m_price;
        }
        return *this;
    }

    // Destructor to clean up dynamically allocated memory for the name.
    Billable::~Billable()
    {
        delete[] m_name;
        m_name = nullptr;
    }

 /************************/
 /************************/

    // Returns the price of the billable item
    double Billable::price() const
    {
        return m_price;
    }

    // Conversion operator to allow the Billable object to be treated as a C-string (returns the name).
    Billable::operator const char *() const
    {
        return m_name;
    }

    // Overloaded + operator to add the price of a Billable item to a double value.
    double operator+(double money, const Billable &B)
    {
        return money + B.price();
    }

    // Overloaded += operator to add the price of a Billable item to a double variable.
    double &operator+=(double &money, const Billable &B)
    {
        money += B.price();
        return money;
    }

}