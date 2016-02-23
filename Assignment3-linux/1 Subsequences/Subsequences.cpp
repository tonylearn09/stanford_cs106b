/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    while (true) {
        cout << "enter text: ";
        string text = getLine();

        cout << "enter subsequence: ";
        string subsequence = getLine();

        if (isSubsequence(text, subsequence))
            cout << "it is subsequence." << endl;
        else
            cout << "it is not subsequence." << endl;
    }
    return 0;
}

bool isSubsequence(string text, string subsequence)
{
    // put at first
    // empty string is subsequence of all strings
    if (subsequence == "")
        return true;
    // no other string except empty string is 
    // subsequence of empty string
    else if (text == "" && subsequence != "")
        return false;

    // two conditions:
    // 1. first char of text match the first
    // char of the subsequence
    // 2. first char of text don't match the first char 
    // of the subsequence
    else {
        if (text[0] == subsequence[0])
            return isSubsequence(text.substr(1), 
                    subsequence.substr(1));
        else
            return isSubsequence(text.substr(1),
                    subsequence);
    }
}
