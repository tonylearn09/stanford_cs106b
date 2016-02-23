/*
 * File: InverseGenetics.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the InverseGenetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

void findAllPossibility(string solution, string protein,
        Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
	/* Load the codon map. */
	Map<char, Set<string> > codons = loadCodonMap();
    string protein = getLine("enter the protein: ");
    listAllRNAStrandsFor(protein, codons);

	return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
	ifstream input("codons.txt");
	Map<char, Set<string> > result;
    
	/* The current codon / protein combination. */
	string codon;
	char protein;
	
	/* Continuously pull data from the file until all data has been
	 * read.
	 */
	while (input >> codon >> protein) {
		result[protein] += codon;
	}
	
	return result;
}

// wrapper function
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons)
{
    findAllPossibility("", protein, codons);
}

void findAllPossibility(string solution, string protein,
        Map<char, Set<string> >& codons)
{
    // base case
    if (protein == "") {
        cout << solution << endl;
        return;
    }

    // save the current solution
    string save = solution;
    // find the set of macthing codons
    Set<string> current = codons[protein[0]];
    // loop through all the possible codons
    foreach (string s in current) {
        // if use this codons, then add to solution
        solution += s;
        // find the rest of codons
        findAllPossibility(solution, protein.substr(1), codons);
        // let solution be back to the original one
        // so that it can try another string again
        solution = save;
    }
}
