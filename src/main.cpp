#include "FlightData.h"
#include "test.h"
#include "Toolbox.h"
#include <iostream>
#include <map>
#include <chrono>
#include <rapidcsv.h>
#include <pqxx/pqxx>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  
  rapidcsv::Document doc("csv/flights1.csv");

  std::vector<FlightData*> main;
  HashSet mainHashSet(1000000);
  BTreeSet mainBTreeSet;

  for (int i = 0; i < 500000; i++)
  {
    std::vector<std::string> row = doc.GetRow<std::string>(i);
    FlightData* flightData = new FlightData(std::stoi(row[0]), static_cast<regionCode>(std::stoi(row[2])), row[1], static_cast<regionCode>(std::stoi(row[4])), row[3], static_cast<airlineCode>(Toolbox::getInstance().getAirlines()[row[5]]), std::stof(row[6]));
    main.push_back(flightData);
    mainHashSet.insert(flightData);
    mainBTreeSet.insert(flightData);

    Toolbox::getInstance().getOriginBTreeBuckets()[std::stoi(row[2])]->insert(flightData);
    Toolbox::getInstance().getOriginHashBuckets()[std::stoi(row[2])]->insert(flightData);
    Toolbox::getInstance().getDestBTreeBuckets()[std::stoi(row[4])]->insert(flightData);
    Toolbox::getInstance().getDestHashBuckets()[std::stoi(row[4])]->insert(flightData); 
  }

  
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  clean(main);
  std::cout << duration.count() << std::endl;
}