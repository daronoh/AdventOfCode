#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<int, std::vector<int>> after;

    // read first part
    while (std::getline(inputFile, line)) {
        // check if first part has ended
        if (line == "") {
            break;
        }

        std::stringstream ss(line);
        std::string left, right;
        std::getline(ss, left, '|');
        std::getline(ss, right);

        int leftInt = std::stoi(left);
        int rightInt = std::stoi(right);

        after[leftInt].push_back(rightInt);
    }

    int res = 0;
    int res2 = 0;

    // read second part
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int num;
        std::vector<int> update;
        bool isValid = true;

        while (ss >> num) {
            update.push_back(num);

            if (ss.peek() == ',') {
                ss.ignore();
            }
        }

        for (int i = 1; i < update.size(); i++) {
            auto list = after[update[i]];

            for (int j = 0; j < i; j++) {
                // update[j] cannot be in after[i]
                if (std::find(list.begin(), list.end(), update[j]) != list.end()) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) {
                break;
            }
        }

        if (isValid) {
            res += update[update.size() / 2];
        } else {
            std::sort(update.begin(), update.end(), [&after](int a, int b) {
                auto list = after[b];
                return std::find(list.begin(), list.end(), a) == list.end();
            });
            res2 += update[update.size() / 2];
        }
    }

    std::cout << res <<  "," << res2 << std::endl;

    inputFile.close();

    return 0;
}
