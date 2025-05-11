#include <fstream>
#include <string>
#include <vector>

// help from TAs, chatgpt, etc, stackoverflow omg

class ExportCSV {
public:
  void ExportCSV(const std::vector<std::string> &dataEntries) {
    // ExportedCSV.csv
    std::ofstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Couldnt' open file: "
    }

    for (const auto &line : data) {
      file << line << "\n";
    }

    file.close();
  }
};