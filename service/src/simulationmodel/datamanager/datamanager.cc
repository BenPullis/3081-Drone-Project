

#include "Datamanager.h"

#include "SimulationModel.h"

DataManager::DataManager() {
  // private
}

DataManager *DataManager::getInstance() { // singleton design pattern
  if (instance == nullptr) {
    // make a new instance
  }
  static DataManager *instance;
  return instance; // make sure get instance has to be static const, or just
                   // static
                   // check if instance is
}

// DataManager::query() {} relic from refactoring.guru

void DataManager::update(double dt, IEntity *entity) {
  // Update logic for DataManager
  // This function will call AddDataEntry
  counter++;
  // do not do that

  // complete every update first. AND THEN after time ticks, then export a line
  // to a csv :DDDD
  if (counter >= 1000) {
    counter = 0;
    AddDataEntry(entity);
  } // almost want to:
  /**
  make it into a map
  key would be entity
  value as a vector or array or whatever. maybe
  drone, speed: 10 distance:10 timesPastKellerHall:10, color, name,
  store it as a vector or struct


  //data structures within data structures

  just update it if not in map
  */

  // Update logic for DataManager
  // This function will call AddDataEntry
  // counter++;

  // if (counter >= 1000) {
  //   counter = 0;
  //   for (auto entity : VectorEntities) {
  //     AddDataEntry(entity);
  //   }
  // } // almost want to:
  /**
  make it into a map
  key would be entityß
  value as a vector or array or whatever. maybe
  drone, speed: 10 distance:10 timesPastKellerHall:10, color, name,
  store it as a vector or struct

  //data structures within data structures

  just update it if not in map
  */
}

void DataManager::AddDataEntry(IEntity *entity) {
  DataEntry entry;
  entry.timestamp = std::chrono::system_clock::now();
  // entry.location = location;
  dataEntries.push_back(entry);
}

void DataManager::addToDataManager(IEntity *entity) {
  VectorEntities.push_back(entity);
  // map to a vector of strings
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
