// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Sticks Header

#ifndef STICKS_H
#define STICKS_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

/** 
 * This class acts as the sticks used to determine the number of spaces to move during a player's turn
**/
class Sticks {

    private:
        int result; // number of spaces player can move after the roll between 0 and 5 inclusive
        vector<bool> stickVect; // stores values of each stick after a toss, black or white
    public:
        // CONSTRUCTORS
        
        /**
         * Default constructor, sets seed of random generator
        **/
        Sticks();

        // GETTERS
        
        /**
         * Returns result after a roll has occurred
         * @return integer value between 0 and 5 inclusive
        **/
        int getResult() const;

        // OTHER FUNCTIONS

        /**
         * Simulates tossing 4 sticks, result is stored for later
        **/
        void rollSticks();

        /**
         * Draws 4 boxes, either black or white, to show the results of a stick toss
        **/
        void drawSticks() const;
};

#endif