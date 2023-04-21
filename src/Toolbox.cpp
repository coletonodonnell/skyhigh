#include "Toolbox.h"
#include <set>

Toolbox::Toolbox()
{
    // Airlines
    airlines["WN"] = 1;
    airlines["DL"] = 2;
    airlines["AA"] = 3;
    airlines["UA"] = 4;
    airlines["B6"] = 5;
    airlines["AS"] = 6;
    airlines["NK"] = 7;
    airlines["G4"] = 8;
    airlines["F9"] = 9;
    airlines["HA"] = 10;
    airlines["SY"] = 11;
    airlines["VX"] = 12;

    std::set<std::string> state({"ABQ", "ANC", "ATL", "AUS", "BDL", "BHM", "BNA", "BOS", "BUF", "BUR", "BWI", "CHS", "CLE", "CLT", "CMH", "CVG", "DAL", "DCA", "DEN", "DFW", "DTW", "ELP", "ECP", "EWR", 
    "FLL", "HNL", "HOU", "IAD", "IAH", "IND", "JAX", "JFK", "LAS", "LAX", "LGA", "LIT", "MCI", "MCO", "MDW", "MEM", "MIA", "MKE", "MSP", "MSY", "OAK", "OGG", "OKC", "OMA", "ONT", "ORD", 
    "ORF", "PBI", "PDX", "PHL", "PHX", "PIT", "PVD", "RDU", "RIC", "RNO", "RSW", "SAN", "SAT", "SDF", "SEA", "SFO", "SJC", "SJU", "SLC", "SMF", "SNA", "STL", "TPA", "TUL", "TUS", "ABE", 
    "ABI", "ABR", "ABY", "ACK", "ACT", "ACV", "ACY", "ADK", "ADQ", "AEX", "AGS", "AKN", "ALB", "ALO", "AMA", "APN", "ART", "ASE", "ATW", "AVL", "AVP", "AZO", "BET", "BFL", "BGM", "BGR", 
    "BIL", "BIS", "BJI", "BLI", "BMI", "BOI", "BPT", "BQK", "BQN", "BRD", "BRO", "BRW", "BTM", "BTR", "BTV", "BZN", "CAE", "CAK", "CDC", "CDV", "CEC", "CHA", "CHO", "CIC", "CID", "CIU", 
    "CLD", "CLL", "CMI", "CMX", "CNY", "COD", "COS", "COU", "CPR", "CRP", "CRW", "CSG", "CWA", "CYS", "DAB", "DAY", "DBQ", "DHN", "DIK", "DLG", "DLH", "DRO", "DRT", "DSM", "DVL", "EAU", 
    "EGE", "EKO", "ELM", "ERI", "ESC", "EUG", "EVV", "EWN", "EYW", "FAI", "FAR", "FAT", "FAY", "FCA", "FLG", "FLO", "FNT", "FOE", "FSD", "FSM", "FWA", "GCC", "GCK", "GEG", "GFK", "GGG", 
    "GJT", "GNV", "GPT", "GRB", "GRI", "GRK", "GRR", "GSO", "GSP", "GST", "GTF", "GTR", "GUC", "GUM", "HDN", "HIB", "HLN", "HOB", "HPN", "HRL", "HSV", "HTS", "HYA", "HYS", "ICT", "IDA", 
    "ILG", "ILM", "IMT", "INL", "IPL", "ISN", "ISP", "ITH", "ITO", "IYK", "JAC", "JAN", "JLN", "JMS", "JNU", "KOA", "KTN", "LAN", "LAR", "LAW", "LBB", "LCH", "LEX", "LFT", "LGB", "LIH", 
    "LMT", "LNK", "LRD", "LSE", "LWB", "LWS", "LYH", "MAF", "MBS", "MCN", "MDT", "MEI", "MFE", "MFR", "MGM", "MHK", "MHT", "MKG", "MLB", "MLI", "MLU", "MMH", "MOB", "MOD", "MOT", "MQT", 
    "MRY", "MSN", "MSO", "MTJ", "MVY", "MWH", "MYR", "OAJ", "OME", "ORH", "OTH", "OTZ", "OXR", "PAH", "PFN", "PHF", "PIA", "PIB", "PIE", "PIH", "PIR", "PLN", "PNS", "PPG", "PSC", "PSE", 
    "PSG", "PSP", "PUB", "PWM", "RAP", "RDD", "RDM", "RFD", "RHI", "RKS", "ROA", "ROC", "ROW", "RST", "SAF", "SAV", "SBA", "SBN", "SBP", "SCC", "SCE", "SGF", "SGU", "SHD", "SHV", "SIT", 
    "SJT", "SMX", "SPI", "SPN", "SPS", "SRQ", "STC", "STT", "STX", "SUN", "SUX", "SWF", "SYR", "TEX", "TLH", "TOL", "TRI", "TTN", "TUP", "TVC", "TWF", "TXK", "TYR", "TYS", "VEL", "VLD", 
    "VPS", "WRG", "WYS", "XNA", "YAK", "YUM"});

    for (auto i: state)
    {
        originBTreeBuckets[i] = new BTreeSet();
        destBTreeBuckets[i] = new BTreeSet();
        originHashBuckets[i] = new HashSet(1400);
        destHashBuckets[i] = new HashSet(1400);
    }

    bucketSelect = true;
}

Toolbox::~Toolbox()
{
    for (auto i = originBTreeBuckets.begin(); i != originBTreeBuckets.end(); i++)
        delete i->second;
    for (auto i = destBTreeBuckets.begin(); i != destBTreeBuckets.end(); i++)
        delete i->second;
    for (auto i = originHashBuckets.begin(); i != originHashBuckets.end(); i++)
        delete i->second;
    for (auto i = destHashBuckets.begin(); i != destHashBuckets.end(); i++)
        delete i->second;
}

std::map<std::string, int>& Toolbox::getAirlines()
{
    return airlines;
}

std::map<std::string, BTreeSet*>& Toolbox::getOriginBTreeBuckets()
{
    return originBTreeBuckets;
}

std::map<std::string, HashSet*>& Toolbox::getOriginHashBuckets()
{
    return originHashBuckets;
}

std::map<std::string, BTreeSet*>& Toolbox::getDestBTreeBuckets()
{
    return destBTreeBuckets;
}

std::map<std::string, HashSet*>& Toolbox::getDestHashBuckets()
{
    return destHashBuckets;
}

bool Toolbox::getBucketSelect()
{
    return bucketSelect;
}

void Toolbox::setBucketSelect()
{
    bucketSelect = !bucketSelect;
}

Toolbox& Toolbox::getInstance()
{
    static Toolbox tb;
    return tb;
}