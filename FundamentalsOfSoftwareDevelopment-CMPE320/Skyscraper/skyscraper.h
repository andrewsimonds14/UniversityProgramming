#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H
#include <string>
#include <iostream>
#include <stdexcept>
#include "itemnames.h"

class Skyscraper
{
public:
    Skyscraper(const std::string& name, double height, int nrFloors);
    double getHeight() const {return m_height;}
    std::string getName() const {return m_name;}
    int getNrFloors() const {return m_nrFloors;}
    void print() const;

private:
    std::string m_name;
    double m_height;
    int m_nrFloors;
};

struct EntityComp {
    int property;
    EntityComp(int property) {this->property = property;}
    bool operator()(const Skyscraper& s1, const Skyscraper& s2) const {
        if(property == FLOORS)
            return s1.getNrFloors() < s2.getNrFloors();
        else
            return s1.getHeight() < s2.getHeight();
    }
};

#endif // SKYSCRAPER_H