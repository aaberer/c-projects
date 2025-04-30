//
// Created by Andrew Aberer on 2/12/25.
//

#ifndef STATS_H
#define STATS_H

#include <fstream>
#include <vector>
#include <cmath>

void stats(const std::vector<double>& data, double& min, double& max, double& avg, double& std_dev) {
    if (data.empty()) {
        min = max = avg = std_dev = 0;
        return;
    }

    min = data[0];
    max = data[0];
    double sum = 0;

    for (const double& value : data) {
        if (value < min)
            min = value;
        if (value > max)
            max = value;
        sum += value;
    }
    avg = sum / data.size();

    double sum_sq = 0;
    for (const double& value : data) {
        double diff = value - avg;
        sum_sq += diff * diff;
    }
    std_dev = std::sqrt(sum_sq / data.size());
}

#endif //STATS_H
