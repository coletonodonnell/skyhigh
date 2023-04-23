#include "test.h"
#include "HashSet.h"
#include "BTreeSet.h"
#include <pqxx/pqxx>
#include <iostream>

void clean(std::vector<FlightData*> data)
{
  for (auto flight: data)
    delete flight;
}

bool test1() // test 500,000 elements stored
{
  HashSet test1_hash_set(20);
  BTreeSet test1_tree_set;
  std::vector<FlightData*> tests;
  tests.reserve(250000);

  for (int i = 0; i < 250000; i++)
  {
    FlightData* newFlight = new FlightData(i, regionCode::AK, "PAX", regionCode::AL, "NYC", airlineCode::AA, 127.0);
    test1_hash_set.insert(newFlight);
    test1_tree_set.insert(newFlight);
    tests.push_back(newFlight);
  }

  std::vector<bool> hash_test;
  hash_test.reserve(250000);
  std::vector<bool> tree_test;
  tree_test.reserve(250000);

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
    if (i > 74)
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

  int count = 74;
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
    if (i > 74)
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

  for (auto flight: intersection)
  {
    if (!(test3_btree_set_A.contains(flight) && test3_btree_set_B.contains(flight)))
    {
      clean(tests);
      std::cout << "TEST 3 \033[1;31mFAILED\033[0m" << std::endl;
      return false;
    }
  }

  if (intersection.size() != 50)
  {
    clean(tests);
    std::cout << "TEST 3 \033[1;31mFAILED\033[0m: " << intersection.size() << std::endl;
    return false;
  }

  std::cout << "TEST 3 \033[1;32mPASSED\33[0m" << std::endl;
  clean(tests);
  return true;
}

bool test4() // test connection to server, read flights table
{
  try
  {
    std::string connectionString = "host=skyhigh.cxneevt5jfbi.us-east-2.rds.amazonaws.com port=5432 dbname=production user=postgres password=dPaA&3A^JUmG*^!MLX*z2&";
    auto conn = pqxx::connection(connectionString.c_str());
    pqxx::work work(conn);
    pqxx::row r = work.exec1("SELECT * FROM flights");
    work.commit();
    std::cout << "TEST 4 \033[1;32mPASSED\33[0m:";
    for (auto a : r)
      std::cout << " " << a.as<std::string>();
    std::cout << std::endl;
    return true;
  }
  catch (const std::exception &e)
  {
    std::cout << "TEST 4 \033[1;31mFAILED\033[0m: " << e.what() << std::endl;
    return false;
  }
}

bool test5()
{
  try
  {
    std::string connectionString = "host=skyhigh.cxneevt5jfbi.us-east-2.rds.amazonaws.com port=5432 dbname=production user=postgres password=dPaA&3A^JUmG*^!MLX*z2&";
    auto conn = pqxx::connection("host=skyhigh.cxneevt5jfbi.us-east-2.rds.amazonaws.com port=5432 dbname=production user=postgres password=dPaA&3A^JUmG*^!MLX*z2&");
    pqxx::work w(conn);
    pqxx::result r = w.exec("TRUNCATE tests");
    r = w.exec("INSERT INTO tests VALUES (0, 23, 'PHL', 91, 'LAX', 1, 182.3);");
    pqxx::row a = w.exec1("SELECT * FROM tests");
    w.commit();
    bool state = true;
    if (a[0].as<std::string>() != "0")
      state = false;
    if (a[1].as<std::string>() != "23")
      state = false;
    if (a[2].as<std::string>() != "PHL")
      state = false;
    if (a[3].as<std::string>() != "91")
      state = false;
    if (a[4].as<std::string>() != "LAX")
      state = false;
    if (a[5].as<std::string>() != "1")
      state = false;
    if (a[6].as<std::string>() != "182.3")
      state = false;
    if (state)
    {
      std::cout << "TEST 5 \033[1;32mPASSED\33[0m" << std::endl;
      return true;
    }
    std::cout << "TEST 5 \033[1;31mFAILED\033[0m" << std::endl;
    return false;
  }
  catch (const std::exception &e)
  {
    std::cout << "TEST 5 \033[1;31mFAILED\033[0m: " << e.what() << std::endl;
    return false;
  }
}

void run_tests()
{
  test1();
  test2();
  test3();
  test4();
  test5();
}