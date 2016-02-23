/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment 3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);

int main() {
    while (true) {
        int street = getInteger("enter the street number: ");
        int avenue = getInteger("enter the avenue number: ");

        cout << "numver of paths back: " 
            << numPathsHome(street, avenue) << endl;
    }

	return 0;
}

int numPathsHome(int street, int avenue)
{
    // invalid index, there is no path back home(1, 1)
    if (street < 1 || avenue < 1)
        return 0;
    // karel is at (1, 1), there is exactly one
    // path back: just stay where they are
    else if (street == 1 && avenue == 1)
        return 1;
    // sum up all the possible journey that begin with
    // step left ot step down
    else
        return numPathsHome(street - 1, avenue)
            + numPathsHome(street, avenue - 1);
}
