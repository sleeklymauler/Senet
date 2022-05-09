// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Piece Header

#ifndef PIECE_H
#define PIECE_H

#include "Square.h"

/**
 * This class simulates a pawn on the gameboard
**/
class Piece {
    private:
        bool onBoard; // is piece currently on the board or not
        Square currentSpace; // current Square Piece is on
        string color; // color of piece / which player owns the piece
    public:
        // CONSTRUCTORS

        /**
         * Default constructor, sets onBoard to false
        **/
        Piece();

        /**
         * Parameterized constructor
         * @param currentSpaceIn Square where piece is currently located
         * @param colorIn color of piece
         * @param onBoardIn is piece currently on the board
        **/
        Piece(Square currentSpaceIn, string colorIn, bool onBoardIn);

        // GETTERS

        /**
         * Gets current Square Piece is on
         * @return Square piece is on
        **/
        Square getCurrentSpace() const;

        /**
         * Gets color of piece
         * @return color of Piece
        **/
        string getPieceColor() const;

        /**
         * Determines if piece is on the board or not
         * @return true if piece is on the board, false if it isn't
        **/
        bool isOnBoard() const;

        // SETTERS

        /**
         * Sets current Square of Piece
         * @param newSpace Square the piece will be on
        **/
        void setCurrentSpace(Square newSpace);

        /**
         * Sets color of Piece
         * @param colorIn new color for the piece
        **/
        void setPieceColor(string colorIn);

        /**
         * Moves piece on or off the board
         * @param onBoardIn true if piece is on the board, false if it isn't
        **/
        void setOnBoard(bool onBoardIn);
};

#endif