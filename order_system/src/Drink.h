#ifndef DRINK_H
#define DRINK_H

#include "Billable.h"

namespace seneca
{
    class Drink : public Billable
    {
    private:
        // 'S', 'M', 'L', 'X' for sizes or 0 for unset
        char m_size{}; 

    public:
        
        // Default Constructor
        Drink() = default;

        
        /***************************************/
        /***************************************/
        // Pure virtual methods implementation
        std::ostream &print(std::ostream &ostr = std::cout) const override;
        
        bool order() override;
        bool ordered() const override;
        
        std::ifstream &read(std::ifstream &file) override;
        /***************************************/
        /***************************************/


        // Override price to adjust based on size
        double price() const override;
    };

    // Insertion operator for easy printing
    std::ostream &operator<<(std::ostream &ostr, const Drink &drink);
}

#endif // !DRINK_H