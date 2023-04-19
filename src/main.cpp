#include <iostream>
#include "FlightData.h"
#include "HashSet.h"
#include "BTreeSet.h"
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <vector>

void clean(std::vector<FlightData*> data)
{
  for (auto flight: data)
    delete flight;
}

bool test1() // test 1,000,000 elements stored
{
  HashSet test1_hash_set(20);
  BTreeSet test1_tree_set;
  std::vector<FlightData*> tests;
  tests.reserve(1000000);

  for (int i = 0; i < 1000000; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    test1_hash_set.insert(newFlight);
    test1_tree_set.insert(newFlight);
    tests.push_back(newFlight);
  }

  std::vector<bool> hash_test;
  hash_test.reserve(1000000);
  std::vector<bool> tree_test;
  tree_test.reserve(1000000);

  for (auto flight: tests)
  {
    hash_test.push_back(test1_hash_set.contains(flight));
    tree_test.push_back(test1_tree_set.contains(flight));
  }

  for (bool result: hash_test)
  {
    if (!result)
    {
      std::cout << "TEST 1 \033[1;31mFAILED\033[0m: HASH SET" << std::endl;
      clean(tests);
      return false;
    }
  }

  for (bool result: tree_test)
  {
    if (!result)
    {
      std::cout << "TEST 1 \033[1;31mFAILED\033[0m: TREE SET" << std::endl;
      clean(tests);
      return false;
    }
  }

  std::cout << "TEST 1 \033[1;32mPASSED\33[0m" << std::endl;
  clean(tests);
  return true;
}

bool test2() // test HashSet intersection
{
  HashSet test2_hash_set_A(20);
  HashSet test2_hash_set_B(20);
  std::vector<FlightData*> tests;
  tests.reserve(200);


  for (int i = 0; i < 100; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    test2_hash_set_A.insert(newFlight);
    if (i >= 74)
      test2_hash_set_B.insert(newFlight);
    tests.push_back(newFlight);
  }

  for (int i = 100; i < 200; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    test2_hash_set_B.insert(newFlight);
    if (i < 125)
      test2_hash_set_A.insert(newFlight);
    tests.push_back(newFlight);
  }

  std::vector<FlightData*> intersection = test2_hash_set_A.intersection(&test2_hash_set_B);

  int count = 73;
  for (auto flight: intersection)
  {
    count++;
    if (flight->getID() != count)
    {
      clean(tests);
      std::cout << "TEST 2 \033[1;31mFAILED\033[0m" << std::endl;
      return false;
    }
  }

  if (count != 124)
  {
    clean(tests);
    std::cout << "TEST 2 \033[1;31mFAILED\033[0m" << std::endl;
    return false;
  }

  std::cout << "TEST 2 \033[1;32mPASSED\33[0m" << std::endl;
  clean(tests);
  return true;
}

int main()
{
  // auto start = std::chrono::high_resolution_clock::now();

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

  // auto stop = std::chrono::high_resolution_clock::now();
  // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  test1();
  test2();
}