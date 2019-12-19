//
// Created by Andrew Simonds on 2019-11-25.
// Student Number: 200566566
// NetID: 16avs6
//
#pragma once

#include <string>
#include <utility>
using namespace std;

class Shape {
public:
    Shape() = default;
    Shape(int lengthIn, int widthIn) : length{lengthIn}, width{widthIn}
    {//Empty
    }
    virtual ~Shape() = default;
    int getLength(){
        return length;
    };
    int getWidth(){
        return width;
    };

    virtual void draw(){};
private:
    int length{}, width{};
};

class Fillable : public virtual Shape{
public:
    Fillable() = default;
    Fillable(int lengthIn, int widthIn, string fillIn) : Shape{ lengthIn, widthIn }, fillColour{std::move( fillIn )}
    {//Empty
    }
    string getFillColour(){
        return fillColour;
    };
private:
    string fillColour;
};

class HasText : public virtual Shape{
public:
    HasText() = default;
    HasText(int lengthIn, int widthIn, string textIn) : Shape{ lengthIn, widthIn }, text{std::move( textIn )}
    {//Empty
    }
    string getText(){
        return text;
    };
private:
    string text;
};

class Square : public virtual Shape{
public:
    Square() = default;
    Square(int lengthIn, int widthIn, string colourIn) : Shape{ lengthIn, widthIn }, colour{ std::move(colourIn) }
    {//Empty
    }
    ~Square() override = default;
    string getColour(){
        return colour;
    };
    void draw() override;
private:
    string colour;
};

class FilledSquare : public Fillable, public Square{
public:
    FilledSquare() = default;
    FilledSquare(int lengthIn, int widthIn, string colourIn, string fillColourIn) : Square{ lengthIn, widthIn,std::move(colourIn) },  Fillable{ lengthIn, widthIn,std::move(fillColourIn) }
    {//Empty
    }
    ~FilledSquare() override = default;
    void draw() override;
};

class FilledTextSquare : public Fillable, public HasText, public Square{
public:
    FilledTextSquare() = default;
    FilledTextSquare(int lengthIn, int widthIn, string colourIn, string fillColourIn, string textIn) : Square{ lengthIn, widthIn,std::move(colourIn) },  Fillable{ lengthIn, widthIn,std::move(fillColourIn) }, HasText{ lengthIn, widthIn,std::move(textIn) }
    {//Empty
    }
    ~FilledTextSquare() override = default;
    void draw() override;
};

class Circle : public virtual Shape{
public:
    Circle() = default;
    Circle(int lengthIn, int widthIn, string colourIn) : Shape{ lengthIn, widthIn }, colour{ std::move(colourIn) }
    {//Empty
    }
    ~Circle() override = default;
    string getColour(){
        return colour;
    };
    void draw() override;
private:
    string colour;
};

class FilledCircle : public Fillable, public Circle{
public:
    FilledCircle() = default;
    FilledCircle(int lengthIn, int widthIn, string colourIn, string fillColourIn) : Circle{ lengthIn, widthIn,std::move(colourIn) },  Fillable{ lengthIn, widthIn,std::move(fillColourIn) }
    {//Empty
    }
    ~FilledCircle() override = default;
    void draw() override;
};

class Arc : public Shape{
public:
    Arc()= default;
    Arc(int lengthIn, int widthIn, string colourIn) : Shape{ lengthIn, widthIn }, colour{ std::move(colourIn) }
    {//Empty
    }
    ~Arc() override = default;
    string getColour(){
        return colour;
    };
    void draw() override;
private:
    string colour;
};
