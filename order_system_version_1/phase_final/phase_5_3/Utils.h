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
#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H
namespace seneca
{
    class Utils
    {
    public:
        char* alocpy(const char* src) const;
        char* alocpy(char*& des, const char* src) const;
        char* strcpy(char* des, const char* src) const;
        int strlen(const char* str) const;
        bool isspace(char ch) const;
        bool isspace(const char* cstring) const;

        int getInt() const;
        int getInt(int min, int max) const;

        // Function to create a bill file name based on bill number
        char* makeBillFileName(char* filename, size_t billNo) const;
    };
    extern Utils ut; // makes the ut object available where Utils.h is included
    // to call a Utils function call it as follows
    // ut.strcpy(des, src);
}

#endif // !SENECA_UTILS_H
