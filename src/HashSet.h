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
        HashSet(int tableSize);
        HashSet();
        // ~HashSet();
        // HashSet(const HashSet& l);

        bool insert(FlightData* flightData);
        bool contains(FlightData* flightData);
        std::vector<FlightData*> intersection(HashSet* b);
        int size();
        int getMaxSize();
        float load_factor();
};