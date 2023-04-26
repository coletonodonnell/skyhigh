#include "FlightData.h"
#include "test.h"
#include "Toolbox.h"
#include "UpdateListener.h"
#include <iostream>
#include <map>
#include <chrono>
#include <rapidcsv.h>
#include <pqxx/pqxx>
#include "signal.h"

using namespace efsw;

int main()
{  
  // CSV is read 
  rapidcsv::Document doc("csv/flights1.csv");

  std::vector<FlightData*> main;
  HashSet mainHashSet(1000000); // pre-populating means no need to rehash, more efficient
  BTreeSet mainBTreeSet;

  for (int i = 0; i < 500000; i++)
  {
    std::vector<std::string> row = doc.GetRow<std::string>(i);
    FlightData* flightData = new FlightData(std::stoi(row[0]), static_cast<regionCode>(std::stoi(row[2])), row[1], static_cast<regionCode>(std::stoi(row[4])), row[3], static_cast<airlineCode>(Toolbox::getInstance().getAirlines()[row[5]]), std::stof(row[6]));
    main.push_back(flightData);
    mainHashSet.insert(flightData);
    mainBTreeSet.insert(flightData);

    Toolbox::getInstance().getOriginBTreeBuckets()[row[1]]->insert(flightData);
    Toolbox::getInstance().getOriginHashBuckets()[row[1]]->insert(flightData);
    Toolbox::getInstance().getDestBTreeBuckets()[row[3]]->insert(flightData);
    Toolbox::getInstance().getDestHashBuckets()[row[3]]->insert(flightData); 
  }

  // Taken from the sample example here: https://github.com/SpartanJ/efsw

  efsw::FileWatcher* fileWatcher = new efsw::FileWatcher();
  UpdateListener* listener = new UpdateListener();

  efsw::WatchID watchID = fileWatcher->addWatch("command/", listener, false);

  fileWatcher->watch();

  while (true) {}

  return 0;
}