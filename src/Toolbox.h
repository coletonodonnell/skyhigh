#pragma once
#include <map>
#include <string>

class Toolbox
{
    private:
        Toolbox();

    public:
        ~Toolbox();
        Toolbox& getInstance();
        std::map<std::string, std::pair<double, double>> airports;
};