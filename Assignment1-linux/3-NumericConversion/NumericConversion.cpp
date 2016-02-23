/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    while (true) {
        
        string numberString;
        cout << "enter a number: ";
        cin >> numberString;
        int resultInt = stringToInt(numberString);
        cout << "string to int: " <<  resultInt << endl;
        


        int number;
        cout << "enter a number: ";
        cin >> number;
        string resultString = intToString(number);
        cout << "int to string: " <<  resultString << endl;
        
    }
   return 0;
}

string intToString(int n)
{
    // should put in the font
    // otherwise it is also <= 9, it will do ch = n + '0';
    if (n < 0) {
        n = -n;
        return "-" + intToString(n); 
    }

    if (n <= 9) {
        char ch = char(n + '0');
        return string() + ch; 
    }

    return intToString(n / 10) + intToString(n % 10);
}
int stringToInt(string str)
{
    if (str[0] == '-') {
        return (-1) * stringToInt(str.substr(1));
    }

    // base case if only one character
    if (str.size() == 1) {
        // char - '0' will be int
        return str[0] - '0';
    }

    return stringToInt(str.substr(0, str.size() - 1)) * 10 +
        stringToInt(str.substr(str.size() - 1));
} 
