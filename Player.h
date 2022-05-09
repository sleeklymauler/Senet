// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Player Header

#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"
#include <iostream>

using namespace std;

/**
 * This class simulates a Player with a set of Pieces
**/
class Player {
    private:
        static const int NUMPAWNS = 7;
        Piece pawns[NUMPAWNS]; // array containing the player's pieces
        string color; // black or white
    
    public:
        // CONSTRUCTORS

        /**
         * Default constructor
        **/
       Player();

        /**
         * Parameterized constructor
         * @param colorIn color you want to set the player to, black or white
        **/
        Player(string colorIn);

        // GETTERS

        /**
         * Fetches Piece from pawns[] by index
         * @param index index between 0 and 7
         * @return Piece found at pawns[index]
        **/
        Piece getPawnByIndex(int index) const;

        /**
         * Fetches Piece from pawns[] by the square number the piece is on
         * @param spaceNumber number of Square containing Piece
         * @return Piece from that square
        **/
        Piece getPawnBySquareNumber(int spaceNumber) const;

        /**
         * gets index of Piece in pawns[] by the square number it is currently on
         * @param spaceNumber square number of pawn
         * @return index
        **/
        int getIndexBySquareNumber(int spaceNumber) const;

        /**
         * @return number of pawns player has
        **/
        int getNumPawns() const;

        /**
         * @return color of the player
        **/
        string getColor() const;

        // SETTERS

        /**
         * Stores a piece at index in pawns[] based on information found in Square
         * @param index index between 0 and 7
         * @param spaceIn Square that contains the pawn you want to set
        **/
        void setPawn(int index, Square spaceIn);

        // OTHER FUNCTIONS

        /**
         * @return true if all the Player's piece are off the board, false if not
        **/
        bool detectWin();




};

#endif