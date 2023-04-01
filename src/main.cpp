#include <iostream>
#include "FlightData.h"
#include <vector>

int main()
{
  std::vector<FlightData> flights;
  for (int i = 0; i < 10000000; i++)
  {
    FlightData flightData(regionCode::AK, std::pair<float, float>(1.0, 1.0), regionCode::AL, std::pair<float, float>(1.0, 1.0), airlineCode::AA, 127.0);
    flights.push_back(flightData);
  }
  for (auto i: flights)
    std::cout << i.getID() << std::endl;
}