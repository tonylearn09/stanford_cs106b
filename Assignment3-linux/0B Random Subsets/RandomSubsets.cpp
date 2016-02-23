/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s);

int main() {
	Set<int> testSet;
	testSet += 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
	cout << randomSubsetOf(testSet) << endl;
	//cout << testSet << endl;
	return 0;
}

Set<int> randomSubsetOf(Set<int>& s)
{
    // the only subset of the empty set is the empty set
    if (s.isEmpty())
        return s;

    // extract the first element from the set
    int element = s.first();

    // choose a random subset of what remain
    // remove the first element
    s -= element;
    // compute the random subset
    Set<int> removeElementSubsetResult = randomSubsetOf(s);

    // add back the first element
    // need to add this back, since it is pass by reference
    s += element;

    // randomly choose wheter add the element back in
    return randomChance(0.5) ? removeElementSubsetResult
        : removeElementSubsetResult + element;
}
