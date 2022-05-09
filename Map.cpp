// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Map Implementation

#include "Map.h"

Map::Map(Player &b1, Player &w1) {
    // setting seed of random generator for house of re-atoum
    srand(time(0));
    // first 14 squares are filled with alternating black and white pieces
    for (int i = 0; i < 14; i++) { 
        string tempColor;
        if (i % 2 == 0) {
            tempColor = "black";
        }
        else {
            tempColor = "white";
        }
        spaces[i] = Square(true, tempColor, false, "", i);
    }
    // initializing pawns[] for each player
    for (int i = 0; i < b1.getNumPawns(); i++) {
        b1.setPawn(i, spaces[2 * i]);
        w1.setPawn(i, spaces[1 + (2 * i)]);
    }
    // setting house of rebirth to be 14th square
    spaces[14] = Square(false, "", true, "house of rebirth", 14);
    // setting squares 15 - 24 to be empty
    for (int i = 15; i < 25; i++) { 
        spaces[i] = Square(false, "", false, "", i);
    }
    // square 25 is house of happiness
    spaces[25] = Square(false, "", true, "house of happiness", 25);
    // square 26 is house of water
    spaces[26] = Square(false, "", true, "house of water", 26);
    // square 27 is house of three truths
    spaces[27] = Square(false, "", true, "house of three truths", 27);
    // square 28 is house of re-atoum
    spaces[28] = Square(false, "", true, "house of re-atoum", 28);
    // last square is regular square
    spaces[29] = Square(false, "", false, "", 29);
    // creating an "off board" square for pawns that have moved off the gameboard
    offBoard = Square(false, "", "", "", -1);
    // update defense conditions
    detectDefense();
    // update blockade conditions
    detectBlockade();
}

Square Map::getSpace(int spaceNumber) const {
    return spaces[spaceNumber];
}

void Map::printMap() { 
    for (int row = 0; row < numRows; row++) {
        // print upper line
        cout << endl;
        cout << "__________________________________________________" << endl;
        // printing top half of each square
        if (row == 1) { // middle row goes right to left instead of left to right
            for (int col = numCol - 1; col >= 0; col--) {
                printHalfSquare(spaces[(row * 10) + col]); // accesses every Square in spaces[] using row and col
            }
        }
        else {
            for (int col = 0; col < numCol; col++) {
                printHalfSquare(spaces[(row * 10) + col]); // accesses every Square in spaces[] using row and col
            }
        }
        cout << endl; // moving to next line
        // printing lower half of each square
        if (row == 1) { // middle row goes right to left instead of left to right
            for (int col = numCol - 1; col >= 0; col--) {
                printHalfSquare(spaces[(row * 10) + col]); // accesses every Square in spaces[] using row and col
            }
        }
        else {
            for (int col = 0; col < numCol; col++) {
                printHalfSquare(spaces[(row * 10) + col]); // accesses every Square in spaces[] using row and col
            }
        }
        cout << endl; // move to next line
        // printing lower line
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
        // printing out numbers below squares
        if (row == 0) {
            cout << "  0    1    2    3    4    5    6    7    8    9";
        }
        else if (row == 1) {
            cout << "  19   18   17   16   15   14   13   12   11   10";
        }
        else if (row == 2) {
            cout << "  20   21   22   23   24   25   26   27   28   29";
        }
        cout << endl;
    }
}

