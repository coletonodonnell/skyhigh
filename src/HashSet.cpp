#include "HashSet.h"
#include <primesieve.hpp>

HashSet::HashSet(int tableSize) : loadFactor(0.0), maxSize(tableSize), itemCount(0)
{
    hashTable = new FlightData*[maxSize]();
    constant = new FlightData(INT16_MIN, regionCode::AK, "", regionCode::AK, "", airlineCode::AA, 0.0);
}

void HashSet::rehash() // O(n)
{
    it.jump_to(maxSize * 2);                                // double size of hash table, find nearest prime, 
                                                            // e.g. nearestPrime(maxSize * 2)
    int oldSize = maxSize;                                  // for later for loop
    maxSize = it.next_prime();
    FlightData** newHashtable = new FlightData*[maxSize](); // this is our new hashTable

    for (int i = 0; i < oldSize; i++)                       // iterate over every element in the old table
    {
        if (hashTable[i] != nullptr)
        {
            int indexCount = i;
            int probe = 0;
            while (newHashtable[indexCount] != nullptr)     // rehash
            {
                probe++;
                indexCount = (indexCount + probe * probe) % maxSize;
            }

            newHashtable[indexCount] = hashTable[i];
        }
    }

    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);
    delete hashTable;
    hashTable = newHashtable;                               // set new hashtable as the objects hashtable
}

bool HashSet::insert(FlightData* flightData) // O(1) average, O(n) worst
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

bool HashSet::contains(FlightData* flightData) // O(1)
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

HashSet HashSet::intersection(HashSet b) // O(n)
{
    int selectedSize;
    if (b.getMaxSize() < maxSize)
        selectedSize = b.getMaxSize();
    else
        selectedSize = maxSize;
    HashSet intersection(selectedSize); // choose min maxSize between A and B because that
                                        // is the maximum size possible for an intersection

    for (int i = 0; i < maxSize; i++)
    {
        if (hashTable[i] != nullptr)
        {
            if (b.contains(hashTable[i]))
                intersection.insert(hashTable[i]);
        }
    }

    return intersection;
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