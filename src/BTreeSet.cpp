#include "BTreeSet.h"
#include <iostream>
#include <queue>

int BTreeSet::getHeight(Node* root) // O(1)
{
    if ((root->right && root->left && root->right->height > root->left->height) || (root->right && !root->left))
        return root->right->height + 1;
    else if (root->left)
        return root->left->height + 1;
    else
        return 1;
}

int BTreeSet::getBF(Node* root) // O(1)
{
    if (root)
        return ((root->left) ? root->left->height : 0) - ((root->right) ? root->right->height : 0);
    return 0;
}

BTreeSet::Node* BTreeSet::rotateLeft(Node* root) // O(1)
{
    Node* grandchild = root->right->left;
    Node* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    newParent->left->height = getHeight(newParent->left);
    newParent->right->height = getHeight(newParent->right);
    newParent->height = getHeight(newParent);

    return newParent;
}

BTreeSet::Node* BTreeSet::rotateRight(Node* root) // O(1)
{
    Node* grandchild = root->left->right;
    Node* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    newParent->left->height = getHeight(newParent->left);
    newParent->right->height = getHeight(newParent->right);
    newParent->height = getHeight(newParent);

    return newParent;
}

BTreeSet::Node* BTreeSet::rotateLeftRight(Node* root) // O(1)
{
    Node* newChild = root->left->right;
    root->left->right = newChild->left;
    newChild->left = root->left;
    root->left = newChild;

    root->left->left->height = getHeight(root->left->left);
    root->left->height = getHeight(root->left);

    root = rotateRight(root);
    return root;
}

BTreeSet::Node* BTreeSet::rotateRightLeft(Node* root) // O(1)
{
    Node* newChild = root->right->left;
    root->right->left = newChild->right;
    newChild->right = root->right;
    root->right = newChild;

    root->right->right->height = getHeight(root->right->right);
    root->right->height = getHeight(root->right);

    root = rotateLeft(root);
    return root;
}

BTreeSet::Node* BTreeSet::insertRecursive(Node* root, FlightData* value) // O(log n)
{
    if (root == nullptr)
    {
        return new Node(value, 1);
        counter_size++;
    }

    if (value->getID() < root->data->getID())
        root->left = insertRecursive(root->left, value);
    else if (value->getID() > root->data->getID())
        root->right = insertRecursive(root->right, value);
    else
    {
        stateFlag = true;
        return root;
    }

    if (!stateFlag)
    {
        root->height = getHeight(root);

        int bf = getBF(root);

        if (bf < -1)
        {
            if (getBF(root->right) <= 0)
                return rotateLeft(root);

            if (getBF(root->right) > 0)
                return rotateRightLeft(root);
        }

        if (bf > 1)
        {
            if (getBF(root->left) >= 0)
                return rotateRight(root);

            if (getBF(root->left) < 0)
                return rotateLeftRight(root);
        }
    }

    return root;
}

BTreeSet::Node* BTreeSet::containsRecursive(Node* root, FlightData* value) // O(log n)
{
    if (root == nullptr || root->data->getID() == value->getID())
        return root;

    if (value->getID() < root->data->getID())
        return containsRecursive(root->left, value);
    
    return containsRecursive(root->right, value);
}

void BTreeSet::postOrderDelete(Node* root) // O(n)
{
    if (root == nullptr)
        return;
    else
    {
        postOrderDelete(root->left);
        postOrderDelete(root->right);
        delete root;
    }
}

bool BTreeSet::insert(FlightData* flightData) // O(log n)
{
    head = insertRecursive(head, flightData);
    if (stateFlag)
    {
        stateFlag = false;
        return false;
    }
    else return true;
}

bool BTreeSet::contains(FlightData* flightData) // O(log n)
{
    Node* result = containsRecursive(head, flightData);
    if (result)
        return true;
    return false;
}

std::vector<FlightData*> BTreeSet::intersection(BTreeSet& b) // O(n log n)
{
    std::vector<FlightData*> intersection;

    if (head == nullptr)
        return intersection;

    std::queue<Node*> q;

    q.push(head);

    // BFS iteration over A set (this current object)
    while (!q.empty())
    {
        Node* node = q.front();
        if (b.contains(node->data)) // if B contains this node in A, this is an intersection
            intersection.push_back(node->data);
        q.pop();

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }

    return intersection;
}

void BTreeSet::breadthFirstSearch() // O(n)
{
    if (head == nullptr)
        return;

    std::queue<Node*> q;

    q.push(head);

    while (!q.empty())
    {
        Node* node = q.front();
        std::cout << node->data->getID() << " ";
        q.pop();

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
}

BTreeSet::~BTreeSet()
{
    postOrderDelete(head);
}