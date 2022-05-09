// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Piece Implementation

#include "Piece.h"

Piece::Piece() {
    onBoard = false;
}

Piece::Piece(Square currentSpaceIn, string colorIn, bool onBoardIn) {
    currentSpace = currentSpaceIn;
    color = colorIn;
    onBoard = onBoardIn;
}

Square Piece::getCurrentSpace() const {
    return currentSpace;
}

string Piece::getPieceColor() const {
    return color;
}

bool Piece::isOnBoard() const {
    return onBoard;
}

void Piece::setCurrentSpace(Square newSpace) {
    currentSpace = newSpace;
}

void Piece::setPieceColor(string colorIn) {
    color = colorIn;
}

void Piece::setOnBoard(bool onBoardIn) {
    onBoard = onBoardIn;
}