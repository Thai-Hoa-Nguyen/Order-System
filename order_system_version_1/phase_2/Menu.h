/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.1
// started by Fardad
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name Thai Hoa Nguyen            Date            Reason
// Student ID: 175752237
/////////////////////////////////////////////////////////////////
***********************************************************************/
/*---------------------------------------------------------- -
- Defined Getter Function to Access menuItemContent Safely
		  const char* getContent() const { return menuItemContent;}

- Defined Display, make the Menu Title shows inside each table 
		  void displayMainTitle() const;
		  void displaySubTitle() const;
---------------------------------------------------------- - */
#ifndef MENU_H
#define MENU_H

#include <ostream>
#include <cstring>
#include "constants.h"

namespace seneca
{
	//Forward declaration of Menu
	class Menu;

	class MenuItem
	{

	private:

		char* menuItemContent;
		unsigned int indentNumber;
		unsigned int indentSize;
		int menuObject;

		// Constructor with parameter
		MenuItem(const char* menu_ItemContent, unsigned int indent_Number, unsigned int indent_Size, unsigned int menu_Object); // Change menu_Object to unsigned int

		//Default Constructor
		MenuItem() = default;

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


		//Only the Menu Class can access the MenuItem objects
		friend class Menu;

	public:
		
		//Getter Function to Access menuItemContent Safely
		const char* getContent() const { return menuItemContent; }

	};


	class Menu
	{

	private:

		unsigned int indentNumber; // track indentation level of MenuItems
		unsigned int indentSize; // track spacing for indentation
		unsigned int numItem; // track total item in Menu

		MenuItem title; // Menu title 
		MenuItem exitOption; // Exit toggle
		MenuItem entryPrompt; // Enter entry "> _" 

		MenuItem* item[seneca::MaximumNumberOfMenuItems]; // list of MenuItems


	public:

		//Default constructor
		Menu() = default;

		//Constructor with 4 arguments
		Menu(const char* c_title, const char* exit_Option = "Exit", unsigned int indent_Number = 0, unsigned int indent_Size = 3); 

		// Rules of three
		/************************/
		//Destructor
		~Menu();

		//Copy Destructor
		Menu(const Menu& other) = delete;
		
		//Copy Assignment Operator
		Menu& operator=(const Menu& other) = delete;
		/************************/

		//Operator Overload
		Menu& operator<<(const char* menuItemContent);

		//select Method
		size_t select() const;

		//Display, make the Menu Title shows inside each table 
		void displayMainTitle() const;
		void displaySubTitle() const;

	};

	// Insertion Operator Overload into ostream
	size_t operator<<(std::ostream& ostr, const Menu& m);
}


#endif // !MENU_H