#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <stdexcept> // using with std::out_of_range

#include "Utils.h"

using namespace std;
namespace seneca
{

    Utils ut;

    char* Utils::alocpy(const char* src) const
    {
        char* des{};
        return alocpy(des, src);
    }

    char* Utils::alocpy(char*& des, const char* src) const
    {
        delete[] des;
        des = nullptr;
        if (src)
        {
            des = new char[strlen(src) + 1];
            strcpy(des, src);
        }
        return des;
    }
    char* Utils::strcpy(char* des, const char* src) const
    {
        int i;
        for (i = 0; src[i]; i++)
            des[i] = src[i];
        des[i] = char(0);
        return des;
    }
    int Utils::strlen(const char* str) const
    {
        int len;
        for (len = 0; str[len]; len++)
            ;
        return len;
    }

    bool Utils::isspace(char ch) const
    {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    bool Utils::isspace(const char* cstring) const
    {
        while (cstring && isspace(*cstring))
        {
            cstring++;
        }
        return cstring && *cstring == 0;
    }

    /*Solve FoolProof*/
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/

    // Removes leading and trailing whitespace from a given string
    std::string trim(const std::string& str)
    {
        // avoid user try to enter " 123 "
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos)
        {
            return "";
        }
            
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // Checks if a string represents a valid integer, considering optional leading '+' or '-' signs
    bool isValidInteger(const std::string& str)
    {
        if (str.empty())
        {
            return false;
        }

        size_t start = 0;

        if (str[0] == '-') // input example: "-123",..
        {
            if (str.length() == 1)
            {
                return false; // Only a sign without digits
            }
            start = 1;
        }

        // force user to enter only number
        for (size_t i = start; i < str.length(); ++i)
        {
            if (!isdigit(str[i])) // example output: "thai"
            {
                return false;
            }
        }
        return true;
    }

    // Determines if a string contains any numeric digits
    bool containsDigit(const std::string& str)
    {
        // check when user try to enter number and character together or only characters
        // example input: "123asb" or "heloo"
        for (char ch : str)
        {
            if (isdigit(ch))
            {
                return true;
            }
        }
        return false;
    }

    // Function to read and validate an integer input
    int Utils::getInt() const
    {
        std::string userInput;
        int value = 0;

        while (true)
        {
            std::getline(std::cin, userInput);
            userInput = trim(userInput); // check trim

            if (userInput.empty())
            {
                std::cout << "You must enter a value: ";
                continue;
            }

            // Try to make print the correct format
            //  Enter only characters -> "Invalid integer:"
            //  Enter characters and numbers together -> "Only an integer please:"
            if (isValidInteger(userInput))
            {
                try
                {
                    size_t pos;
                    value = std::stoi(userInput, &pos);

                    if (pos == userInput.length())
                    {
                        break; // Successfully parsed integer
                    }
                    else
                    {
                        std::cout << "Only an integer please: ";
                    }
                }
                catch (const std::out_of_range&)
                {
                    std::cout << "Invalid integer: ";
                }
            }
            else if (containsDigit(userInput))
            {
                std::cout << "Only an integer please: ";
            }
            else
            {
                std::cout << "Invalid integer: ";
            }
        }

        return value;
    }

    // Modified getInt(min, max) function using stringToInt()
    int Utils::getInt(int min, int max) const
    {
        int value = 0;
        bool isValid = false;

        while (!isValid)
        {
            value = getInt();

            if (value < min || value > max)
            {
                std::cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";
            }
            else
            {
                isValid = true;
            }
        }

        return value;
    }

    char* Utils::makeBillFileName(char* filename, size_t billNo) const
    {
        char billFileName[21] = "bill_";
        size_t temp = billNo;
        int cnt = 5;
        int length;
        // Calculate the number of digits
        do
        {
            cnt++;
            temp /= 10;
        } while (temp > 0);
        length = cnt;
        // Convert each digit to character from the end
        while (billNo > 0)
        {
            billFileName[--cnt] = (billNo % 10) + '0';
            billNo /= 10;
        }
        // Handle the case when billNo is 0
        if (billFileName[cnt - 1] == '\0')
        {
            billFileName[--cnt] = '0';
        }
        // Attach .txt to the end of the file name
        for (int i = 0; ".txt"[i]; i++)
        {
            billFileName[length++] = ".txt"[i];
        }
        billFileName[length] = '\0';
        strcpy(filename, billFileName);
        return filename;
    }

    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
}