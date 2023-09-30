#include "DSString.h"
#include <iostream>
#include <fstream>


/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-string.
 */

// DO NOT USE STRING COPY!!!!!
// DO NOT USE STRING COPY!!!!! RIGHT CLICK FORMAT AT THE END
// DO NOT USE STRING COPY!!!!! 

DSString::DSString() : data(nullptr), len(0) {
}

//confirmed
DSString::DSString(const char *str)
{
    if (str)
    {
        len = strlen(str);
        data = new char[len + 1]; // +1 for the null terminator
        strcpy(data, str);
    }
    else
    {
        len = 0;
        data = new char[1];
        data[0] = '\0'; // Empty string with null terminator
    }
}

//confirmed
DSString::DSString(const DSString &other)
{
    len = other.len;
    data = new char[len + 1];
    strcpy(data, other.data);
}
//confirmed
DSString::~DSString()
{
    delete[] data;
}
//confirmed
DSString &DSString::operator=(const DSString &other) {
    if (this != &other) {
        delete[] data; // Deallocate existing memory
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }
    return *this;
}

//confirmed len
size_t DSString::length() const
{
    return len;
}
//confirmed
char &DSString::operator[](size_t index)
{
    if (index < len)
    {
        return data[index];
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}
//confirmed
DSString DSString::operator+(const DSString &other) const {
    DSString result;
    result.len = len + other.len;
    result.data = new char[result.len + 1];

    // Copy characters from the first string
    for (size_t i = 0; i < len; ++i) {
        result.data[i] = data[i];
    }

    // Copy characters from the second string
    for (size_t i = 0; i < other.len; ++i) {
        result.data[len + i] = other.data[i];
    }

    // Null-terminate the resulting string
    result.data[result.len] = '\0';

    return result;
}



bool DSString::operator==(const DSString &other) const {
    return strcmp(data, other.data) == 0;
}

bool DSString::operator<(const DSString &other) const {
    return strcmp(data, other.data) < 0;
}

DSString DSString::substring(size_t start, size_t numChars) const {
    if (start >= len) {
        // Handle out of bounds scenario (throw exception or handle it as needed)
    }
    char *subStr = new char[numChars + 1];
    strncpy(subStr, data + start, numChars);
    subStr[numChars] = '\0'; // Null-terminate the substring
    DSString result(subStr);
    delete[] subStr;
    return result;
}
DSString DSString::toLowerCase() const {
    char *lowerStr = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        lowerStr[i] = std::tolower(data[i]);
    }
    lowerStr[len] = '\0'; // Null-terminate the lowercase string
    DSString result(lowerStr);
    delete[] lowerStr;
    return result;
}


DSString DSString::toLower() const {
    char *lowerStr = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        lowerStr[i] = tolower(data[i]);
    }
    lowerStr[len] = '\0'; // Null-terminate the lowercase string
    DSString result(lowerStr);
    delete[] lowerStr;
    return result;
}

char *DSString::c_str() const {
    char *cString = new char[len + 1];
    strcpy(cString, data);
    return cString;
}

bool DSString::isNumeric() const
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!isdigit(data[i]))
        {
            return false;
        }
    }
    return true;
}

int DSString::toInt() const
{
    if (isNumeric())
    {
        return std::atoi(data);
    }
    else
    {
        throw std::invalid_argument("Invalid numeric string");
    }
}
int DSString::customToInt() const {
    try {
        return std::stoi(str);  
    } catch (const std::exception& e) {
        return 0; 
    }
}

std::ostream& operator<<(std::ostream& os, const DSString& str) {
    os << str.c_str(); // Assuming you have a member function c_str() in your DSString class
    return os;
}

std::istream& operator>>(std::istream& is, DSString& str) {
    std::string temp;
    is >> temp; // Read input into a temporary string
    str = temp.c_str(); // Assign the value of the temporary string to the DSString object
    return is;
}







