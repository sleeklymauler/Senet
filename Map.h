// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Map Header

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "Square.h"
#include "Piece.h"
#include "Player.h"

using namespace std;

class Map {
    private:
        static const int numRows = 3; // number of rows gameboard has
        static const int numCol = 10; // number of columns gameboard has
        Square spaces[30]; // array that has all 30 Square spaces
        Square offBoard;

    public:
        // Constructors
        
        /**
         * Parameterized constructor, fills spaces[] with Squares according to starting setup of the game and fills Players' pawns[] array with Pieces with corresponding Square
         * Reference variables used so that constructor can fill the Piece arrays of the Players
         * @param &b1 player with black pawns
         * @param &w1 player with white pawns
        **/
        Map(Player &b1, Player &w1);

        // GETTERS

        /**
         * Gets square based off of its number
         * @param spaceNumber number found under the Square on the gameboard
         * @return Square with that space number
        **/
        Square getSpace(int spaceNumber) const;

        // Other functions

        /**
         * Prints the map using attributes of each Square in spaces[], requires helper function printHalfSquare()
        **/
        void printMap();

        /**
         * Prints the top/bottom half of an individual space on the gameboard
         * @param space Square that you want to print
        **/
        void printHalfSquare(Square space);

        /**
         * Moves a piece on the board, and will swap pieces if conditions are met, doesn't check for any house conditions (yet)
         * @param spaceNumber square number with pawn you want to move
         * @param forward number of spaces forward you want the pawn to move
         * @return 0 if successful, negative integers if invalid move has been made
         * 
        **/
        int movePiece(int spaceNumber, int forward, Player &pieceMover, Player &other);

        /**
         * Moves a piece backwards to the nearest empty square
         * @param spaceNumber space that contains the piece to move
         * @param &pieceMover player that is moving the piece
         * @param &other other player
         * @return 0 if successful, -1 if invalid move has been made
        **/
        int moveBackwards(int spaceNumber, Player &pieceMover, Player &other);

        /**
         * Determines if a player can move any one of their pieces forward with what they just rolled
         * @param mover Player who's turn it is
         * @param roll number the player rolled
         * @return true if a piece can be moved forward by roll, false if every piece can't
        **/
        bool moveExists(Player mover, int roll);

        /**
         * Determines if a player can move any one of their pieces backwards to some empty space behind them
         * @param mover Player who's turn it is
         * @return true if a backwards move exits, false if one doesn't
        **/
        bool backMoveExists(Player mover);

        /**
         * Checks if pieces are adjacent to each other and updates those squares so that they have the defended condition
        **/
        void detectDefense();

        /**
         * Checks if pieces line up 3 or more and updates those squares with the blockaded condition
        **/
        void detectBlockade();

        /**
         * Prints what spaces are being defended by black and white respectively
        **/
        void printStats();
};





#endif