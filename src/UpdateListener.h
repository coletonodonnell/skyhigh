#pragma once
#include <efsw/efsw.hpp>
#include <pqxx/pqxx>
#include <string>

class UpdateListener : public efsw::FileWatchListener {
  private:
    int count;
    std::string origin;
    std::string dest;

  public:
    UpdateListener();
    void handleFileAction(efsw::WatchID watchid, const std::string& dir,
                          const std::string& filename, efsw::Action action,
                          std::string oldFilename) override;
};