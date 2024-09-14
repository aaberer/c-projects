#include "stream.h"

std::string streamEncrypt(const std::string &data, const std::string &key) {
    std::string result = data;
    size_t keyLength = key.size();

    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % keyLength];
    }

    return result;
}

std::string streamDecrypt(const std::string &data, const std::string &key) { // decrypt = encrypt
    return streamEncrypt(data, key);
}
