//
// Created by Andrew Simonds on 2019-10-08.
// Student Number: 20056566
// For testing, change accessor names in "FractionTest" to getNum() and getDenom()
//


#include <string>
#include <iostream>
#include "fraction_16avs6.h"

using namespace std;

int Fraction :: gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

//Error handling class functions
FractionException::FractionException(){
    message = ("Can't have zero denominator");
}

FractionException::FractionException(string inputMessage){
    message = inputMessage;
}
string FractionException::getMessage() {
    return message;
}

// Fraction constructors
Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
}
Fraction::Fraction(int whole){
    numerator = whole;
    denominator = 1;
}
Fraction::Fraction(int num, int denom){
    if (denom == 0) {
        throw FractionException("Error!!! Denominator cannot be equal to 0!!!");
    }
    int val = gcd(num,denom);
    val = abs(val); // Ensure GCD is always positive
    if (denom < 0){ //If denominator is negative, reverse sign on both values
        numerator = -(num/val);
        denominator = -(denom/val);
    }
    else{
        numerator = num/val;
        denominator = denom/val;
    }
}

// Fraction accessors
int Fraction::getNum() const{
    return numerator;
}
int Fraction::getDenom() const{
    return denominator;
}

// Fraction overloading
Fraction Fraction :: operator-() {
    return Fraction(-numerator, denominator);
}

Fraction Fraction :: operator++(int) {  //Unused input argument
    Fraction f(numerator,denominator);
    numerator += denominator;
    return f;
}

Fraction& Fraction :: operator++() {
    numerator += denominator;
    return *this;
}

Fraction operator+ (const Fraction& f1, const Fraction& f2) {
    if (f1.getDenom() == f2.getDenom()) {
        return Fraction((f1.getNum() + f2.getNum()) , f1.getDenom());
    } else {
        return Fraction(((f1.getNum() * f2.getDenom()) + (f2.getNum() * f1.getDenom())), (f1.getDenom() * f2.getDenom()));
    }
}

Fraction operator- (const Fraction& f1, const Fraction& f2) {
    if (f1.getDenom() == f2.getDenom()) {
        return Fraction((f1.getNum() - f2.getNum()) , f1.getDenom());
    } else {
        return Fraction(((f1.getNum() * f2.getDenom()) - (f2.getNum() * f1.getDenom())), (f1.getDenom() * f2.getDenom()));
    }
}

Fraction operator* (const Fraction& f1, const Fraction& f2) {
    return Fraction ((f1.getNum() * f2.getNum()), (f1.getDenom() * f2.getDenom()));
}
Fraction operator/ (const Fraction& f1, const Fraction& f2) {
    return Fraction ((f1.getNum() * f2.getDenom()), (f1.getDenom() * f2.getNum()));
}

Fraction& Fraction::operator+= (const Fraction& f) {
    Fraction newF = Fraction(numerator, denominator) + f;
    numerator = newF.numerator;
    denominator = newF.denominator;
    return *this;
}

bool operator< (const Fraction& f1, const Fraction& f2) {
    return ((f1.getNum() * f2.getDenom()) < (f1.getDenom() * f2.getNum()));
}
bool operator<= (const Fraction& f1, const Fraction& f2) {
    return ((f1.getNum() * f2.getDenom()) <= (f1.getDenom() * f2.getNum()));
}
bool operator== (const Fraction& f1, const Fraction& f2) {
    return ((f1.getNum() * f2.getDenom()) == (f1.getDenom() * f2.getNum()));
}
bool operator!= (const Fraction& f1, const Fraction& f2) {
    return ((f1.getNum() * f2.getDenom()) != (f1.getDenom() * f2.getNum()));
}
bool operator>= (const Fraction& f1, const Fraction& f2) {
    return ((f1.getNum() * f2.getDenom()) >= (f1.getDenom() * f2.getNum()));
}
bool operator> (const Fraction& f1, const Fraction& f2) {
    return ((f1.getNum() * f2.getDenom()) > (f1.getDenom() * f2.getNum()));
}

ostream& operator<<(ostream& out, const Fraction& f){
    out << f.getNum() << "/" << f.getDenom();
    return out;
}

istream& operator>>(istream& in, Fraction& f){
    int fNum;
    int fDenom;
    std::string inputLine;
    if (getline(in, inputLine)) {
        int num_read = sscanf(inputLine.c_str(), "%d/%d", &fNum, &fDenom);
        if (num_read > 0) {
            if (num_read < 2) { // Check if it's an int not a fraction
                fDenom=1;
            }
            f = Fraction(fNum,fDenom);
        }
    }
    return in;
}
