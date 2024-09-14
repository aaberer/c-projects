#ifndef STREAM_H
#define STREAM_H

#include <string>

std::string streamEncrypt(const std::string &data, const std::string &key);
std::string streamDecrypt(const std::string &data, const std::string &key);

#endif