void Map::printHalfSquare(Square space) {
    cout << "|";
    if (!space.isHouse()) { 
        if (!space.isOccupied()) {
            cout << "    "; // space doesn't have a house and has no pieces on it
        }
        else if (space.isOccupied()) {
            if (space.getPieceColorOfSquare() == "white") { // space doesn't have a house but has white piece
                cout << "▮ ▮ ";
            }
            else if (space.getPieceColorOfSquare() == "black") {
                cout << "▯ ▯ "; // space doesn't have a house but has black piece
            }
            else {
                cout << "ERROR PRINTING PIECE COLOR"; // just in case
            }
        }
    }
    else if (space.isHouse()) {
        if (!space.isOccupied()) {
            if (space.getHouseName() == "house of rebirth") {
                cout << "☥☥☥☥"; // house of rebirth with no piece
            }
            else if (space.getHouseName() == "house of happiness") {
                cout << "𓄿 𓄿 "; // house of happiness with no piece
            }
            else if (space.getHouseName() == "house of water") {
                cout << "𓈗 𓈗 "; // house of water with no piece
            }
            else if (space.getHouseName() == "house of three truths") {
                cout << "𓃋𓃋𓃋𓃋"; // house of three truths with no piece
            }
            else if (space.getHouseName() == "house of re-atoum") {
                cout << "𓂀 𓂀 "; // house of re-atoum with no piece
            }
            else {
                cout << "ERROR PRINTING HOUSE"; // just in case
            }
        }
        else if (space.isOccupied() && space.getPieceColorOfSquare() == "white") {
            if (space.getHouseName() == "house of rebirth") {
                cout << "☥▮ ☥"; // house of rebirth with white piece
            }
            else if (space.getHouseName() == "house of happiness") {
                cout << "𓄿▮ 𓄿"; // house of happiness with white piece
            }
            else if (space.getHouseName() == "house of water") {
                cout << "𓈗▮ 𓈗"; // house of water with white piece
            }
            else if (space.getHouseName() == "house of three truths") {
                cout << "𓃋▮ 𓃋"; // house of three truths with white piece
            }
            else if (space.getHouseName() == "house of re-atoum") {
                cout << "𓂀▮ 𓂀"; // house of re-atoum with white piece
            }
            else {
                cout << "ERROR PRINTING PIECE AND HOUSE"; // just in case
            }
        }
        else if (space.isOccupied() && space.getPieceColorOfSquare() == "black") {
            if (space.getHouseName() == "house of rebirth") {
                cout << "☥▯ ☥"; // house of rebirth with black piece
            }
            else if (space.getHouseName() == "house of happiness") {
                cout << "𓄿▯ 𓄿"; // house of happiness with black piece
            }
            else if (space.getHouseName() == "house of water") {
                cout << "𓈗▯ 𓈗"; // house of water with black piece
            }
            else if (space.getHouseName() == "house of three truths") {
                cout << "𓃋▯ 𓃋"; // house of three truths with black piece
            }
            else if (space.getHouseName() == "house of re-atoum") {
                cout << "𓂀▯ 𓂀"; // house of re-atoum with black piece
            }
            else {
                cout << "ERROR PRINTING PIECE AND HOUSE"; // just in case
            }
        }
    }
}

