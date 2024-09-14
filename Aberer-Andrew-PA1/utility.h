#ifndef UTILITY_H
#define UTILITY_H

#include <string>

bool fileExists(const std::string &filePath);
std::string readFile(const std::string &filePath);
void writeFile(const std::string &filePath, const std::string &data);

#endif // UTILITY_H
