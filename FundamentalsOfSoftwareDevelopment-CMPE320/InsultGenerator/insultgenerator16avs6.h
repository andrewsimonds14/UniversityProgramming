/*
 * insultgenerator16avs6.h
 *
 *
 *      Author: Andrew Simonds
 *      NetID: 16avs6
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InsultGenerator{

public:
    void initialize(); //The initialize() method should load all the source phrases from the InsultsSource.txt
    string talkToMe(); //Return a single insult
    vector<string> generate(const int &numInsults);
    void generateAndSave(const string &fileName, const int &numInsults); // generateAndSave() generates the requested number of unique insults and saves them to the filename

private:
    vector<string> first;//stores the first column of words in Insults.txt
    vector<string> second;//stores the second column of words in Insults.txt
    vector<string> third;//stores the third column of words in Insults.txt

};

class FileException : public exception{ //Exception for errors reading/writing to files

public:
    FileException();//generic constructor with hard-coded message
    FileException(string statement);//constructor with a programmer-dictated message
    string what();//getter for message

private:
    string message;//message that explains exception

};

class NumInsultsOutOfBounds : public exception{ //Exception for invalid number argument error

public:
    NumInsultsOutOfBounds();//generic constructor with hard-coded message
    NumInsultsOutOfBounds(string statement);//constructor with a programmer-dictated message
    string what();//getter for message

private:
    string message;//message that explains exception

};