/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "strlib.h"

using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int MIN_WORD_LENGTH = 4;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

// user defined type
// row: which row this cell is in
// col: which col this cell is in
struct PointT {
    int row;
    int col;
};


/* Function prototypes */

// initial
void welcome();
void giveInstructions();

void startGame(Grid<char>& board, Lexicon& englishWords);

// set up board
void setUpBoard(Grid<char>& board);

// user configuration function
bool userSetUpCube();
Vector<char> turnStringToVector(string& letters);
Vector<char> userConfigurationLetters();

// shuffle board function
Vector<string> shuffleBoardCube();
Vector<char> shuffleCubeLetters(Vector<string>& copyCubes);

// draw board
void assignBoardLetters(Grid<char>& board, Vector<char>& cubesLetters);
void drawCubes(Vector<char>& cubesLetters);

// human player turn's function
Vector<string> playerTurn(Grid<char>& board, Lexicon& englishWords);
void verifyWord(Grid<char>& board, string word,
        Vector<string>& guesses, Lexicon& englishWords);
bool alreadyGuess(Vector<string>& guesses, string word);
bool boardContainsWord(Grid<char>& board, string word);
bool recursiveFindWords(Grid<char>& board, string word,
        int row, int col, Vector<PointT>& cells);
bool outOfBound(Grid<char>& board, int row, int col);
void highlightCells(Vector<PointT>& cells);

// computer player turn's function
void computerTurn(Grid<char>& board, Lexicon& englishWords,
        Vector<string>& foundWords);
void computerFind(Grid<char>& board, string soFar,
        Lexicon& englishWords, 
        Vector<string>& foundWords, int row, int col,
        Vector<PointT>& usedCells);
bool alreadyUsedCells(Vector<PointT>& usedCells, int row, int col);


/* Main program */

int main() {

    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    Lexicon englishWords("EnglishWords.dat");

    initGBoggle(gw);
    welcome();
    giveInstructions();
    // my implementation
    Grid<char> board(4, 4);
    startGame(board, englishWords);

    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]

// start the game
void startGame(Grid<char>& board, Lexicon& englishWords)
{
    // set up the board for the game, and
    // draw the board
    setUpBoard(board);

    // store user foundWords
    Vector<string> foundWords;
    // plyer start to find the word
    foundWords = playerTurn(board, englishWords);

    // computer start to find the word
    // @param foundWords has two ability
    // first, computer store the words it find in it
    // second, computer figure out if a word is already found with it
    computerTurn(board, englishWords, foundWords);
}


// set up random board
void setUpBoard(Grid<char>& board)
{
    // draw the board with 16 square
    drawBoard(4, 4);

    // ask if user want to create board himself
    bool userCubeRequest = userSetUpCube();

    Vector<char> cubesLetters;
    if (userCubeRequest) {
        cubesLetters = userConfigurationLetters();
    } else {
        // shuffle to get random Cube
        // by shuffle algorithm given in assignment 4
        Vector<string> randomCube;
        randomCube = shuffleBoardCube();

        // choose which letter to face up
        // in each string
        cubesLetters = shuffleCubeLetters(randomCube);
    }

    // make up the board
    // remember without this, although you draw the picture cubes
    // your board is still empty
    assignBoardLetters(board, cubesLetters);

    // draw the letter on cube
    // and show in console
    drawCubes(cubesLetters);

}

// ask whether user want cube comfiguration
bool userSetUpCube()
{
    bool userSetUp = false;
    while (true) {
        cout << "you want to set up board by yourself? (y/n) ";
        string response = getLine();

        if (response == "y") {
            userSetUp = true;
            break;
        }
        else if (response == "n") {
            userSetUp = false;
            break;
        }
    }

    return userSetUp;
}



// turn a string to vector<char>
Vector<char> turnStringToVector(string& letters)
{
    Vector<char> result;
    for (int i = 0; i < letters.size(); i++)
        result.add(letters[i]);
    return result;
}


