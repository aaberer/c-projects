//
// Created by Andrew Aberer on 2/12/25.
//

#include "stats.h"

#include <fstream>
#include <vector>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 3){return 1;}
    const char* output_file = argv[argc - 1];
    std::ofstream ofs(output_file);
    if (!ofs.is_open()){return 1;}

    for (int i = 1; i < argc - 1; ++i) {
        const char* input_file = argv[i];
        std::ifstream ifs(input_file);
        if (!ifs.is_open()){ continue;}

        std::vector<double> data;
        double value;
        while (ifs >> value) {
            data.push_back(value);
        }
        ifs.close();

        double min, max, avg, std_dev;
        stats(data, min, max, avg, std_dev);

        ofs << min << "," << max << "," << avg << "," << std_dev << "\n";
    }
    ofs.close();
    return 0;
}