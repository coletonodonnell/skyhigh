#include <iostream>
#include <vector>

int main()
{
    std::vector<int*> myvector;
    myvector.resize(2, nullptr);
    int* a = new int(5);
    int* b = new int(6);
    myvector.push_back(a);
    myvector.push_back(b);
    myvector.resize(5, b);
    return 0;
}