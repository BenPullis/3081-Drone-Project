#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

// #include "IObserver.h"
// #include "IPublisher.h"

// remember to cite!
#include "IEntity.h"
#include "math/vector3.h"
#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class DataManager : public IEntity {
public:
  // struct DataEntry {
  //   std::chrono::system_clock::time_point timestamp;
  //   std::string location;
  //   std::chrono::system_clock::time_point creationTime;
  // };

  void update(double dt, IEntity *entity);

  void AddDataEntry(const std::string &location);
  // const std::vector<DataEntry> &GetDataEntries() const;

  void addToDataManager(IEntity *entity);

  // struct DataEntry {
  //   std::vector<Vector3> onion_position;
  //   std::chrono::system_clock::time_point timestamp;
  //   std::string name;
  // };

  static DataManager *getInstance();

protected:
  ~DataManager();

private:
  DataManager();
  std::vector<DataEntry> dataEntries;
  std::vector<IEntity *> VectorEntities;
  // Datamanager *instance = NULL;

  struct DataEntry {
    std::vector<Vector3> onion_position; // lets get it from ye
    std::string colour;
    std::chrono::system_clock::time_point timestamp;
    std::string name;
    // in the future maybe lets do something like durability?
  };
  int yesCSV = 0;
  int yesJSON = 0;
  int counter = 0;
};

#endif // DATA_MANAGER_H_