int Map::movePiece(int spaceNumber, int forward, Player &pieceMover, Player &otherPlayer) {  
    // Checks to make sure the move itself is valid
    // making sure there is actually a pawn on the square to move
    if (spaces[spaceNumber].getPieceColorOfSquare() != pieceMover.getColor()) {
        // cout << "ERROR: NO " << pieceMover.getColor() << " PAWN AT SQUARE " << spaceNumber << " TO MOVE" << endl;
        return -1;
    }    
    // handling house of re-atoum probablity
    if (spaceNumber == 28) {
        double percentage = forward * 10;
        double r = ((double)rand() / RAND_MAX) * 100;
        cout << "You rolled: " << forward << " so you have a " << percentage << "% chance of moving out of the house of re-atoum" << endl;
        if (r < percentage) {
            spaces[spaceNumber].setOccupied(false); // old square now doesn't have a piece on it
            spaces[spaceNumber].setPieceColorOfSquare(""); // old square now doesn't have a color on it
            pieceMover.getPawnBySquareNumber(spaceNumber).setOnBoard(false); // setting onBoard status to false for Piece in pawns[]
            pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), offBoard); // setting square of Piece to special offBoard square
            cout << "The random value was " << r << " so you have successfully moved your pawn out of the house of re-atoum and off the board" << endl;
            // update defense conditions
            detectDefense();
            // update blockade conditions
            detectBlockade();
            return 0; 
        }
        else {
            cout << "The random value was " << r << " so you did not move out of the house of re-atoum" << endl;
            return 0;
        }
    }
    // checking to make sure piece only leaves house of 3 truths with a roll of 3
    if (spaceNumber == 27 && forward != 3) {
        // cout << "ERROR: ONLY WAY TO EXIT THE HOUSE OF THREE TRUTHS IS TO ROLL A THREE" << endl;
        return -2;
    }
    // checking to make sure piece stops at house of happiness first
    if (spaceNumber < 25 && spaceNumber + forward > 25) {
        // cout << "ERROR: PIECE MUST LAND ON HOUSE OF HAPPINESS EXACTLY BEFORE CONTINUING FORWARD ON THE BOARD" << endl;
        return -7;
    }
    // if pawn can be moved off the board
    if (spaceNumber + forward > 29) {
        spaces[spaceNumber].setOccupied(false); // old square now doesn't have a piece on it
        spaces[spaceNumber].setPieceColorOfSquare(""); // old square now doesn't have a color on it
        pieceMover.getPawnBySquareNumber(spaceNumber).setOnBoard(false); // setting onBoard status to false for Piece in pawns[]
        pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), offBoard); // setting square of Piece to special offBoard square
        // cout << "PAWN MOVED OFF OF BOARD" << endl;
        // update defense conditions
        detectDefense();
        // update blockade conditions
        detectBlockade();
        return 1; // is this the right return number?
    }
    // making sure not trying to move to a square that already has one of your pieces on it
    if (spaces[spaceNumber + forward].isOccupied() && spaces[spaceNumber + forward].getPieceColorOfSquare() == spaces[spaceNumber].getPieceColorOfSquare()) {
        // cout << "ERROR: CAN'T MOVE PIECE TO SQUARE THAT IS ALREADY OCCUPIED BY SAME COLOR" << endl;
        return -3;
    }
    // making sure not moving to house of rebirth if it has an enemy piece on it
    if (spaces[spaceNumber + forward].isOccupied() && spaces[spaceNumber + forward].getHouseName() == "house of rebirth") {
        // cout << "ERROR: CAN'T MOVE PIECE TO HOUSE OF REBIRTH IF ENEMY PIECE OCCUPIES IT" << endl;
        return -4;
    }
    // checking for blockades
    for (int i = spaceNumber + 1; i <= spaceNumber + forward; i++) {
        if (spaces[i].getBlockaded() != "" && spaces[i].getBlockaded() != spaces[spaceNumber].getPieceColorOfSquare()) {
            // cout << "ERROR: CAN'T MOVE TO SQUARE " << spaceNumber + forward << " AS THERE IS A BLOCKADE BY " << spaces[i].getBlockaded() << endl;
            return -5;
        }
    }
    // checking if new square is defended
    if (spaces[spaceNumber + forward].getDefended() != "" && spaces[spaceNumber + forward].getDefended() != spaces[spaceNumber].getPieceColorOfSquare()) {
        // cout << "ERROR: CAN'T MOVE TO SQUARE " << spaceNumber + forward << " AS IT IS DEFENDED BY " << spaces[spaceNumber + forward].getDefended() << endl;
        return -6;
    }
    // Once we get here, the move is valid and we can actually move the piece
    if (!spaces[spaceNumber + forward].isOccupied()) { // if square to move to is empty
        if (spaces[spaceNumber + forward].getHouseName() == "house of water") { // if piece lands on house of water
            if (!spaces[14].isOccupied()) { // if house of rebirth is empty
                spaces[14].setOccupied(true); // house of rebirth is now occupied
                spaces[14].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // house of rebirth gets color of old square
                spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[14]); // set pawn at old square to now have house of rebirth
                cout << "Your piece landed on the house of water, and so has been sent to the house of rebirth" << endl;
            }
            else { // house of rebirth is already occupied
                bool foundEmpty = false;
                int iter = 13;
                while (!foundEmpty && iter >= 0) { // iterate through all squares before it to find an empty one
                    if (!spaces[iter].isOccupied()) {
                        spaces[iter].setOccupied(true); // new square is now occupied
                        spaces[iter].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
                        spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                        spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                        pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[iter]); // set pawn at old square to now have new square
                        cout << "Your piece landed on the house of water, but since the house of rebirth is already occupied, it was moved to the closest square behind it." << endl;
                        foundEmpty = true;
                    }
                    iter--;
                }
                if (!foundEmpty) { // if every square before house of rebirth is occupied
                    int jter = 14;
                    while (!foundEmpty && iter < 26)  { // iterate through every square after it
                        if (!spaces[jter].isOccupied()) {
                            spaces[jter].setOccupied(true); // new square is now occupied
                            spaces[jter].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
                            spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                            spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                            pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[jter]); // set pawn at old square to now have new square
                            cout << "Your piece landed on the house of water, but since the house of rebirth is already occupied, it has been sent to the closest square ahead." << endl;
                            foundEmpty = true;
                        }
                        jter++;
                    }
                }
                if (!foundEmpty) { // if there STILL isn't an empty square, just leave piece on house of water
                    cout << "Your piece landed on the house of water, but a suitable spot to move it to couldn't be found so it will remain there." << endl;
                }
            }
        }
        else { // piece isn't moving to house of water
            spaces[spaceNumber + forward].setOccupied(true); // square to move to is now occupied
            spaces[spaceNumber + forward].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
            spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
            spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
            pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[spaceNumber + forward]); // set pawn at old square to now have new square
        }
    }
    else if (spaces[spaceNumber + forward].isOccupied()) { // if square to move to has enemy piece
        spaces[spaceNumber + forward].setOccupied(true); // new square has a piece on it
        string tempColor = spaces[spaceNumber + forward].getPieceColorOfSquare(); // store color of what piece used to be on new square
        spaces[spaceNumber + forward].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
        spaces[spaceNumber].setPieceColorOfSquare(tempColor); // old square gets color of new square
        pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[spaceNumber + forward]); // pawns swap each others' squares
        otherPlayer.setPawn(otherPlayer.getIndexBySquareNumber(spaceNumber + forward), spaces[spaceNumber]);
    }
    // update defense conditions
    detectDefense();
    // update blockade conditions
    detectBlockade();
    return 0;
}

