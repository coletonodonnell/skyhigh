#pragma once
#include <map>
#include "HashSet.h"
#include "BTreeSet.h"

class Toolbox
{
    private:
        Toolbox();
        bool bucketSelect; // true = HashSet, false = BTreeSet
        std::map<std::string, int> airlines;
        std::map<int, BTreeSet*> originBTreeBuckets;
        std::map<int, HashSet*> originHashBuckets;
        std::map<int, BTreeSet*> destBTreeBuckets;
        std::map<int, HashSet*> destHashBuckets;
    
    public:
        ~Toolbox();
        Toolbox(const Toolbox &) = delete;
        Toolbox& operator=(const Toolbox &) = delete;
        std::map<std::string, int>& getAirlines();
        std::map<int, BTreeSet*>& getOriginBTreeBuckets();
        std::map<int, HashSet*>& getOriginHashBuckets();
        std::map<int, BTreeSet*>& getDestBTreeBuckets();
        std::map<int, HashSet*>& getDestHashBuckets();

        bool getBucketSelect();
        void setBucketSelect();

        static Toolbox& getInstance();
};