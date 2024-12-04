#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

bool checkReport(const std::vector<int>& report) {
    int prev = report[0];
    bool isAscending = prev < report[1];
    for (int i = 1; i < report.size(); i++) {
        if ((isAscending && report[i] < prev) || (!isAscending && report[i] > prev) || (std::abs(report[i] - prev) > 3) || (std::abs(report[i] - prev) < 1)) {
            return false;
        } else {
            prev = report[i];
        }
    }
    return true;
}

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> data;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::vector<int> report;

        int level;
        while (ss >> level) {
            report.push_back(level);
        }

        data.push_back(report);
    }

    inputFile.close();

    // part 1
    int res = 0;

    for (int i = 0; i < data.size(); i++) {
        if (checkReport(data[i])) {
            res ++;
        }
    }

    std::cout << res << std::endl;

    // part 2
    int res2 = 0;


    for (int i = 0; i < data.size(); i++) {
        if (checkReport(data[i])) {
            res2++;
        } else {
            for (int j = 0; j < data[i].size(); j++) {
                std::vector<int> alteredReport = data[i];
                alteredReport.erase(alteredReport.begin() + j);

                if (checkReport(alteredReport)) {
                    res2++;
                    break;
                }
            }
        }
    }

    std::cout << res2 << std::endl;

    return 0;
}
