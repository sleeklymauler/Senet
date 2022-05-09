// CSCI 1300 Fall 2021
// Author: Luke Sellmayer
// Recitation: 117 – Meenakshi
// Project 3 - Sticks Implementation

#include "Sticks.h"

Sticks::Sticks() {
    srand(time(0)); // setting seed for random generator
    stickVect.resize(4); 
}

void Sticks::rollSticks() {    
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int r = rand() % 2;
        if (r == 1) { // 1 represents a white side coming up
            stickVect.at(i) = true;
            count++;
        }
        else {
            stickVect.at(i) = false;
        }
    }
    switch (count) {
        case 0: // all black comes up
            result = 5;
            break;
        case 1: // 1 white, 3 black
            result = 1;
            break;
        case 2: // 2 white, 2 black
            result = 2;
            break;
        case 3: // 3 white, 1 black
            result = 3;
            break;
        case 4: // all white comes up
            result = 4;
            break;
    }
}

int Sticks::getResult() const {
    return result;
}

void Sticks::drawSticks() const {
    for (int i = 0; i < stickVect.size(); i++) {
        if (stickVect.at(i) == true) {
            cout << "▮  ";
        }
        else {
            cout << "▯  ";
        }
    }
    cout << endl;
}



