/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
        Vector< Set<string> >& locations,
        int numHospitals,
        Vector< Set<string> >& result);

bool coverAllCities(Set<string>& cities, Vector<Set<string> >& check);
bool existInResult(Vector<Set<string> >& result, Set<string>& check);

int main() {
    // test code
    Set<string> cities;
    cities += "A", "B", "C", "D", "E", "F";
    cout << cities << endl;

    Vector<Set<string> > locations;
    Set<string> coverCities1;
    coverCities1 += "A", "B", "C";
    Set<string> coverCities2;
    coverCities2 += "A", "C", "D";
    Set<string> coverCities3;
    coverCities3 += "B", "F";
    Set<string> coverCities4;
    coverCities4 += "C", "E", "F";
    locations.add(coverCities1);
    locations.add(coverCities2);
    locations.add(coverCities3);
    locations.add(coverCities4);

    Vector<Set<string> > result;

    int numHospitals = getInteger("enter how many hospital to build: ");
    if (numHospitals > locations.size()) {
        cout << "not enough hospital" << endl;
        return 1;
    }
    // test code end

    if (canOfferUniversalCoverage(cities, locations, numHospitals, result))
        for (int i = 0; i < result.size(); ++i) 
            cout << result[i] << endl;
    else
        cout << "can't cover the whole cities" << endl;

    return 0;
}



// backtracking
bool canOfferUniversalCoverage(Set<string>& cities,
        Vector< Set<string> >& locations,
        int numHospitals,
        Vector< Set<string> >& result)
{
    // base case: have build specify number of hospitals
    if (numHospitals <= 0)
        // check whether all the cities was cover
        return coverAllCities(cities, result);

    for (int i = 0; i < locations.size(); ++i) {
        // make sure don't duplicate existing hospital
        if (!existInResult(result, locations[i])) {
            // save the current result for backup
            Vector<Set<string> > save = result;
            // do the decision
            result.add(locations[i]);
            // do the recursive step to check if it can succeed
            if (canOfferUniversalCoverage(cities, locations,
                        numHospitals - 1, result))
                return true;
            else
                // unmake the choice
                result = save;
        }
    }

    // check all the condition, and can't succeed
    return false;
}

// to see whether all the cities can be covered
bool coverAllCities(Set<string>& cities, Vector<Set<string> >& check)
{
    Set<string> res;
    for (int i = 0; i < check.size(); ++i) {
        foreach (string str in check[i]) {
            if (!res.contains(str))
                res.add(str);
        }
    }

    return cities == res;
}

// check whether 'check' is in 'result'
bool existInResult(Vector<Set<string> >& result, Set<string>& check)
{
    for (int i = 0; i < result.size(); ++i) {
        if (result[i] == check)
            return true;
    }

    return false;
}
