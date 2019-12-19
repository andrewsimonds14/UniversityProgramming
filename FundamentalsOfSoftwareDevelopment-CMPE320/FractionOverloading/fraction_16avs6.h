//
// Created by Andrew Simonds on 2019-10-08.
// Student Number: 20056566
//For testing, change accessor names in "FractionTest" to getNum() and getDenom()
//

#include <string>
#include <iostream>

using namespace std;

class Fraction{
    public:
        //Constructors
        Fraction();
        Fraction(int whole);
        Fraction(int num, int denom);
        //Greatest Common Divisor
        int gcd(int a, int b);
        //Accessors
        int getNum() const;
        int getDenom() const;
        //Overloading
        //Unary Operators
        Fraction operator-(); // Negation
        Fraction operator++(int); // Pre increment
        Fraction& operator++(); // Post increment

        //Binary Operators
        friend Fraction operator+(const Fraction& f1, const Fraction& f2); // Addition
        friend Fraction operator-(const Fraction& f1, const Fraction& f2); // Subtraction
        friend Fraction operator*(const Fraction& f1, const Fraction& f2);// Multiplication
        friend Fraction operator/(const Fraction& f1, const Fraction& f2); // Division
        Fraction& operator+=(const Fraction& f); // Addition and assignment

        friend bool operator<(const Fraction& f1, const Fraction& f2); // Comparison Operator
        friend bool operator<=(const Fraction& f1, const Fraction& f2); // Comparison Operator
        friend bool operator==(const Fraction& f1, const Fraction& f2); // Comparison Operator
        friend bool operator!=(const Fraction& f1, const Fraction& f2); // Comparison Operator
        friend bool operator>=(const Fraction& f1, const Fraction& f2); // Comparison Operator
        friend bool operator>(const Fraction& f1, const Fraction& f2); // Comparison Operator
        friend ostream& operator<<(ostream& out, const Fraction& f); //Used w/ Cout
        friend istream& operator>>(istream& in, Fraction& f); // Used w/ Cin
    private:
        int numerator;
        int denominator;
};

class FractionException : public exception{
    public:
         FractionException();
         FractionException(string inputMessage);
         string getMessage();
    private:
          string message;
};