bool Map::moveExists(Player mover, int roll) {
    vector<bool> blockades;
    vector<bool> defenses;
    vector<bool> friendlyFire;
    vector<bool> happiness;
    vector<bool> rebirth;
    bool houseHappy = false;
    bool house3 = false;
    bool houseRe = false;
    bool space29 = false;
    for (int i = 0; i < 26; i++) { // looking at first 25 squares
        if (spaces[i].getPieceColorOfSquare() == mover.getColor()) { // if mover has a piece on a particular square
            bool foundBlockade = false;
            bool foundDefense = false;
            bool foundFriendly = false;
            bool foundHappy = false;
            bool foundRebirth = false;
            for (int j = i + 1; j <= i + roll; j++) { // looking at all squares between square with mover piece and square to move to with roll
                if (spaces[j].getBlockaded() != "" && spaces[j].getBlockaded() != mover.getColor()) { // if any of these squares has the blockaded condition
                    foundBlockade = true;
                }
            }
            blockades.push_back(foundBlockade);
            if (spaces[i + roll].getDefended() != "" && spaces[i + roll].getDefended() != mover.getColor()) { // if square to move to is defended by enemy piece
                foundDefense = true;
            }
            defenses.push_back(foundDefense);
            if (spaces[i + roll].getPieceColorOfSquare() == mover.getColor()) {
                foundFriendly = true;
            }
            friendlyFire.push_back(foundFriendly);
            if (i + roll > 25 && i != 25) {
                foundHappy = true;
            }
            happiness.push_back(foundHappy);
            if (spaces[i + roll].getHouseName() == "house of rebirth" && spaces[i + roll].isOccupied() && spaces[i + roll].getPieceColorOfSquare() != mover.getColor()) {
                foundRebirth = true;
            }
            rebirth.push_back(foundRebirth);
        }
    }
    for (int k = 0; k < blockades.size(); k++) {
        if (defenses.at(k) == false && blockades.at(k) == false && friendlyFire.at(k) == false && happiness.at(k) == false && rebirth.at(k) == false) {
            // cout << "Move is possible for " << mover.getColor() << " with a roll of " << roll << endl;
            return true;
        }
    }
    if (spaces[27].getPieceColorOfSquare() == mover.getColor() && roll == 3) { // if they rolled a 3 with a piece on house of three truths
        // cout << "Move is possible for " << mover.getColor() << " with a roll of " << roll << endl;
        return true;
    }
    if (spaces[28].getPieceColorOfSquare() == mover.getColor()) { // if they have a piece on house of re-atoum
        // cout << "Move is possible for " << mover.getColor() << " with a roll of " << roll << endl;
        return true;
    }
    if (spaces[29].getPieceColorOfSquare() == mover.getColor()) { // if they have a piece on square 29
        // cout << "Move is possible for " << mover.getColor() << " with a roll of " << roll << endl;
        return true;
    }
    return false; // if all else fails, then the player has no possible moves to make
}

bool Map::backMoveExists(Player mover) {
    for (int i = 29; i >= 0; i--) { // iterate through every square on the board
        if (spaces[i].getPieceColorOfSquare() == mover.getColor()) { // finding square closest to end that has mover pawn
            for (int j = i - 1; j >= 0; j--) { // iterate through all squares before square with mover pawn
                if (!spaces[j].isOccupied()) { // if an empty space exists
                    return true;
                }
            }
        }
    }
    return false;
}

