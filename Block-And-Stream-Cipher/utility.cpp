#include "utility.h"
#include <fstream>
#include <sstream>

bool fileExists(const std::string &filePath) {
    std::ifstream file(filePath);
    return file.good();
}

std::string readFile(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const std::string &filePath, const std::string &data) {
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
}
