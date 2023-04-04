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
        FlightData** hashTable;
        primesieve::iterator it;
        FlightData* constant;

        void rehash();

    public:
        HashSet(int tableSize);
        bool insert(FlightData* flightData);
        bool contains(FlightData* flightData);
        bool remove(FlightData* flightData);
        int size();
        float load_factor();
};