int Map::moveBackwards(int spaceNumber, Player &pieceMover, Player &other) {
    if (spaces[spaceNumber].getPieceColorOfSquare() != pieceMover.getColor()) {
        return -1;
    }
    for (int i = spaceNumber - 1; i >= 0; i--) {
        if (!spaces[i].isOccupied()) { 
            if (spaces[i].getHouseName() == "house of water") { // if piece moves backwards onto house of water
                // following is copied from movePiece() house of water check
                if (!spaces[14].isOccupied()) { // if house of rebirth is empty
                    spaces[14].setOccupied(true); // house of rebirth is now occupied
                    spaces[14].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // house of rebirth gets color of old square
                    spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                    spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                    pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[14]); // set pawn at old square to now have house of rebirth
                    cout << "Your piece landed on the house of water, and so has been sent to the house of rebirth" << endl;
                    return 0;
                }
                else { // house of rebirth is already occupied
                    bool foundEmpty = false;
                    int iter = 13;
                    while (!foundEmpty && iter >= 0) { // iterate through all squares before it to find an empty one
                        if (!spaces[iter].isOccupied()) {
                            spaces[iter].setOccupied(true); // new square is now occupied
                            spaces[iter].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
                            spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                            spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                            pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[iter]); // set pawn at old square to now have new square
                            cout << "Your piece landed on the house of water, but since the house of rebirth is already occupied, it was moved to the closest square behind it." << endl;
                            foundEmpty = true;
                            return 0;
                        }
                        iter--;
                    }
                    if (!foundEmpty) { // if every square before house of rebirth is occupied
                        int jter = 14;
                        while (!foundEmpty && iter < 26)  { // iterate through every square after it
                            if (!spaces[jter].isOccupied()) {
                                spaces[jter].setOccupied(true); // new square is now occupied
                                spaces[jter].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
                                spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                                spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                                pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[jter]); // set pawn at old square to now have new square
                                cout << "Your piece landed on the house of water, but since the house of rebirth is already occupied, it has been sent to the closest square ahead." << endl;
                                foundEmpty = true;
                                return 0;
                            }
                            jter++;
                        }
                    }
                    if (!foundEmpty) { // if there STILL isn't an empty square, just leave piece on house of water
                        cout << "Your piece landed on the house of water, but a suitable spot to move it to couldn't be found so it will remain there." << endl;
                        return 0;
                    }
                }
            }
            else { // if piece doesn't move backwards onto house of water
                spaces[i].setOccupied(true); // square to move to is now occupied
                spaces[i].setPieceColorOfSquare(spaces[spaceNumber].getPieceColorOfSquare()); // new square gets color of old square
                spaces[spaceNumber].setPieceColorOfSquare(""); // old square no longer has a piece color
                spaces[spaceNumber].setOccupied(false); // old square no longer has a piece on it
                pieceMover.setPawn(pieceMover.getIndexBySquareNumber(spaceNumber), spaces[i]); // set pawn at old square to now have new square
                // update defense conditions
                detectDefense();
                // update blockade conditions
                detectBlockade();
                return 0;
            }
        }
    }
    return -2;
}

