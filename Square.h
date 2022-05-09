// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Square Header

#ifndef SQUARE_H
#define SQUARE_H

#include <string>

using namespace std;

/**
 * This class simulates individual squares on the gameboard
**/
class Square {
    private:
        bool occupied; // has piece or not
        bool hasHouse; // square is a house or not
        string pieceColor; // color of piece on square
        string houseName; // name of house
        int number; // square number on board
        string defended; // player color that is currently defending the square
        string blockaded; // player color that is currently blockading the square
    
    public:
        // CONSTRUCTORS

        /**
         * Default constructor, sets occupied to false
        **/
        Square();

        /**
         * Parameterized constructor
         * @param occupiedIn true if Square has a pawn on it, false if it doesn't
         * @param pieceColorIn black for black pawn, white for white pawn
         * @param hasHouseIn true if Square is a house, false if it isn't
         * @param houseNameIn name of house if hasHouseIn is true
         * @param numberIn number of Square found under it on the gameboard
        **/
        Square(bool occupiedIn, string pieceColorIn, bool hasHouseIn, string houseNameIn, int numberIn);

        // GETTERS

        /**
         * Determines if square has a piece on it or not
         * @return true if pawn on square, false if there isn't one
        **/
        bool isOccupied() const;

        /**
         * Determines if square is a house
         * @return true if square is a house, false if it isn't
        **/
        bool isHouse() const;

        /**
         * Determines color of piece on square
         * @return black for black pawn, white for white pawn
        **/
        string getPieceColorOfSquare() const;

        /**
         * Determines name of the house on the square
         * @return one of 5 potential house names: see HowToPlay.txt
        **/
        string getHouseName() const;

        /**
         * Determines square number
         * @return number of square, found below the square on the gameboard, 0-29 inclusive
        **/
        int getNumber() const;

        /**
         * @return color of player defending the square, or empty string if square isn't defended
        **/
        string getDefended() const;

        /**
         * @return color of player blockading the square, or empty string if square isn't blockaded
        **/
        string getBlockaded() const;

        // SETTERS

        /**
         * Changes if there is a pawn located on the square or not
         * @param setOccupiedIn true if pawn on square, false if there isn't one
        **/
        void setOccupied(bool setOccupiedIn);

        /**
         * Changes if square has a house on it or not
         * @param hasHouseIn true if square is a house, false if it isn't
        **/
        void setHouse(bool hasHouseIn);

        /**
         * Sets color of pawn on the square
         * @param pieceColorIn black for black pawn, white for white pawn
        **/
        void setPieceColorOfSquare(string pieceColorIn);

        /**
         * Sets name of house on the square if it has one
         * @param houseNameIn one of the 5 potential house names: see rules.txt
        **/
        void setHouseName(string houseNameIn);

        /**
         * Sets number of the square
         * @param numberIn number that you want the square to be
        **/
        void setNumber(int numberIn);

        /**
         * Set status of whether square is defended or not
         * @param defendedIn color of player defending the square
        **/
        void setDefended(string defendedIn);

        /**
         * Set status of whether square is blockaded or not
         * @param blockadedIn color of player blockading the square
        **/
        void setBlockaded(string blockadedIn);
};

#endif