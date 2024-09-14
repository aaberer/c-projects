#ifndef BLOCK_H
#define BLOCK_H

#include <string>

std::string blockEncrypt(const std::string &data, const std::string &key);
std::string blockDecrypt(const std::string &data, const std::string &key);

#endif
