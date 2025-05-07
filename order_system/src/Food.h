#ifndef FOOD_H
#define FOOD_H

#include "Billable.h"

namespace seneca
{
    // Derive Class Food to base class Billable 
    class Food : public Billable
    {
    private:
        bool m_ordered{};
        bool m_child{};
        char *m_customize{};

    public:
        
        /******************************************************/
        /******************************************************/
                /*Constructors and rule of three*/
        
        //Default constructor
        Food() = default;

        //Constructor 
        Food(const Food &other);
        
        //Destructor
        ~Food();
        
        //Copy assignment operator
        Food &operator=(const Food &other);
       
        /******************************************************/
        /******************************************************/
        
        
        // Pure virtual methods implementation
        std::ostream &print(std::ostream &ostr = std::cout) const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream &read(std::ifstream &file) override;

        // Override price to adjust based on portion type
        double price() const override;
    };

    // Insertion operator for easy printing
    std::ostream &operator<<(std::ostream &ostr, const Food &food);
}

#endif // !FOOD_H