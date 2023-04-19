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

bool test3() // test BTreeSet intersection
{
  BTreeSet test3_btree_set_A;
  BTreeSet test3_btree_set_B;
  std::vector<FlightData*> tests;
  tests.reserve(200);

  for (int i = 0; i < 100; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    test3_btree_set_A.insert(newFlight);
    if (i >= 74)
      test3_btree_set_B.insert(newFlight);
    tests.push_back(newFlight);
  }

  for (int i = 100; i < 200; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    test3_btree_set_B.insert(newFlight);
    if (i < 125)
      test3_btree_set_A.insert(newFlight);
    tests.push_back(newFlight);
  }

  std::vector<FlightData*> intersection = test3_btree_set_A.intersection(test3_btree_set_B);

  int count = 73;
  for (auto flight: intersection)
  {
    count++;
    if (!(test3_btree_set_A.contains(flight) && test3_btree_set_B.contains(flight)))
    {
      clean(tests);
      std::cout << "TEST 3 \033[1;31mFAILED\033[0m" << std::endl;
      return false;
    }
  }

  if (count != 124)
  {
    clean(tests);
    std::cout << "TEST 3 \033[1;31mFAILED\033[0m" << std::endl;
    return false;
  }

  std::cout << "TEST 3 \033[1;32mPASSED\33[0m" << std::endl;
  clean(tests);
  return true;
}

int main()
{
  test1();
  test2();
  test3();
}