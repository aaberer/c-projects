#include "block.h"

#define BLOCK_SIZE 16
#define PADDING_BYTE 0x81

// Pad the data to ensure it is a multiple of BLOCK_SIZE
std::string padBlock(const std::string &data) {
    std::string padded = data;
    size_t padding = BLOCK_SIZE - (data.size() % BLOCK_SIZE);
    if (padding != BLOCK_SIZE) {
        padded.append(padding, PADDING_BYTE);
    }
    return padded;
}

// Encrypt or decrypt a block using XOR with the key
std::string xorWithKey(const std::string &block, const std::string &key) {
    std::string result = block;
    for (size_t i = 0; i < block.size(); ++i) {
        result[i] = block[i] ^ key[i % key.size()];
    }
    return result;
}

// Swap bytes in the block based on key
std::string swapBytes(const std::string &block, const std::string &key) {
    std::string result = block;
    size_t start = 0;
    size_t end = BLOCK_SIZE - 1;
    size_t keyIndex = 0;

    while (start < end) {
        if (key[keyIndex] % 2 == 1) {
            std::swap(result[start], result[end]);
        }
        ++start;
        --end;
        keyIndex = (keyIndex + 1) % key.size();
    }
    return result;
}

std::string blockEncrypt(const std::string &data, const std::string &key) {
    std::string paddedData = padBlock(data);
    std::string encryptedData;

    for (size_t i = 0; i < paddedData.size(); i += BLOCK_SIZE) {
        std::string block = paddedData.substr(i, BLOCK_SIZE);
        std::string xored = xorWithKey(block, key);
        encryptedData += swapBytes(xored, key);
    }

    return encryptedData;
}

std::string blockDecrypt(const std::string &data, const std::string &key) {
    std::string decryptedData;

    for (size_t i = 0; i < data.size(); i += BLOCK_SIZE) {
        std::string block = data.substr(i, BLOCK_SIZE);
        std::string swapped = swapBytes(block, key);
        decryptedData += xorWithKey(swapped, key);
    }

    // Remove padding
    decryptedData.erase(std::find(decryptedData.rbegin(), decryptedData.rend(), PADDING_BYTE).base(), decryptedData.end());

    return decryptedData;
}
