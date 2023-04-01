#include "HashSet.h"
#include <primesieve.hpp>

void HashSet::rehash()
{
    it.jump_to(maxSize * 2);               // double size of hash table, find nearest prime, e.g. nearestPrime(maxSize * 2)
    int oldSize = maxSize;                 // for iterator
    maxSize = it.next_prime();
    std::vector<FlightData*> newHashtable; // this is our new hashTable
    newHashtable.resize(maxSize, nullptr); // 

    for (int i = 0; i < oldSize; i++)
    {
        if (hashTable.at(i) != nullptr)
        {
            int indexCount = i;
            int probe = 1;
            while (newHashtable.at(indexCount) != nullptr)
            {
                indexCount = (indexCount + probe * probe) % maxSize;
                probe++;
            }

            newHashtable.insert(newHashtable.begin() + indexCount, hashTable.at(i));
        }
    }

    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);
    hashTable = newHashtable;
}

HashSet::HashSet() : loadFactor(0.0), maxSize(1009), itemCount(0)
{
    hashTable.resize(maxSize, nullptr);
}

bool HashSet::insert(FlightData* flightData)
{
    int index = flightData->getID();
    int probe = 1;

    while(hashTable.at(index) != nullptr)
    {
        if (hashTable.at(index)->getID() == flightData->getID())
            return false;
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    hashTable.insert(hashTable.begin() + index, flightData);
    itemCount++;
    loadFactor = static_cast<float>(itemCount) / static_cast<float>(maxSize);

    if (loadFactor >= 0.5)
        rehash();

    return true;
}

bool HashSet::contains(FlightData* flightData)
{
    int index = flightData->getID();
    int probe = 1;
    while (hashTable.at(index) != nullptr && hashTable.at(index)->getID() != flightData->getID())
    {
        index = (index + probe * probe) % maxSize;
        probe++;
    }

    if (hashTable.at(index) != nullptr && hashTable.at(index)->getID() == flightData->getID())
        return true;
    return false;
}

bool HashSet::remove(FlightData* flightData)
{

}

int HashSet::size()
{
    return itemCount;
}

float HashSet::load_factor()
{
    return loadFactor;
}