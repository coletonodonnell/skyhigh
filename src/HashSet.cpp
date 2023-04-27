#include "HashSet.h"

HashSet::HashSet() : loadFactor(0.0), maxSize(5), itemCount(0)
{
    std::vector<FlightData*> table(maxSize, nullptr);
    hashTable = table;
} 

HashSet::HashSet(int tableSize) : loadFactor(0.0), maxSize(tableSize), itemCount(0)
{
    std::vector<FlightData*> table(tableSize, nullptr);
    hashTable = table;
}

// Create a new hash table
void HashSet::rehash() // O(n)
{
    it.jump_to(maxSize * 2);                                 // double size of hash table, find nearest prime, 
                                                             // e.g. nearestPrime(maxSize * 2)
                                                             // for later for loop
    maxSize = it.next_prime();                               // generate next set of primes
    std::vector<FlightData*> newHashtable(maxSize, nullptr); // this is our new hashTable

    for (auto flight: hashTable)                             // iterate over every element in the old table
    {
        if (flight != nullptr)
        {
            int index = flight->getID() % maxSize;
            int probe = 1;
            while (newHashtable[index] != nullptr)           // rehash
            {
                index = (index + probe * probe) % maxSize;
                probe++;
            }

            newHashtable[index] = flight;
        }
    }

    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);
    hashTable = newHashtable;                                // set new hashtable as the objects hashtable
}


bool HashSet::insert(FlightData* flightData) // O(1) average, O(n) worst
{
    int index = flightData->getID() % maxSize;
    int id = flightData->getID();
    int probe = 1;
    while (hashTable[index] != nullptr)
    {
        if (hashTable[index]->getID() == id)
            return false;
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    hashTable[index] = flightData;
    itemCount++;
    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);

    if (loadFactor >= 0.5) // this makes the worst case O(n)
        rehash();          // keeping it at or below 0.5 guarantees collision resolution

    return true;
}

bool HashSet::contains(FlightData* flightData) // O(n)
{
    int index = flightData->getID() % maxSize;
    int probe = 1;

    while (hashTable[index] != nullptr && hashTable[index]->getID() != flightData->getID())
    {
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    if (hashTable[index] != nullptr && hashTable[index]->getID() == flightData->getID())
        return true;

    return false;
}

std::vector<FlightData*> HashSet::intersection(HashSet* b) // O(n^2)
{
    int selectedSize;
    if (b->getMaxSize() < maxSize)
        selectedSize = b->getMaxSize();
    else
        selectedSize = maxSize;
    
    std::vector<FlightData*> intersection;

    for (int i = 0; i < maxSize; i++)
    {
        if (hashTable[i] != nullptr)
        {
            if (b->contains(hashTable[i]))
                intersection.push_back(hashTable[i]);
        }
    }

    return intersection;
}

std::vector<FlightData*> HashSet::getHashTable()
{
    std::vector<FlightData*> a;
    for (FlightData* i: hashTable)
    {
        if (i)
            a.push_back(i);
    }
    return a;
}

int HashSet::size() // O(1)
{
    return itemCount;
}

int HashSet::getMaxSize() // O(1)
{
    return maxSize;
}

float HashSet::load_factor() // O(1)
{
    return loadFactor;
}