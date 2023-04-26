#pragma once
#include <utility>
#include <string>

enum airlineCode { WN = 1, DL = 2, AA = 3, UA = 4, B6 = 5, AS = 6, NK = 7, G4 = 8, F9 = 9, HA = 10, SY = 11, VX = 12 };
enum regionCode { AL = 51, AK = 1, AZ = 81, AR = 71, CA = 91, CO = 82, CT = 11, DE = 31, DC = 32, FL = 33, GA = 34, GU, HI = 2, ID = 83, IL = 41, IN = 42, IA = 61, KS = 62,
                 KY = 52, LA = 72, ME = 12, MD, MA = 13, MI = 43, MN = 63, MS = 53, MO = 64, MT = 84, NE = 65, NV = 85, NH = 14, NJ = 21, NM = 86, NY = 22, NC = 36, ND = 66, MP, 
                 OH = 44, OK = 73, OR, PA = 23, PR = 3, RI = 15, SC = 37, SD = 67, TN = 54, TX = 74, TT = 5, UT = 87, VT = 16, VA = 38, VI = 4, WA = 93, WV = 39, WI = 45, WY = 88 };

class FlightData
{
    public:
        int id;                                      // ID
        regionCode originState;                      // OriginWac
        std::string originLocation;                  // Origin Airport
        regionCode destinationState;                 // DestWac
        std::string destinationLocation;             // Destination Airport
        airlineCode airlineCompany;                  // Airline Company
        float ticketPrice;                           // PricePerTicket
        
        FlightData(int id, regionCode originState, std::string originLocation, regionCode destinationState,
                   std::string destinationLocation, airlineCode airlineCompany, float ticketPrice) : id(id), originState(originState), originLocation(originLocation), 
                   destinationState(destinationState), destinationLocation(destinationLocation), airlineCompany(airlineCompany), ticketPrice(ticketPrice) {}
        int getID();
        
};