/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

void foundLadder(string startWord, string endWord);
void printLadder(const Vector<string>& vec);
void generateAndEnque(Queue<Vector<string> >& ladder, Vector<string>& current, 
        const Lexicon& words, Lexicon& previousAppear, int wordLength);
void enqueueAndStoreWord(Queue<Vector<string> >& ladder, string& copyString, 
        Lexicon& previousAppear, Vector<string>& current);

int main() {
    while (true) {
        string startWord;
        startWord = getLine("Enter start word (RETURN to quit): ");
        if (startWord.empty())
            break;

        string endWord;
        endWord = getLine("Enter desitination word: ");

        if (startWord.size() != endWord.size()){
            cerr << "wrong destination" << endl;
            continue;
        }

        foundLadder(startWord, endWord);
    }

    return 0;
}

void foundLadder(string startWord, string endWord)
{
    // queue store vector<string> with whole possible ladder
    // at first the vector<string> only one element, later two , and so on
    Queue<Vector<string> > ladder;
    // the start word
    Vector<string> start;
    start.add(startWord);
    ladder.enqueue(start);

    // to verify it is a word
    Lexicon words("EnglishWords.dat");
    // to store words that appear before, so wont have infinite loop
    // and for efficiency, too
    Lexicon previousAppear;

    // the size of the word
    int wordLength = startWord.size();

    // if queue is not empty
    while (!ladder.isEmpty()) {
        Vector<string> current = ladder.dequeue();
        // printLadder(current);

        // base case
        if (current[current.size() - 1] == endWord) {
            cout << "Found ladder: ";
            // print the vector that store the min ladder
            printLadder(current);
            return;
        }

        generateAndEnque(ladder, current, words, previousAppear, wordLength);
    }

    // if dequeue all the possible answer and didn't found
    if (ladder.isEmpty()) {
        cout << "No ladder found" << endl;
    }
}



void printLadder(const Vector<string>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}


void generateAndEnque(Queue<Vector<string> >& ladder, Vector<string>& current, 
        const Lexicon& words, Lexicon& previousAppear, int wordLength)
{
    for (int i = 0; i < wordLength; ++i) {
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            // copy the current last string
            string copyString = current[current.size() - 1];
            // modify just one place
            copyString[i] = ch;

            // if it is a valid word, and it did not appear before
            if (words.contains(copyString) && !previousAppear.contains(copyString))
                enqueueAndStoreWord(ladder, copyString, previousAppear, current);
        }
    }
}


void enqueueAndStoreWord(Queue<Vector<string> >& ladder, string& copyString, 
        Lexicon& previousAppear, Vector<string>& current)
{
    Vector<string> newVectorCanTry = current;
    newVectorCanTry.add(copyString);
    previousAppear.add(copyString);
    // printLadder(newVectorCanTry);
    ladder.enqueue(newVectorCanTry);
}

