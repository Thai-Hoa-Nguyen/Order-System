/***********************************************************************
// OOP244 Project, Billable Module
//
// File	Billable.h
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
#ifndef BILLABLE_H
#define BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca
{
    class Billable
    {
    private:
        char *m_name{};
        double m_price{};

    protected:
        void price(double value);
        void name(const char *name);

    public:
        // Default constructor
        Billable() = default;

        // Copy constructor
        Billable(const Billable &other);

        // Copy assignment operator
        Billable &operator=(const Billable &other);

        // Virtual destructor
        virtual ~Billable();

        // Virtual Method
        // Returns the item's price, allowing derived classes to override if needed.
        virtual double price() const;

        /**************************************************/
        /**************************************************/
        /*Pure Virtual Method*/
        virtual std::ostream &print(std::ostream &ostr = std::cout) const = 0;
        virtual bool order() = 0;
        virtual bool ordered() const = 0;
        virtual std::ifstream &read(std::ifstream &file) = 0;
        /**************************************************/
        /**************************************************/

        /**************************************************/
        /**************************************************/
        /*Operator Overloads*/
        /*Friend function*/
        friend double operator+(double money, const Billable &B);
        friend double &operator+=(double &money, const Billable &B);

        // Conversion operator: Allows the Billable object to be treated as a C-string.
        operator const char *() const;
        /**************************************************/
        /**************************************************/
    };

    double operator+(double money, const Billable &B);
    double &operator+=(double &money, const Billable &B);
}

#endif // BILLABLE_H