void Map::detectDefense() {
    // remove all previous defense conditions
    for (int i = 0; i < 30; i++) {
        spaces[i].setDefended("");
    }
    
    for (int i = 1; i < 29; i++) {
        // if square before or after spaces[i] has the same color piece as spaces[i]
        // only going through spaces 1 - 28 to avoid indexing out of bounds
        if ((spaces[i - 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) || (spaces[i].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare())) {
            spaces[i].setDefended(spaces[i].getPieceColorOfSquare());
        }
    }
    // handling square 0
    if (spaces[0].getPieceColorOfSquare() == spaces[1].getPieceColorOfSquare()) {
        spaces[0].setDefended(spaces[0].getPieceColorOfSquare());
    }
    // handling square 29
    if (spaces[29].getPieceColorOfSquare() == spaces[28].getPieceColorOfSquare()) {
        spaces[29].setDefended(spaces[29].getPieceColorOfSquare());
    }
}

void Map::detectBlockade() { 
    // remove all previous blockade conditions
    for (int i = 0; i < 30; i++) {
        spaces[i].setBlockaded("");
    }    
    // blockade checking goes from right to left
    // handling squares 2 - 7
    for (int i = 7; i >= 2; i--) {
        // checking to see if two squares to left of current square have the same piece
        if (spaces[i - 2].getPieceColorOfSquare() == spaces[i - 1].getPieceColorOfSquare() && spaces[i - 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) {
            for (int j = i; j >= i - 2; j--) { // all squares up to end of blockade get blockaded status by color of spaces[i]
                spaces[j].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
        // checking to see if two squares to right of current square have the same piece
        if (spaces[i + 2].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare() && spaces[i + 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) {
            for (int k = i + 2; k >= i; k--) {
                spaces[k].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
        // checking to see if squares on each side of current square have the same piece
        if (spaces[i].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare() && spaces[i].getPieceColorOfSquare() == spaces[i - 1].getPieceColorOfSquare()) {
            for (int l = i + 1; l >= i - 1; l--) {
                spaces[l].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
    }
    // handling squares 12 - 17
    for (int i = 17; i >= 12; i--) {
        // checking to see if two squares to right of current square have the same piece
        if (spaces[i - 2].getPieceColorOfSquare() == spaces[i - 1].getPieceColorOfSquare() && spaces[i - 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) {
            for (int j = i; j >= i - 2; j--) { // all squares up to end of blockade get blockaded status by color of spaces[i]
                spaces[j].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
        // checking to see if two squares to left of current square have the same piece
        if (spaces[i + 2].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare() && spaces[i + 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) {
            for (int k = i + 2; k >= i; k--) {
                spaces[k].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
        // checking to see if squares on each side of current square have the same piece
        if (spaces[i].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare() && spaces[i].getPieceColorOfSquare() == spaces[i - 1].getPieceColorOfSquare()) {
            for (int l = i + 1; l >= i - 1; l--) {
                spaces[l].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
    }
    // handling squares 22 - 27
    for (int i = 27; i >= 22; i--) {
        // checking to see if two squares to left of current square have the same piece
        if (spaces[i - 2].getPieceColorOfSquare() == spaces[i - 1].getPieceColorOfSquare() && spaces[i - 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) {
            for (int j = i; j >= i - 2; j--) { // all squares up to end of blockade get blockaded status by color of spaces[i]
                spaces[j].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
        // checking to see if two squares to right of current square have the same piece
        if (spaces[i + 2].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare() && spaces[i + 1].getPieceColorOfSquare() == spaces[i].getPieceColorOfSquare()) {
            for (int k = i + 2; k >= i; k--) {
                spaces[k].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
        // checking to see if squares on each side of current square have the same piece
        if (spaces[i].getPieceColorOfSquare() == spaces[i + 1].getPieceColorOfSquare() && spaces[i].getPieceColorOfSquare() == spaces[i - 1].getPieceColorOfSquare()) {
            for (int l = i + 1; l >= i - 1; l--) {
                spaces[l].setBlockaded(spaces[i].getPieceColorOfSquare());
            }
        }
    }
}

void Map::printStats() {
    vector<int> blackDefenses;
    vector<int> blackBlockades;
    vector<int> whiteDefenses;
    vector<int> whiteBlockades;
    for (int i = 0; i < 30; i++) {
        if (spaces[i].getDefended() == "black") {
            blackDefenses.push_back(i);
        }
        if (spaces[i].getBlockaded() == "black") {
            blackBlockades.push_back(i);
        }
        if (spaces[i].getDefended() == "white") {
            whiteDefenses.push_back(i);
        }
        if (spaces[i].getBlockaded() == "white") {
            whiteBlockades.push_back(i);
        }
    }
    if (blackDefenses.size() != 0) {
        cout << "Black is defending spaces ";
        for (int i = 0; i < blackDefenses.size(); i++) {
            cout << blackDefenses.at(i) << ", ";
        }
    }
    else {
        cout << "Black isn't defending any spaces.";
    }
    cout << endl;
    if (blackBlockades.size() != 0) {
        cout << "Black is blockading spaces ";
        for (int i = 0; i < blackBlockades.size(); i++) {
            cout << blackBlockades.at(i) << ", ";
        }
    }
    else {
        cout << "Black isn't blockading any spaces.";
    }
    cout << "\n" << endl;
    if (whiteDefenses.size() != 0) {
        cout << "White is defending spaces ";
        for (int i = 0; i < whiteDefenses.size(); i++) {
            cout << whiteDefenses.at(i) << ", ";
        }
    }
    else {
        cout << "White isn't defending any spaces.";
    }
    cout << endl;
    if (whiteBlockades.size() != 0) {
        cout << "White is blockading spaces ";
        for (int i = 0; i < whiteBlockades.size(); i++) {
            cout << whiteBlockades.at(i) << ", ";
        }
    }
    else {
        cout << "White isn't blockading any spaces.";
    }
    cout << "\n" << endl;
}