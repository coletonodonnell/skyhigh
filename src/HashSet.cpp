#include "HashSet.h"
#include <primesieve.hpp>

void HashSet::rehash() // should be working...
{
    it.jump_to(maxSize * 2);               // double size of hash table, find nearest prime, e.g. nearestPrime(maxSize * 2)
    int oldSize = maxSize;                 // for later for loop
    maxSize = it.next_prime();
    FlightData** newHashtable = new FlightData*[maxSize](); // this is our new hashTable

    for (int i = 0; i < oldSize; i++)
    {
        if (hashTable[i] != nullptr)
        {
            int indexCount = i;
            int probe = 1;
            while (newHashtable[indexCount] != nullptr)
            {
                indexCount = (indexCount + probe * probe) % maxSize;
                probe++;
            }

            newHashtable[indexCount] = hashTable[i];
        }
    }

    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);
    delete hashTable;
    hashTable = newHashtable;
}

HashSet::HashSet(int tableSize) : loadFactor(0.0), maxSize(tableSize), itemCount(0)
{
    FlightData** newHashtable = new FlightData*[maxSize]();
    hashTable = newHashtable;
}

bool HashSet::insert(FlightData* flightData) // in theory works
{
    int index = flightData->getID();
    int id = flightData->getID();
    int probe = 1;

    while(hashTable[index] != nullptr)
    {
        if (hashTable[index]->getID() == id)
            return false;
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    hashTable[index] = flightData;
    itemCount++;
    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);

    if (loadFactor >= 0.5)
        rehash();

    return true;
}

bool HashSet::contains(FlightData* flightData) // untested
{
    int index = flightData->getID();
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

bool HashSet::remove(FlightData* flightData) // untested
{
    int index = flightData->getID();
    int probe = 1;
    while (hashTable[index] != nullptr && hashTable[index]->getID() != flightData->getID())
    {
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    if (hashTable[index] != nullptr && hashTable[index]->getID() == flightData->getID())
    {    
        hashTable[index] = nullptr;
        return true;
    }
    return false;

}

int HashSet::size()
{
    return itemCount;
}

float HashSet::load_factor()
{
    return loadFactor;
}