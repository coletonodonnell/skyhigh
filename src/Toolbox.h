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
        std::map<std::string, BTreeSet*> originBTreeBuckets;
        std::map<std::string, HashSet*> originHashBuckets;
        std::map<std::string, BTreeSet*> destBTreeBuckets;
        std::map<std::string, HashSet*> destHashBuckets;
    
    public:
        ~Toolbox();
        Toolbox(const Toolbox &) = delete;
        Toolbox& operator=(const Toolbox &) = delete;
        std::map<std::string, int>& getAirlines();
        std::map<std::string, BTreeSet*>& getOriginBTreeBuckets();
        std::map<std::string, HashSet*>& getOriginHashBuckets();
        std::map<std::string, BTreeSet*>& getDestBTreeBuckets();
        std::map<std::string, HashSet*>& getDestHashBuckets();

        bool getBucketSelect();
        void setBucketSelect();

        static Toolbox& getInstance();
};