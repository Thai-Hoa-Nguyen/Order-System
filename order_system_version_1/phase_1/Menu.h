#ifndef MENU_H
#define MENU_H

#include <ostream>

namespace seneca
{
	class MenuItem
	{

	private:

		char* menuItemContent;
		unsigned int indentNumber;
		unsigned int indentSize;
		int menuObject;

	public:

        // Constructor with parameter
        MenuItem(const char* menu_ItemContent, unsigned int indent_Number, unsigned int indent_Size, unsigned int menu_Object); // Change menu_Object to unsigned int
		
		//Default Constructor
		MenuItem() : menuItemContent(nullptr), indentNumber(0), indentSize(0), menuObject(0) {};

		//Destructor
		~MenuItem();

		//Copy Constructor (prevented the copy constructor)
		MenuItem(const MenuItem& menuItem_copy) = delete;

		//Copy assignment operator (prevented the copy assignment)
		MenuItem& operator=(const MenuItem& menuItem_copyOperator) = delete;

		
		//Overloaded bool
		operator bool() const;

		//Display with argument
		std::ostream& display(std::ostream& output) const;

		// Display without argument 
		std::ostream& display() const; //(defaults to std::cout)
		
	};
}


#endif // !MENU_H