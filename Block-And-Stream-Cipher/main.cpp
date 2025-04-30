#include <iostream>
#include <fstream>
#include <string>
#include "block.h"
#include "stream.h"
#include "utility.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: ./cipher <B/S> <input file> <output file> <key file> <E/D>" << std::endl;
        return 1;
    }

    char cipherType = argv[1][0];
    std::string inputFilePath = argv[2];
    std::string outputFilePath = argv[3];
    std::string keyFilePath = argv[4];
    char mode = argv[5][0];

    if (cipherType != 'B' && cipherType != 'S') {
        std::cerr << "Invalid Function Type" << std::endl;
        return 1;
    }

    if (!fileExists(inputFilePath)) {
        std::cerr << "Input File Does Not Exist" << std::endl;
        return 1;
    }

    if (!fileExists(keyFilePath)) {
        std::cerr << "Key File Does Not Exist" << std::endl;
        return 1;
    }

    if (mode != 'E' && mode != 'D') {
        std::cerr << "Invalid Mode Type" << std::endl;
        return 1;
    }

    std::string key = readFile(keyFilePath);
    std::string inputData = readFile(inputFilePath);

    std::string outputData;

    if (cipherType == 'B') {
        if (mode == 'E') {
            outputData = blockEncrypt(inputData, key);
        } else {
            outputData = blockDecrypt(inputData, key);
        }
    } else {
        if (mode == 'E') {
            outputData = streamEncrypt(inputData, key);
        } else {
            outputData = streamDecrypt(inputData, key);
        }
    }

    writeFile(outputFilePath, outputData);

    return 0;
}
