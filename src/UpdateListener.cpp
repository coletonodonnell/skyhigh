#include "UpdateListener.h"
#include "Toolbox.h"
#include "FlightData.h"
#include <iostream>
#include <fstream>
#include <vector>

UpdateListener::UpdateListener() : count(0), origin(""), dest("")
{}

void UpdateListener::handleFileAction( efsw::WatchID watchid, const std::string& dir,
                           const std::string& filename, efsw::Action action,
                           std::string oldFilename ) {
      switch ( action ) {
        case efsw::Actions::Modified:
          if (filename == "selection.out" || filename == "4913")
          {
            count++;
            if (count % 3 == 0) 
            {
                std::ifstream input("/home/coleton/test/selection.out");
                std::vector<std::string> lines;
                for (std::string line; getline(input, line); )
                    lines.push_back(line);
                if (lines.size() == 3)
                {
                    if ((lines[2] == "0" && Toolbox::getInstance().getBucketSelect() == true) ||
                        (lines[2] == "1" && Toolbox::getInstance().getBucketSelect() == false))
                            Toolbox::getInstance().setBucketSelect();

                    if (lines[0] == origin && lines[1] == dest)
                        return;

                    auto connection = pqxx::connection("host=skyhigh.cxneevt5jfbi.us-east-2.rds.amazonaws.com port=5432 dbname=production user=postgres password=dPaA&3A^JUmG*^!MLX*z2&");

                    std::string message = "INSERT INTO flights VALUES";
                    if (Toolbox::getInstance().getBucketSelect())
                    {
                        if (Toolbox::getInstance().getOriginHashBuckets().find(lines[0]) != Toolbox::getInstance().getOriginHashBuckets().end() &&
                            Toolbox::getInstance().getDestHashBuckets().find(lines[1]) != Toolbox::getInstance().getDestHashBuckets().end())
                        {
                            origin = lines[0];
                            dest = lines[1];

                            std::vector<FlightData*> intersection = Toolbox::getInstance().getOriginHashBuckets()[origin]->intersection(Toolbox::getInstance().getDestHashBuckets()[dest]);
                            
                            for (FlightData* i: intersection)
                            {
                                message += "\n  (" + std::to_string(i->id) + ", " + std::to_string(static_cast<int>(i->originState)) + ", '" 
                                            + i->originLocation + "', " + std::to_string(static_cast<int>(i->destinationState)) + ", '"
                                            + i->destinationLocation + "', " + std::to_string(static_cast<int>(i->airlineCompany)) + ", "
                                            + std::to_string(i->ticketPrice) + "),";
                            }
                            message.pop_back();
                            message += ";";
                        }
                    }
                    else
                    {
                        if (Toolbox::getInstance().getOriginBTreeBuckets().find(lines[0]) != Toolbox::getInstance().getOriginBTreeBuckets().end() &&
                            Toolbox::getInstance().getDestBTreeBuckets().find(lines[1]) != Toolbox::getInstance().getDestBTreeBuckets().end())
                        {
                            origin = lines[0];
                            dest = lines[1];

                            std::vector<FlightData*> intersection = Toolbox::getInstance().getOriginBTreeBuckets()[origin]->intersection(*(Toolbox::getInstance().getDestBTreeBuckets()[dest]));
                            for (FlightData* i: intersection)
                            {
                                message += "\n  (" + std::to_string(i->id) + ", " + std::to_string(static_cast<int>(i->originState)) + ", '" 
                                            + i->originLocation + "', " + std::to_string(static_cast<int>(i->destinationState)) + ", '"
                                            + i->destinationLocation + "', " + std::to_string(static_cast<int>(i->airlineCompany)) + ", "
                                            + std::to_string(i->ticketPrice) + "),";
                            }
                            message.pop_back();
                            message += ";";
                        }
                    }
                    
                    pqxx::work work(connection);
                    pqxx::result r = work.exec("TRUNCATE flights");
                    r = work.exec(message);
                    work.commit();
                }
            }
          }
          break;
        default:
          ;
      }
    }