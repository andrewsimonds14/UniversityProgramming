//
// Created by Andrew Simonds on 2019-11-25.
// Student Number: 200566566
// NetID: 16avs6
//

#include "ShapesGood.h"
#include <iostream>

using namespace std;

void Square::draw(){
    cout << "Drawing a " + getColour() + " square\n";
}

void FilledSquare::draw(){
    cout << "Drawing a " + getColour() + " square.  With " + getFillColour() + " fill.\n";
}

void FilledTextSquare::draw(){
    cout << "Drawing a " + getColour() + " square.  With " + getFillColour() + " fill.  Containing the text : '" + getText() +"'\n";
}

void Circle::draw(){
    cout << "Drawing a " + getColour() + " circle\n";
}

void FilledCircle::draw(){
    cout << "Drawing a " + getColour() + " circle.  With " + getFillColour() + " fill.\n";
}

void Arc::draw(){
    cout << "Drawing a " + getColour() + " arc\n";
}

