/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
using namespace std;


void createSeedMap(string text, int order, 
        Map<string, Vector<char> >& seedMap);
void parseInput(ifstream& input, int order, 
        Map<string, Vector<char> >& seedMap);

string getInitialSeed(Map<string, Vector<char> >& seedMap);
void generateRandomText(string seed,
        Map<string, Vector<char> >& seedMap);

int main()
{
    ifstream infile;
    while (true) {
        string filename;
        filename = getLine("please enter filename containing sorce text: ");
        infile.open(filename.c_str());
        if (!infile.fail())
            break;
        cout << "file open error!" << endl;
        infile.clear();
    }


    int order;
    while (true) {
        order = getInteger("what order of analysis? (a number from 1 to 10): ");
        if (order >= 1 && order <= 10)
            break;
        cout << "invalid order!" << endl;
    }

    Map<string, Vector<char> > seedMap;
    parseInput(infile, order, seedMap);
    infile.close();

    string seed = getInitialSeed(seedMap);
    generateRandomText(seed, seedMap);

    // for next time usage
    seedMap.clear();

    return 0;
}

void parseInput(ifstream& input, int order, 
        Map<string, Vector<char> >& seedMap)
{
    cout << "analyzing input text ... " << endl;
    // read all the text file char by char
    // and store all the chars in string text
    string text;
    char ch;
    while (input.get(ch)) {
        // process data
        text += ch;
    }
    createSeedMap(text, order, seedMap);
}

void createSeedMap(string text, int order, 
        Map<string, Vector<char> >& seedMap) 
{
    // only text.size() - order seed
    for (int i = 0; i < text.size() - order; ++i) {
        string seedString = text.substr(i, order);

        if (i + order < text.size()) {
            // the following char of the seed
            char c = text[i + order];
            // vector for the following chars
            Vector<char> nextChars;
            if (seedMap.containsKey(seedString)) {
                nextChars = seedMap[seedString];
                nextChars.add(c);
                seedMap[seedString] = nextChars;
            } else {
                nextChars.add(c);
                seedMap[seedString] = nextChars;
                // cout << seedString << endl;
            }
        }
    }
}

string getInitialSeed(Map<string, Vector<char> >& seedMap)
{
    string mostFrequentSeed;
    int maxVectorSize = 0;

    // loop through all the seed in the map
    // find the most frequent one
    foreach(string seed in seedMap) {
        if (seedMap[seed].size() > maxVectorSize) {
            maxVectorSize= seedMap[seed].size();
            // cout << seedMap[seed].size() << endl;
            mostFrequentSeed = seed;
        }
    }

    return mostFrequentSeed;
}


void generateRandomText(string seed,
        Map<string, Vector<char> >& seedMap)
{
    // print out at most 2000 chars
    const int CHAROUTPUTNUM = 2000;

    // vector to store the following chars of seed
    Vector<char> seedChars;

    cout << seed;
    for (int i = 0; i < CHAROUTPUTNUM; ++i) {
        if (seedMap.containsKey(seed))
            seedChars = seedMap[seed];
        else
            break; // seed not found

        int size = seedChars.size();
        if (size == 0)
            break; // seed has no associated char

        // choose next char at the probability
        // of its occurence time
        int randomIndex = randomInteger(0, size - 1);
        char c = seedChars[randomIndex];
        cout << c;

        // erase from zero index, and the erase length
        // is 1
        seed.erase(0, 1);
        seed += c;
    }

    cout << endl;
}
