#pragma once
#include "FlightData.h"
#include <vector>

class BTreeSet
{
    private:
        struct Node
        {
            FlightData* data;
            int height;
            Node* left;
            Node* right;
            Node(FlightData* data, int height) : data(std::move(data)), height(height), left(nullptr), right(nullptr) {} 
        };
        Node* head;
        bool stateFlag;
        int counter_size;

        static int getHeight(Node* root);
        static int getBF(Node* root);

        static Node* rotateLeft(Node* root);
        static Node* rotateRight(Node* root);
        static Node* rotateLeftRight(Node* root);
        static Node* rotateRightLeft(Node* root);

        Node* insertRecursive(Node* root, FlightData* value);
        Node* containsRecursive(Node* root, FlightData* value);
        void postOrderDelete(Node* root);

    public:
        BTreeSet() : head(nullptr), stateFlag(false), counter_size(0) {};
        ~BTreeSet();
        bool insert(FlightData* flightData);
        bool contains(FlightData* flightData);
        std::vector<FlightData*> intersection(BTreeSet& b);
        void breadthFirstSearch();
        int size();
};