// set up the user configuration letters to assign to board
Vector<char> userConfigurationLetters()
{
    Vector<char> cubesLetters;
    while (true) {
        cout << "enter letters for configuration: " << endl;
        string letters = getLine();

        // if there are enough letters to assign
        // then we just pick the first 16 characters
        // and return it back
        if (letters.size() >= 16) {
            string temp = letters.substr(0, 16);
            cubesLetters = turnStringToVector(temp);
            break;
        }
    }
    return cubesLetters;
}


// shuffle the const array
Vector<string> shuffleBoardCube()
{
    Vector<string> copyCubes;
    // copy the const array, so that i can modify.
    // becareful that copyCubes's size is zero right now
    // can't use copyCubes[i] now
    for (int i = 0; i < 16; i++)
        copyCubes.add(STANDARD_CUBES[i]);

    // shyffle algorithm by assignment
    for (int i = 0; i < copyCubes.size(); i++) {
        int randomIndex = randomInteger(i, 
                copyCubes.size() - 1);
        swap(copyCubes[i], copyCubes[randomIndex]);
    }

    return copyCubes;
}

// choose a cube letter to be faced up
Vector<char> shuffleCubeLetters(Vector<string>& copyCubes)
{
    Vector<char> letters;
    for (int i = 0; i < copyCubes.size(); i++) {
        // choose 0~5 a number to decide which letter should be chosen
        int randomIndex = randomInteger(0, 5);
        letters.add(copyCubes[i][randomIndex]);
    }

    return letters;
}


// assign letter to the board
void assignBoardLetters(Grid<char>& board, Vector<char>& cubesLetters)
{
    int i = 0;
    for (int row = 0; row < board.numRows(); row++)
        for (int col = 0; col < board.numCols(); col++) 
            board[row][col] = cubesLetters[i++];
}


// draw the letter in the cube
void drawCubes(Vector<char>& cubesLetters)
{
    int i = 0;
    for (int row = 0; row < 4; row++) 
        for (int col = 0; col < 4; col++)
            labelCube(row, col, cubesLetters[i++]);
}


Vector<string> playerTurn(Grid<char>& board, Lexicon& englishWords)
{
    Vector<string> guesses;

    string word;
    while (true) {
        word = getLine("enter word: ");
        if (word == "")
            break;
        // can accept lower case letter
        word = toUpperCase(word);
        // verify if it really find a word
        verifyWord(board, word, guesses, englishWords);
    }

    return guesses;
}

void verifyWord(Grid<char>& board, string word,
        Vector<string>& guesses, Lexicon& englishWords)
{
    // word not found or already guess
    if (alreadyGuess(guesses, word)) {
        cout << "you have already guess this word." << endl;
        return;
    } else if (!englishWords.contains(word) || 
            word.length() < MIN_WORD_LENGTH) {
        cout << "not a valid word!" << endl;
        return;
    }

    // word found
    if (boardContainsWord(board, word)) {
        guesses.add(word);
        // show the word in the graph, and update the point
        recordWordForPlayer(word, HUMAN);
    } else {
        cout << "couldn't find this entered word." << endl;
    }
}

// see if this word already contains in the word its guesses
bool alreadyGuess(Vector<string>& guesses, string word)
{
    for (int i = 0; i < guesses.size(); i++)
        if (guesses[i] == word)
            return true;

    return false;
}

// check if board really contain the pass in word
bool boardContainsWord(Grid<char>& board, string word)
{
    //cout << word << endl;
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            Vector<PointT> cells;
            // succeed to find the first character
            if (word[0] == board[row][col]) {
                if (recursiveFindWords(board, word.substr(1), row, col, cells)) {
                    highlightCells(cells);
                    return true;
                }
            }
        }
    }

    // fail to find the word
    return false;
}

