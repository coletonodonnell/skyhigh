#pragma once
#include "FlightData.h"
#include <primesieve.hpp>
#include <vector>

class HashSet
{
    private:
        float loadFactor;
        int maxSize;
        int itemCount;
        std::vector<FlightData*> hashTable;
        primesieve::iterator it;

        void rehash();

    public:
        HashSet();
        bool insert(FlightData* flightData);
        bool contains(FlightData* flightData);
        bool remove(FlightData* flightData);
        int size();
        float load_factor();
};