using namespace std;

#include "ShapesGood.h"

#include <iostream>
#include <vector>


int main() {

    int count(0);
    vector<Shape*> shapes;
    shapes.push_back(new Square(10, 10, "orange"));
    shapes.push_back(new FilledSquare(10, 10, "purple", "red"));
    shapes.push_back(new FilledTextSquare(10, 10, "green", "gray", "Hello"));
    shapes.push_back(new Circle(10, 10, "blue"));
    shapes.push_back(new FilledCircle(10, 10, "yellow", "green"));
    shapes.push_back(new Arc(10, 10, "puce"));

    // Isn't this much nicer!
    for (Shape* shp : shapes) {
        cout << "\nShape " << count++ << ":\n";
        shp->draw();
    } // end for

    for (Shape* shp : shapes)
        delete shp;

} // end main