// backtracking
bool recursiveFindWords(Grid<char>& board, string word,
        int row, int col, Vector<PointT>& cells)
{
    // cout << word << endl;

    // if all the characters in word is checked, then we are done
    if (word == "") {
        // remember to add this last letter to cells
        PointT p;
        p.row = row;
        p.col = col;
        cells.add(p);

        return true;
    }

    // loop through all the neighbor
    for (int vertical = -1; vertical <= 1; vertical++) {
        for (int horizon = -1; horizon <= 1; horizon++) {
            // verify it is a valid place
            // not out of bound, and
            // not the original place
            if (!outOfBound(board, row + vertical, col + horizon) &&
                    !(horizon == 0 && vertical == 0) &&
                    !alreadyUsedCells(cells, row + vertical, col + horizon)) {
                // board really contain the frontest letter
                if (word[0] == board[row + vertical][col + horizon]) {
                    // store the copy.
                    // if letter it fail, we can unmake the choice
                    string copyCurrentWord = word;

                    word = word.substr(1); 
                    //cout << word << endl;
                    
                    PointT p;
                    p.row = row;
                    p.col = col;
                    cells.add(p);
                    
                    if (recursiveFindWords(board, word, row + vertical, col + horizon, cells)) {
                        return true;
                    } else {
                        // if this try fail
                        // we unmake the choice
                        word = copyCurrentWord;
                        cells.remove(cells.size() - 1);
                    }
                }
            }
        }
    }

    // try all possible answer, but fail
    return false;
}

// check if a given place is valid
bool outOfBound(Grid<char>& board, int row, int col)
{
    if (row >= 0 && row < board.numRows() && col >= 0 && col < board.numCols())
        return false;

    return true;
}

// highlight the cells that user find
void highlightCells(Vector<PointT>& cells)
{
    // highlight the cells that form a words
    for (int i = 0; i < cells.size(); i++) {
        PointT point = cells[i];
        highlightCube(point.row, point.col, true);
    }

    // wait a second to show the highlight
    pause(100);

    // set back to the origin
    for (int j  = 0; j < cells.size(); j++) {
        PointT point = cells[j];
        highlightCube(point.row, point.col, false);
    }
}


// computer do exhaustive search to find rest of the words
void computerTurn(Grid<char>& board, Lexicon& englishWords,
        Vector<string>& foundWords)
{
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            string soFar;
            // store the cells that was used in this turn of finding
            Vector<PointT> usedCells;

            // initial point for the first character in the word
            PointT initialPoint;
            initialPoint.row = row;
            initialPoint.col = col;
            usedCells.add(initialPoint);

            // exhaustive algorithm to find the rest of the words
            computerFind(board, soFar + board[row][col], englishWords,
                        foundWords, row, col, usedCells);
        }
    }
}

// recursive exhustive search for word
void computerFind(Grid<char>& board, string soFar,
        Lexicon& englishWords, 
        Vector<string>& foundWords, int row, int col,
        Vector<PointT>& usedCells)
{
    // if didn't contain this prefix, then just return.
    // don't search down
    if (!englishWords.containsPrefix(soFar))
        return;
    // if it containPrefix
    else if (soFar.size() >= MIN_WORD_LENGTH) {
        // if the word is enough long, and
        // it is valid word, and
        // it didn't find before, then add it
        if (englishWords.contains(soFar) && !alreadyGuess(foundWords, soFar)) {
            foundWords.add(soFar);
            //cout << soFar << endl;
            
            // update the graph of computer's score and word
            recordWordForPlayer(soFar, COMPUTER);
        }
    }


    for (int vertical = -1; vertical <= 1; vertical++) {
        for (int horizon = -1; horizon <= 1; horizon++) {
            if (!(vertical == 0 && horizon == 0) && 
                    !outOfBound(board, row + vertical, col + horizon) &&
                    !alreadyUsedCells(usedCells, row + vertical, col + horizon)) {
                // the copy of current find word
                string soFarCopy = soFar;

                // store the current cell
                PointT usedPoint;
                usedPoint.row = row;
                usedPoint.col = col;
                usedCells.add(usedPoint);

                soFar += board[row + vertical][col + horizon];
                computerFind(board, soFar, englishWords,
                            foundWords, row + vertical, 
                            col + horizon, usedCells);
                soFar = soFarCopy;
                usedCells.remove(usedCells.size() - 1);
            }
        }
    }
}

// check if this cell already be used in the same turn of finding the word
bool alreadyUsedCells(Vector<PointT>& usedCells, int row, int col)
{
    for (int i = 0; i < usedCells.size(); ++i)
        if (usedCells[i].row == row && usedCells[i].col == col)
            return true;

    return false;
}

