// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Player Implementation

#include "Player.h"

Player::Player() {
    
}

Player::Player(string colorIn) {
    color = colorIn;
}

Piece Player::getPawnByIndex(int index) const {
    return pawns[index];
}

Piece Player::getPawnBySquareNumber(int spaceNumber) const {
    bool found = false;
    for (int i = 0; i < NUMPAWNS; i++) {
        if (pawns[i].getCurrentSpace().getNumber() == spaceNumber) {
            found = true;
            return pawns[i];
        }
    }
    cout << "Error in getPawnBySquareNumber(): couldn't find pawn with that space in player's pawns[]" << endl;
    return pawns[0];
}

int Player::getIndexBySquareNumber(int spaceNumber) const {
    for (int i = 0; i < NUMPAWNS; i++) {
        if (pawns[i].getCurrentSpace().getNumber() == spaceNumber) {
            return i;
        }
    }
    cout << "Failed to find pawn in pawns[] with that square number in getIndexBySquareNumber()" << endl;
    return 0;
}

int Player::getNumPawns() const {
    return NUMPAWNS;
}

string Player::getColor() const {
    return color;
}

void Player::setPawn(int index, Square spaceIn) {
    pawns[index] = Piece(spaceIn, spaceIn.getPieceColorOfSquare(), spaceIn.isOccupied());
}

bool Player::detectWin() {
    for (int i = 0; i < NUMPAWNS; i++) {
        if (pawns[i].isOnBoard()) { // if any pawn is still on the board
            return false; // return false
        }
    }
    return true; // otherwise, all pawns are off the board and player has won
}




