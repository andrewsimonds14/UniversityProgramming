//
// Created by Andrew Simonds on 2019-11-08.
// Student Number: 20056566
//

#include <string>
#include <iostream>
#include "jumble.h"
#include <random>

using namespace std;

BadJumbleException::BadJumbleException() {
    errorMessage = "Error: Bad Jumble";
}

string BadJumbleException::what() {
    return errorMessage;
}

JumblePuzzle::JumblePuzzle(const string& wordToHide, const string& puzzleDifficulty){
    if(wordToHide.length() < 3 || wordToHide.length() > 10){
        throw BadJumbleException();
    }
    word = wordToHide;

    if (puzzleDifficulty == "easy"){
        difficulty = 2;
    }
    else if (puzzleDifficulty == "medium"){
        difficulty = 3;
    }
    else if (puzzleDifficulty == "hard"){
        difficulty = 4;
    }
    else throw BadJumbleException();

    size = int(word.length()) * difficulty;

    puzzle = new charArrayPtr[size];
    for (int i = 0; i < size; i++)
    {
        puzzle[i] = new char[size];
    }
    generateJumble();
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& puzzleToCopy) {
    this->word = puzzleToCopy.word;
    this->rowPos = puzzleToCopy.rowPos;
    this->colPos = puzzleToCopy.colPos;
    this->dir = puzzleToCopy.dir;
    this->size = puzzleToCopy.size;
    this->difficulty = puzzleToCopy.difficulty;

    this->puzzle = new charArrayPtr[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->puzzle[i] = new char[this->size];
        for (int j = 0; j < this->size; j++)
        {
            this->puzzle[i][j] = puzzleToCopy.puzzle[i][j];
        }
    }
}

JumblePuzzle::~JumblePuzzle() {
    // Free rows
    for (int i = 0; i < size; i++){
        delete[] puzzle[i];
    }
    // Then free actual array
    delete[] puzzle;
}

charArrayPtr* JumblePuzzle::getJumble(){
    return puzzle;
}
int JumblePuzzle::getSize() {
    return size;
}
int JumblePuzzle::getRowPos(){
    return rowPos;
}
int JumblePuzzle::getColPos() {
    return colPos;
}
char JumblePuzzle::getDirection() {
    if (dir == 0){
        return 'n';
    }
    else if (dir == 1){
        return 'e';
    }
    else if (dir == 2){
        return 's';
    }
    else if (dir == 3){
        return 'w';
    }
    else{
        throw BadJumbleException();
    }
}

int JumblePuzzle::randomBetween(int x, int y){
    int r = rand();
    return(r % abs(y-x) + x);
}

void JumblePuzzle::generateJumble() {
    //Get direction of hidden word
    dir = rand() % 4;
    //Ensure the word can fit in that direction (set starting row and column position)
    int length = int(word.length());
    if (dir == 0){ //'North'
        rowPos = randomBetween(length - 1, size - 1);
        colPos = randomBetween(0, size - 1);
    }
    else if (dir == 1){ //'East'
        rowPos = randomBetween(0, size - 1);
        colPos = randomBetween(0, size - length - 1);
    }
    else if (dir == 2){ //'South'
        rowPos = randomBetween(0, size - length - 1);
        colPos = randomBetween(0, size - 1);
    }
    else if (dir == 3){ //'West'
        rowPos = randomBetween(0, size - 1);
        colPos = randomBetween(length - 1, size - 1);
    }
    //Define start and end point of word in array
    int startingPos = 0;
    int endingPos = size -1;
    if (dir == 0){ //'North'
        startingPos = rowPos - word.length() + 1;
        endingPos = rowPos;
    }
    else if (dir == 1){ //'East'
        startingPos = colPos;
        endingPos = colPos + (length - 1);
    }
    else if (dir == 2){ //'South'
        startingPos = rowPos;
        endingPos = rowPos + word.length() + 1;
    }
    else if (dir == 3){ //'West'
        startingPos = colPos -(length - 1) ;
        endingPos = colPos;
    }
    //Hide word in array of random characters
    int hiddenWordIndex = 0;
    for(int row = 0; row < size; row++){
        for(int col = 0; col< size; col++){
            char randChar = randomBetween(97, 122); //ASCII values for char a - z
            //Fill array w rand char or with part of word if pos is right
            if(dir == 0 && colPos == col && startingPos <= row && row<= endingPos) //North
                puzzle[row][col] = word[word.length() - 1 - hiddenWordIndex++];

            else if(dir == 1 && rowPos == row && startingPos <= col && col<= endingPos) //East
                puzzle[row][col] = word[hiddenWordIndex++];

            else if(dir == 2 && colPos == col && startingPos <= row && row<= endingPos) //South
                puzzle[row][col] = word[hiddenWordIndex++];

            else if(dir == 3 && rowPos == row && startingPos <= col && col<= endingPos) //West
                puzzle[row][col] = word[word.length() - 1 - hiddenWordIndex++];

            else //Rand char
                puzzle[row][col] = randChar;
        }
    }
}
