#include "skyscraper.h"

Skyscraper::Skyscraper(const std::string &name, double height, int nrFloors):
        m_name(name), m_height(height), m_nrFloors(nrFloors){
    if(m_height < 0 || m_nrFloors < 0)
        throw
                std::invalid_argument("Arguments must be non-negative.");
}

void Skyscraper::print() const {
    std::cout << this->m_name << " " << this->m_height << " "
              << this->m_nrFloors << '\n';
}