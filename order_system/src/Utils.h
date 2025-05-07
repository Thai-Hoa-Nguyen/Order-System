#ifndef UTILS_H
#define UTILS_H
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

#endif // !UTILS_H
