/*
 * This file should help you to create a minimal interface for your string class based on
 * a dynamically allocated char array. Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-string.
 */

#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

class DSString
{

private:
    char *data; // a pointer to a character array containing the string with a `\0` terminator
    size_t len; // the length of the string (without the terminator)
    std::string str; 
    // Note: we keep the terminator only so we can return a c-string version in function c_str().

public:
    /**
     * Make sure you implement the rule-of-three and use proper memory management.
     * To help you get started, you can implement the following:
     **/
    int customToInt() const;
    DSString toLowerCase() const;
    DSString();
    //confirmed
    DSString(const char *); // constructor that converts a cstring

        // Function to check if the string is numeric
    bool isNumeric() const;

    // Function to convert numeric string to integer
    int toInt() const;

    // Rule of three confirmed
    DSString(const DSString &);            // copy constructor
    ~DSString();                           // destructor
    DSString &operator=(const DSString &); // assignment operator

    //confirmed
    size_t length() const; // returns the length of the string
    //confirmed
    char &operator[](size_t); // returns a reference to the character at the given index

    DSString operator+(const DSString &) const;

    //these are not implimented 
    bool operator==(const DSString &) const;
    bool operator<(const DSString &) const;

    DSString substring(size_t start, size_t numChars) const;

    DSString toLower() const; 

    char *c_str() const;

    friend std::ostream &operator<<(std::ostream &, const DSString &);
    friend std::istream& operator>>(std::istream& is, DSString& str);
};

#endif
