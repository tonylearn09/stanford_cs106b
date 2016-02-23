/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <ctime>
#include "console.h"
#include "simpio.h"

using namespace std;

int combination(int n, int k)
{
    if (n == k || k == 0)
        return 1;
    else {
        return combination(n - 1, k)
            + combination(n - 1, k - 1);
    }
}

int main() 
{
    while (true) {
        int n = getInteger("enter n for C: ");
        int k = getInteger("enter k for C: ");
        int answer = combination(n, k);
        cout << answer << endl;
    }
    return 0;
}
