#include "datam.h"

Datam::Datam() : running(true) {
  updateThread = std::thread(&Datam::updateLoop, this);
}

// Note. I tried to use POSIX syscalls for open and read, but rthat was painful
// ill just use fopen whatevsies
// this function implements business logic to export data to a CSV file
void Datam::update() {

  for (auto it = dataEntries.begin(); it != dataEntries.end();) {
    if (it->first == nullptr) {
      it = dataEntries.erase(it);
    } else {
      ++it;
    }
  }

  // now, update the dataEntries
  if (toggledOn) {

    appendToFile();
    newDataEntries();
  }
}

void Datam::appendToFile() {
  std::string filename = "ExportedCSV.csv";
  // if file exists but counter is -1, delete the file
  // if (counter == -1) {
  //   std::remove(filename.c_str());
  //   std::cout << "Debug, deleted the old log!\n";
  // }
  FILE *file = fopen(filename.c_str(), "a");
  if (!file) {
    std::cerr << "Couldnt' open file: " << filename << "\n";
    return;
  }

  // write the data to the file. Help from ChatGPT and Stack Overflow on how to
  // iterate through a map
  for (const auto &entry : dataEntries) {
    fprintf(file, "%s,%f,%f,%f,%ld\n", entry.second.name.c_str(),
            entry.second.position.x, entry.second.position.y,
            entry.second.position.z,
            std::chrono::system_clock::to_time_t(entry.second.timestamp));
  }

  fclose(file);
}

void Datam::newDataEntries() {
  // this function will be called after the old data was appended to the file,
  // we now update the dataEntries
  for (auto &pair : dataEntries) {
    IEntity *entity = pair.first;
    entry &data = pair.second;

    if (entity) {
      // Update the entry with new data from the entity
      data.position =
          entity->getPosition(); // Assuming IEntity has getPosition()
      data.timestamp = std::chrono::system_clock::now(); // Update the timestamp

    } else {
      std::cerr << "null entity wasnt deleted uh oh\n";
    }
  }
}

Datam *Datam::getInstance() {
  if (instance == nullptr) {
    instance = new Datam();
  }

  return instance;
}

// adapted code from WeatherSystem
void Datam::updateLoop() {
  while (running) {
    update();
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }
}

void Datam::stop() {
  running = false;
  if (updateThread.joinable()) {
    updateThread.join();
  }
}

// call the update function when destroying object
Datam::~Datam() {
  update();
  stop();
  // no need to delete singleton or data, nothing declared on the heap
}

int Datam::publicUpdate(IEntity *entity) {
  if (!entity) {
    std::cerr << "this entity is null or doesnt make sense\n";
    return -1;
  }
  // add entity to the map dataEntries
  auto it = dataEntries.find(entity);
  if (it == dataEntries.end()) {
    entry newEntry;
    newEntry.name = entity->getName();
    newEntry.position = entity->getPosition();
    newEntry.timestamp = std::chrono::system_clock::now();
    dataEntries[entity] = newEntry;
    // continue;
  }

  // after adding, update all the data
  return 0;
}

void Datam::toggleUpdate() { toggledOn = !toggledOn; }

Datam *Datam::instance = nullptr;