#include <iostream>
#include <vector>
#include <algorithm>
#include "skyscraper.h"
#include "itemnames.h"

int main()
{
    std::vector<Skyscraper> skyscrapers;
    skyscrapers.push_back(Skyscraper("Empire State", 381, 102));
    skyscrapers.push_back(Skyscraper("Petronas", 452, 88));
    skyscrapers.push_back(Skyscraper("Burj Khalifa", 828, 163));
    skyscrapers.push_back(Skyscraper("Taipei", 509, 101));

    std::sort(skyscrapers.begin(),skyscrapers.end(), EntityComp(HEIGHT));
    for(unsigned int i = 0; i < skyscrapers.size(); i++)
        skyscrapers.at(i).print();

    return 0;
}