// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Driver

#include "Map.h"
#include "Square.h"
#include "Piece.h"
#include "Player.h"
#include "Sticks.h"

using namespace std;

int main() {
    int firstInput = -1;
    while (firstInput != 4) {
        cout << "Senet Menu\n1) Start game\n2) About the game\n3) How to play\n4) Quit" << endl;
        cin >> firstInput;
        if (cin.fail() || firstInput <= 0 || firstInput > 6) { // checking for valid input
            cin.clear(); 
            cin.ignore(); // fixing cin after users broke it :(
            cout << "Please enter a number between 1 and 6!" << endl;
        }
        else if (firstInput == 1) { // time to start playing
            int turnNumber = 0; 
            Player currentPlayer; // so I don't have to write two of everything
            Player otherPlayer;
            Player p1 = Player("white"); // initializing players
            Player p2 = Player("black");
            Sticks dice = Sticks(); // initalizing dice
            Map gameboard = Map(p2, p1); // initializing gameboard
            while (!p1.detectWin() && !p2.detectWin()) { // while neither player has won yet
                if (turnNumber % 2 == 0) { // even turn numbers are white's turn
                    currentPlayer = p1;
                    otherPlayer = p2;
                }
                else { // odd numbers are black's turn
                    currentPlayer = p2;
                    otherPlayer = p1;
                }
                gameboard.printMap();
                gameboard.printStats();
                cout << "It is " << currentPlayer.getColor() << "'s turn!" << endl;
                string t;
                do { // keep repeating until user enters 't'
                    cin.clear(); 
                    cin.ignore();
                    cout << "Enter the character 't' to toss sticks" << endl;
                    cin >> t;
                }
                while (t != "t");
                dice.rollSticks();
                int roll = dice.getResult();
                dice.drawSticks();
                cout << "You got a " << roll << "!" << "\n" << endl;
                if (gameboard.moveExists(currentPlayer, roll)) { // if player can make a move
                    int status;
                    do { // loop for valid inputs that are against game rules, handled by movePiece() return values
                        int secondInput;
                        do { // loop for invalid inputs (that could cause seg faults, etc)
                            cin.clear();
                            cin.ignore();
                            cout << "Pick which " << currentPlayer.getColor() << " piece to move by entering the the number of its square between 0 and 29. Enter 30 to view key." << endl;
                            cin >> secondInput;
                            if (secondInput == 30) { // printing a key for players if they need it
                                cout << "Key:\n     ▮ ▮          ▯ ▯          ☥☥☥☥              𓄿𓄿𓄿" << endl;
                                cout << "     ▮ ▮          ▯ ▯          ☥☥☥☥              𓄿𓄿𓄿" << endl;
                                cout << "  white pawn   black pawn   house of life   house of happiness" << endl;
                                cout << "                             (space 14)        (space 25)\n" << endl;
                                cout << "     𓈗𓈗𓈗               𓃋𓃋𓃋𓃋𓃋                  𓂀𓂀𓂀 " << endl;
                                cout << "     𓈗𓈗𓈗               𓃋𓃋𓃋𓃋𓃋                  𓂀𓂀𓂀 " << endl;
                                cout << " house of water  house of three truths   house of re-atoum" << endl;
                                cout << "  (space 26)         (space 27)             (space 28)\n" << endl;
                                cout << "    ☥▯ ☥                    𓂀▮ 𓂀" << endl;
                                cout << "    ☥▯ ☥                    𓂀▮ 𓂀" << endl;
                                cout << "black pawn on house   white pawn on house\n" << endl;
                                cout << "House of rebirth: pawns are protected from swapping." << endl;
                                cout << "House of happiness: all pawns must pass through this square." << endl;
                                cout << "House of water: pawns that land here are sent back to the house of rebirth." << endl;
                                cout << "House of three truths: must roll a 3 in order to leave this space." << endl;
                                cout << "House of re-atoum: houses leave this space based on a probability determined by their roll.\n" << endl;
                            }
                        }
                        while (secondInput < 0 || secondInput > 29 || cin.fail());
                        status = gameboard.movePiece(secondInput, roll, currentPlayer, otherPlayer);
                        // if/elses for making moves against game rules
                        if (status == -1) { 
                            cout << "Please enter a square that has a " << currentPlayer.getColor() << " pawn on it!" << endl;
                        }
                        else if (status == -2) {
                            cout << "You can't move a piece out of the house of three truths (square 27) unless you roll a 3." << endl;
                        }
                        else if (status == -3) {
                            cout << "You can't move a " << currentPlayer.getColor() << " piece to a square that already has a " << currentPlayer.getColor() << " pawn on it." << endl;
                        }
                        else if (status == -4) {
                            cout << "The house of rebirth (square 14) has a " << otherPlayer.getColor() << " pawn on it, so a " << currentPlayer.getColor() << " pawn can't move to it" << endl;
                        }
                        else if (status == -5) {
                            cout << "Can't move " << currentPlayer.getColor() << " pawn to that square as there is a blockade by " << otherPlayer.getColor() << endl;
                        }
                        else if (status == -6) {
                            cout << "Can't move " << currentPlayer.getColor() << " pawn to that square as it is defended by " << otherPlayer.getColor() << endl;
                        }
                        else if (status == -7) {
                            cout << "Your piece must land exactly on the house of happiness (square 25) before it can continue any further" << endl;
                        }
                        else if (status == 1) {
                            cout << "Congrats! You successfully got a pawn off the board" << endl;
                        }
                    }
                    while (status != 0 && status != 1);   
                }
                else { // no valid move exists for the player
                    cout << "No move exists for " << currentPlayer.getColor() << " with a roll of " << roll << endl;
                    if (gameboard.backMoveExists(currentPlayer)) { // if there exists a piece that can be moved backwards
                        int status;
                        do { // loop for valid inputs that are against game rules, handled by moveBackwards() return values
                            int backInput;
                            do { // loop for invalid inputs that could crash the program
                                cin.clear();
                                cin.ignore();
                                cout << "Choose a pawn to move backwards to the nearest empty space." << endl;
                                cin >> backInput;
                            }
                            while (backInput < 0 || backInput > 29 || cin.fail());
                            status = gameboard.moveBackwards(backInput, currentPlayer, otherPlayer);
                            if (status == -1) {
                                cout << "Please enter a square that has a " << currentPlayer.getColor() << " pawn on it!" << endl;
                            }
                            else if (status == -2) {
                                cout << "That piece can't move backwards, choose a different one" << endl;
                            }
                        }
                        while (status != 0);
                    }
                    else { // no pieces can be moved backwards OR forwards
                        cout << "Since none of " << currentPlayer.getColor() << "'s pawns can move backwards, their turn is skipped." << endl;
                    }
                }
                if (turnNumber % 2 == 0) { // since datamembers of currentPlayer and otherPlayer have been updated by movePiece(), need to update p1 and p2 as well
                    p1 = currentPlayer;
                    p2 = otherPlayer;
                }
                else {
                    p2 = currentPlayer;
                    p1 = otherPlayer;
                }
                turnNumber++;
            }
            // after a player has won
            gameboard.printMap();
            cout << currentPlayer.getColor() << " has won! Congratulations!" << endl;
        }
        else if (firstInput == 2) { // learning about the history of the game
            ifstream inFile;
            inFile.open("AboutSenet.txt");
            if (inFile.fail()) { // in case the file doesn't exist
                cout << "Couldn't find file! Is it in the correct directory?" << endl;
            }
            else {
                string line;
                cout << "Opening \"AboutSenet.txt\"\n" << endl;
                while (getline(inFile, line)) { // read every line from the file
                    cout << line << endl;
                }
                inFile.close();
            } 
        }
        else if (firstInput == 3) { // learning how to play
            ifstream inFile;
            inFile.open("HowToPlay.txt");
            if (inFile.fail()) { // in case file doesn't exist
                cout << "Couldn't fin file! Is it in the correct directory?" << endl;
            }
            else {
                string line;
                cout << "Opening \"HowToPlay.txt\"\n" << endl;
                while (getline(inFile, line)) { // read every line from file
                    cout << line << endl;
                }
                inFile.close();
            } 
        }
        else if (firstInput == 4) { // exiting the program
            cout << "Thanks for playing!" << endl;
        }
    }
    return 0;
}