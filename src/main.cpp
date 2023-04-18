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

  // std::vector<HashSet> origins;      // 50
  // std::vector<HashSet> destinations; // 50
  // std::vector<HashSet> airlines;     // 12

  // std::vector<BTreeSet> origins; 
  // std::vector<BTreeSet> destinations;
  // std::vector<BTreeSet> airlines;

  // HashSet practice(1000000);

  // for (int i = 0; i < 500000; i++)
  // {
  //   FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
  //   practice.insert(newFlight);
  // }

  // BTreeSet test;

  // for (int i = 0; i < 25; i++)
  // {
  //   FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
  //   test.insert(newFlight);
  // }

  // auto a = new FlightData(0, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
  // std::cout << test.insert(a) << std::endl;
  // std::cout << test.contains(a) << std::endl;

  // test.breadthFirstSearch();

  HashSet practice(50);

  for (int i = 0; i < 50; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    practice.insert(newFlight);
    std::cout << practice.contains(newFlight)<<std::endl;
  }

  std::cout << practice.insert(new FlightData(0, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0)) << std::endl;

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << duration.count() << std::endl;
}