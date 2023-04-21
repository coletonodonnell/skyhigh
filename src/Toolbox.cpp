#include "Toolbox.h"
#include <set>

Toolbox::Toolbox()
{
    // Airlines
    airlines["WN"] = 1;
    airlines["DL"] = 2;
    airlines["AA"] = 3;
    airlines["UA"] = 4;
    airlines["B6"] = 5;
    airlines["AS"] = 6;
    airlines["NK"] = 7;
    airlines["G4"] = 8;
    airlines["F9"] = 9;
    airlines["HA"] = 10;
    airlines["SY"] = 11;
    airlines["VX"] = 12;

    std::set<int> state({1, 2, 3, 4, 5, 11, 12, 13, 14, 15, 16, 21, 22, 23, 31, 32, 
                         33, 34, 35, 36, 37, 38, 39, 41, 42, 43, 44, 45, 51, 52, 53,
                         54, 61, 62, 63, 64, 65, 66, 67, 71, 72, 73, 74, 81, 82, 83,
                         84, 85, 86, 87, 88, 91, 92, 93});

    for (auto i: state)
    {
        originBTreeBuckets[i] = new BTreeSet();
        destBTreeBuckets[i] = new BTreeSet();
        originHashBuckets[i] = new HashSet(1400);
        destHashBuckets[i] = new HashSet(1400);
    }

    bucketSelect = true;
}

Toolbox::~Toolbox()
{
    for (auto i = originBTreeBuckets.begin(); i != originBTreeBuckets.end(); i++)
        delete i->second;
    for (auto i = destBTreeBuckets.begin(); i != destBTreeBuckets.end(); i++)
        delete i->second;
    for (auto i = originHashBuckets.begin(); i != originHashBuckets.end(); i++)
        delete i->second;
    for (auto i = destHashBuckets.begin(); i != destHashBuckets.end(); i++)
        delete i->second;
}

std::map<std::string, int>& Toolbox::getAirlines()
{
    return airlines;
}

std::map<int, BTreeSet*>& Toolbox::getOriginBTreeBuckets()
{
    return originBTreeBuckets;
}

std::map<int, HashSet*>& Toolbox::getOriginHashBuckets()
{
    return originHashBuckets;
}

std::map<int, BTreeSet*>& Toolbox::getDestBTreeBuckets()
{
    return destBTreeBuckets;
}

std::map<int, HashSet*>& Toolbox::getDestHashBuckets()
{
    return destHashBuckets;
}

bool Toolbox::getBucketSelect()
{
    return bucketSelect;
}

void Toolbox::setBucketSelect()
{
    bucketSelect = !bucketSelect;
}

Toolbox& Toolbox::getInstance()
{
    static Toolbox tb;
    return tb;
}