#include <iostream>
#include "FlightData.h"
#include "HashSet.h"
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <vector>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  HashSet practice(101);
  for (int i = 0; i < 1000; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, std::pair<float, float>(1.0, 1.0), regionCode::AL, std::pair<float, float>(1.0, 1.0), airlineCode::AA, 127.0);
    practice.insert(newFlight);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << duration.count() << std::endl;
}