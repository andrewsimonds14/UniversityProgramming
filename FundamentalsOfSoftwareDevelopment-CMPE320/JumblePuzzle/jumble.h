//
// Created by Andrew Simonds on 2019-11-08.
// Student Number: 20056566
//
#pragma once

#include <string>

using namespace std;

typedef char* charArrayPtr;

class BadJumbleException : exception{
public:
    BadJumbleException();
    string what();

private:
    string errorMessage;
};

class JumblePuzzle{
public:
    JumblePuzzle(const string&, const string&); //Normal Constructor
    JumblePuzzle(const JumblePuzzle&); //Copy constructor
    ~JumblePuzzle(); //Destructor

    charArrayPtr* getJumble();
    int getSize();
    int getRowPos();
    int getColPos();
    char getDirection();
    static int randomBetween(int x, int y);

private:
    string word;
    int rowPos = -1;
    int colPos = -1;
    int dir; // 0,1,2,3 = n,e,s,w
    int size = 0;
    int difficulty;
    charArrayPtr* puzzle;
    void generateJumble();


};