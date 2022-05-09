// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Square Implementation

#include "Square.h"

Square::Square() {
    occupied = false;
}

Square::Square(bool occupiedIn, string pieceColorIn, bool hasHouseIn, string houseNameIn, int numberIn) {
    occupied = occupiedIn;
    pieceColor = pieceColorIn;
    hasHouse = hasHouseIn;
    houseName = houseNameIn;
    number = numberIn;
}

bool Square::isOccupied() const {
    return occupied;
}

bool Square::isHouse() const {
    return hasHouse;
}

string Square::getPieceColorOfSquare() const {
    return pieceColor;
}

string Square::getHouseName() const {
    return houseName;
}

int Square::getNumber() const {
    return number;
}

string Square::getDefended() const {
    return defended;
}

string Square::getBlockaded() const {
    return blockaded;
}

void Square::setOccupied(bool setOccupiedIn) {
    occupied = setOccupiedIn;
}

void Square::setHouse(bool hasHouseIn) {
    hasHouse = hasHouseIn;
}

void Square::setPieceColorOfSquare(string pieceColorIn) {
    pieceColor = pieceColorIn;
}

void Square::setHouseName(string houseNameIn) {
    houseName = houseNameIn;
}

void Square::setNumber(int numberIn) {
    number = numberIn;
}

void Square::setDefended(string defendedIn) {
    defended = defendedIn;
}

void Square::setBlockaded(string blockadedIn) {
    blockaded = blockadedIn;
}