//
// Created by Andrew Aberer on 4/16/25.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <climits>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int waitingTime;
    int completionTime;
};

std::vector<Process> readProcesses(const std::string& filename) {
    std::vector<Process> procs;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return procs;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Process p;
        std::getline(ss, token, ','); p.id = std::stoi(token);
        std::getline(ss, token, ','); p.arrivalTime = std::stoi(token);
        std::getline(ss, token, ','); p.burstTime = std::stoi(token);
        std::getline(ss, token, ','); p.priority = std::stoi(token);
        p.remainingTime = p.burstTime;
        p.waitingTime = 0;
        p.completionTime = 0;
        procs.push_back(p);
    }
    file.close();
    return procs;
}

void fcfs(std::vector<Process>& procs) {
    std::sort(procs.begin(), procs.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    int currentTime = 0;
    for (auto& p : procs) {
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        p.waitingTime = currentTime - p.arrivalTime;
        currentTime += p.burstTime;
        p.completionTime = currentTime;
    }
}

void sjfPreemptive(std::vector<Process>& procs) {
    int n = procs.size();
    int completed = 0;
    int currentTime = 0;
    std::vector<int> completionTimes(n, 0);
    
    std::vector<int> remainingBurst(n);
    for (int i = 0; i < n; ++i) {
        remainingBurst[i] = procs[i].burstTime;
    }
    
    int minArrival = INT_MAX;
    for (const auto& p : procs) {
        minArrival = std::min(minArrival, p.arrivalTime);
    }
    currentTime = minArrival;
    
    while (completed < n) {
        int idx = -1;
        int shortest = INT_MAX;
        
        for (int i = 0; i < n; ++i) {
            if (procs[i].arrivalTime <= currentTime && 
                remainingBurst[i] > 0 && 
                remainingBurst[i] < shortest) {
                shortest = remainingBurst[i];
                idx = i;
            }
        }
        
        if (idx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (procs[i].arrivalTime > currentTime && procs[i].arrivalTime < nextArrival && remainingBurst[i] > 0) {
                    nextArrival = procs[i].arrivalTime;
                }
            }
            currentTime = (nextArrival == INT_MAX) ? currentTime + 1 : nextArrival;
            continue;
        }
        
        remainingBurst[idx]--;
        currentTime++;
        
        if (remainingBurst[idx] == 0) {
            completed++;
            completionTimes[idx] = currentTime;
            
            procs[idx].completionTime = currentTime;
            procs[idx].waitingTime = currentTime - procs[idx].arrivalTime - procs[idx].burstTime;
            if (procs[idx].waitingTime < 0) {
                procs[idx].waitingTime = 0;
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        procs[i].remainingTime = 0;
    }
    
    std::sort(procs.begin(), procs.end(), [](const Process& a, const Process& b) {
        return a.completionTime < b.completionTime;
    });
}

void priorityPreemptive(std::vector<Process>& procs) {
    int n = procs.size();
    int completed = 0;
    int currentTime = 0;
    std::vector<int> completionTimes(n, 0);
    
    std::vector<int> remainingBurst(n);
    for (int i = 0; i < n; ++i) {
        remainingBurst[i] = procs[i].burstTime;
    }
    
    int minArrival = INT_MAX;
    for (const auto& p : procs) {
        minArrival = std::min(minArrival, p.arrivalTime);
    }
    currentTime = minArrival;
    
    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;
        
        for (int i = 0; i < n; ++i) {
            if (procs[i].arrivalTime <= currentTime && remainingBurst[i] > 0) {
                if (procs[i].priority < highestPriority ||
                    (procs[i].priority == highestPriority && remainingBurst[i] < remainingBurst[idx])) {
                    highestPriority = procs[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (procs[i].arrivalTime > currentTime && procs[i].arrivalTime < nextArrival && remainingBurst[i] > 0) {
                    nextArrival = procs[i].arrivalTime;
                }
            }
            currentTime = (nextArrival == INT_MAX) ? currentTime + 1 : nextArrival;
            continue;
        }
        
        remainingBurst[idx]--;
        currentTime++;
        
        if (remainingBurst[idx] == 0) {
            completed++;
            completionTimes[idx] = currentTime;
            
            procs[idx].completionTime = currentTime;
            procs[idx].waitingTime = currentTime - procs[idx].arrivalTime - procs[idx].burstTime;
            if (procs[idx].waitingTime < 0) {
                procs[idx].waitingTime = 0;
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        procs[i].remainingTime = 0;
    }
    
    std::sort(procs.begin(), procs.end(), [](const Process& a, const Process& b) {
        return a.completionTime < b.completionTime;
    });
}

double calcAvgTurnaround(const std::vector<Process>& procs) {
    double sum = 0;
    for (auto& p : procs) {
        sum += (p.completionTime - p.arrivalTime);
    }
    return sum / procs.size();
}

double calcAvgWaiting(const std::vector<Process>& procs) {
    double sum = 0;
    for (auto& p : procs) {
        sum += p.waitingTime;
    }
    return sum / procs.size();
}

double calcThroughput(const std::vector<Process>& procs) {
    if (procs.empty()) return 0;
    int start = procs.front().arrivalTime;
    int end = procs.back().completionTime;
    return procs.size() / static_cast<double>(end - start + 1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./Scheduler <input_filename>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    auto original = readProcesses(filename);

    auto fcfsList = original;
    fcfs(fcfsList);
    std::cout << "--- FCFS ---" << std::endl;
    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(3)
              << calcAvgTurnaround(fcfsList) << std::endl;
    std::cout << "Average Waiting Time: " << calcAvgWaiting(fcfsList) << std::endl;
    std::cout << "Throughput: " << calcThroughput(fcfsList) << std::endl
              << std::endl;

    auto sjfList = original;
    sjfPreemptive(sjfList);
    std::cout << "--- SJFP ---" << std::endl;
    std::cout << "Average Turnaround Time: " << calcAvgTurnaround(sjfList) << std::endl;
    std::cout << "Average Waiting Time: " << calcAvgWaiting(sjfList) << std::endl;
    std::cout << "Throughput: " << calcThroughput(sjfList) << std::endl
              << std::endl;

    auto prioList = original;
    priorityPreemptive(prioList);
    std::cout << "--- Priority ---" << std::endl;
    std::cout << "Average Turnaround Time: " << calcAvgTurnaround(prioList) << std::endl;
    std::cout << "Average Waiting Time: " << calcAvgWaiting(prioList) << std::endl;
    std::cout << "Throughput: " << calcThroughput(prioList) << std::endl;

    return 0;
}
