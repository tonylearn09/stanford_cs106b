/*******************************************************************
 * File: FleschKincaid.cpp
 *
 * A program that approximates the Flesch-Kincaid grade level of a
 * piece of text.
 */

#include <iostream>
#include <fstream>
#include "tokenscanner.h"
using namespace std;

bool validendVowel(char c)
{
    if (c == 'E' || c == 'e')
        return false;
    return true;
}
int countSyllable(string str)
{
    int syllableCount = 0;
    bool HasPreviousVowel = false;
    string vowels = "aeiouyAEIOUY";
    int previousVowelIndex = -1;

    for (int i = 0; i < str.size(); ++i) {

        // if the last element is 'e', 'E', then you sholdn't count it as syllable
        if (i != str.size() - 1 || validendVowel(str[i])) {
            for (int j = 0; j < vowels.size(); ++j) {
                if (str[i] == vowels[j] ) {
                    // if previous one is not vowel
                    if (HasPreviousVowel == false) {
                        ++syllableCount;
                        HasPreviousVowel = true;
                        previousVowelIndex = i;
                        break;
                    } else if (HasPreviousVowel == true) {
                        // if previous one is vowel, then update it
                        // to be the previous vowel
                        previousVowelIndex = i;
                        break;
                    }
                }
            }
            // previousVowelIndex will update, so use it to compare with current index
            if (previousVowelIndex < i)
                HasPreviousVowel = false;
        }
    }

    // make sure at least one syllable in each word
    if (syllableCount == 0)
        syllableCount = 1;

    return syllableCount;
}

int main() 
{
    ifstream infile;
    while (true) {
        cout << "enter input file name: ";
        string filename;
        cin >> filename;

        infile.open(filename.c_str());
        if (!infile.fail())
            break;
    }

    string validWordChars = "'";
    // create a TokenScanner
    TokenScanner scanner(infile);
    // let scanner treat these puntuation as char in word
    scanner.addWordCharacters(validWordChars);
    // lete scanner ignore white space for convenience
    scanner.ignoreWhitespace();

    int sentenceCount = 0;
    int wordCount = 0;
    int syllableCount = 0;

    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        cout << "Token: [" << token << "] ";
        // check if it is word
        if (isalpha(token[0])) {
            ++wordCount;
            cout << " (word";
            cout << "; " << countSyllable(token) << " syllables" << ")";
            syllableCount += countSyllable(token);
        }
        // check if it is the sentence
        else if (token == "." || token == "!" || token == "?") {
            ++sentenceCount;
            cout << " (end of sentence)";
        }
        cout << endl;

    }

    double grade;
    grade = -15.59 + 0.39 * ((double)wordCount / sentenceCount) + 11.8 * ((double)syllableCount / wordCount);

    cout << "words: " << wordCount << endl;
    cout << "syllables: " << syllableCount << endl;
    cout << "sentences: " << sentenceCount << endl;
    cout << "grade: " << grade << endl;

    return 0;
}

