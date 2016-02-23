/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"

using namespace std;

void randomGenerater()
{
    setRandomSeed(time(0));
    int head = 0;
    int tail = 0;
    while (head != 3) {
        if (randomInteger(0, 1) == 0) { 
            cout << "head" << endl;
            ++head;
        } else {
            cout << "tail" << endl;
            ++tail;
            head = 0;
        }
    }
}

int main() 
{
    randomGenerater();
    return 0;
}

