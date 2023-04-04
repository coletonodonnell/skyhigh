#include "HashSet.h"
#include <primesieve.hpp>

void HashSet::rehash() // should be working...
{
    it.jump_to(maxSize * 2);                                // double size of hash table, find nearest prime, 
                                                            // e.g. nearestPrime(maxSize * 2)
    int oldSize = maxSize;                                  // for later for loop
    maxSize = it.next_prime();
    FlightData** newHashtable = new FlightData*[maxSize](); // this is our new hashTable

    for (int i = 0; i < oldSize; i++)
    {
        if (hashTable[i] != nullptr)
        {
            int indexCount = i;
            int probe = 0;
            while (newHashtable[indexCount] != nullptr)
            {
                probe++;
                indexCount = (indexCount + probe * probe) % maxSize;
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
    hashTable = new FlightData*[maxSize]();
    constant = new FlightData(INT16_MIN, regionCode::AK, "", regionCode::AK, "", airlineCode::AA, 0.0);
}

bool HashSet::insert(FlightData* flightData) // in theory works
{
    int index = flightData->getID();
    int id = flightData->getID();
    int probe = 0;

    while(hashTable[index] != nullptr)
    {
        if (hashTable[index]->getID() == id)
            return false;
        probe++;
        index = (index + probe * probe) % maxSize;
    }

    hashTable[index] = flightData;
    itemCount++;
    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);

    if (loadFactor > 0.5) // this makes the worst case O(n)
        rehash();         // keeping it at or below 0.5 guarantees collision resolution

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
    // If it is nullptr, it doesn't exist, probes won't have empty spots
    while (hashTable[index] != nullptr && hashTable[index]->getID() != flightData->getID())
    {
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    if (hashTable[index] != nullptr && hashTable[index]->getID() == flightData->getID())
    {    
        hashTable[index] = constant;         // if we set this to nullptr, remove and contains break
        return true;                         // so this constant acts as a pass through value
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