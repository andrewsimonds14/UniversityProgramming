/*
 * insultgenerator16avs6.cpp
 *
 *
 *      Author: Andrew Simonds
 *      NetID: 16avs6
 */

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include "insultgenerator16avs6.h"

using namespace std;

//Exception Constructors

FileException::FileException(){
    message = "Error: Issue regarding file";
}

FileException::FileException(string inputMessage){
    message = inputMessage;
}

string FileException::what(){
    return message;
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(){
    message = "Error: Number of insults invalid for this argument";
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(string inputMessage){
    message = inputMessage;
}

string NumInsultsOutOfBounds::what(){
    return message;
}



void InsultGenerator::initialize() {
    //***Change destination if running on different PC***
    string insultsText = "C:\\Users\\andre\\CLionProjects\\InsultGenerator\\InsultsSource.txt";
    string line, left, mid, right;

    ifstream file;
    file.open(insultsText.c_str());//open file
    if (file.fail()) {//Throw file not accessible exception
        throw FileException("Error could not open file");
    }
    else {
        while (file >> left >> mid >> right) {
            first.push_back(left);
            second.push_back(mid);
            third.push_back(right);
        }
    }
    file.close();

}

string InsultGenerator::talkToMe(){ //Return single random test insult
    int firstWord = rand()%50;
    int secondWord = rand()%50;
    int thirdWord = rand()%50;

    return ("Thou "+ first.at(firstWord) +" "+ second.at(secondWord) +" "+ third.at(thirdWord)+ "!\n");
}

vector<string> InsultGenerator::generate(const int &numInsults){

    if ((numInsults < 0) || (numInsults > 10000)) //Check numInsults size
        throw NumInsultsOutOfBounds("Invalid number of insults (Must be between 1-10,000)");
    else{
        set<string> insultSet;//Set to store insults
        int firstWord, secondWord, thirdWord;
        string oneInsult;

        while(insultSet.size() < numInsults){
            firstWord = rand()%50;
            secondWord = rand()%50;
            thirdWord = rand()%50;

            oneInsult = ("Thou "+ first.at(firstWord) +" "+ second.at(secondWord) +" "+ third.at(thirdWord) + "!\n");
            insultSet.insert(oneInsult);//Add insult to list
        }
        vector<string> insults;
        insults.assign(insultSet.begin(), insultSet.end()); //Put set into vector
        sort(insults.begin(), insults.end());//Sorts vector alphabetically
        return insults;
    }
}

void InsultGenerator::generateAndSave(const string &fileName, const int &numInsults){
    if ((numInsults < 0) || (numInsults > 10000)) //Check numInsults size
        throw NumInsultsOutOfBounds("Invalid number of insults (Must be between 1-10,000)");
    else{

        vector<string> insults = generate(numInsults);

        ofstream fileOut;
        fileOut.open(fileName.c_str());
        if(fileOut.fail()){
            throw FileException("Error could not write to file!");
        }
        else{
            cout << "\nWriting to " + fileName + "...\n";
        }
        for (string i : insults)
            fileOut << i << "\n";
        fileOut.close();
    }
}