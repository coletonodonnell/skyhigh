#include <iostream>
#include "FlightData.h"
#include "HashSet.h"
#include "BTreeSet.h"
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <vector>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  std::vector<HashSet> origins;      // 50
  std::vector<HashSet> destinations; // 50
  std::vector<HashSet> airlines;     // 12

  std::vector<BTreeSet> origins; 
  std::vector<BTreeSet> destinations;
  std::vector<BTreeSet> airlines;

  HashSet practice(101);

  for (int i = 0; i < 1000; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    practice.insert(newFlight);
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << duration.count() << std::endl;
}