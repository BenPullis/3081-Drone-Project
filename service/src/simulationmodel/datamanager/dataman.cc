

#include "Dataman.h"

#include "SimulationModel.h"

DataManager::DataManager() {
  // private
}

DataManager *DataManager::getInstance() { // singleton design pattern
  static DataManager *instance;
  return instance;
}

// DataManager::query() {} relic from refactoring.guru

void DataManager::AddDataEntry(const std::string &location) {
  DataEntry entry;
  entry.timestamp = std::chrono::system_clock::now();
  // entry.location = location;
  dataEntries.push_back(entry);
}

DataManager::~DataManager() {
  if (yesCSV) {
    // call the CSV function to create
  }
  if (yesJSON) {
    // call the JSON function to create
  } else {
    delete this;
  }
}
