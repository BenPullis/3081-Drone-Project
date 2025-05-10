#include <fstream>
#include <string>
#include <vector>

// help from TAs, chatgpt, etc, stackoverflow omg

class ExportCSV {
public:
  void Update(const std::vector<std::string> &data,
              const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Unable to open file: " + filename);
    }

    for (const auto &line : data) {
      file << line << "\n";
    }

    file.close();
  }
};