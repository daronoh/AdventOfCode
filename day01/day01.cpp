#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

int main() {


    // read file
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<int> leftList;
    std::vector<int> rightList;
    std::unordered_map<int, int> map;

    int left, right;
    std::string line;

    while(std::getline(inputFile, line)) {
        std::stringstream ss(line);

        ss >> left >> right;

        leftList.push_back(left);
        rightList.push_back(right);

        map[left] = 0;
    }

    inputFile.close();

    // part 1
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    long long res = 0;

    for (int i = 0; i < leftList.size(); i++) {
        res += std::abs(leftList[i] - rightList[i]);
    }

    std::cout << res << std::endl;

    // part 2
    long long res2 = 0;

    for (int s : rightList)  {
        if (map.find(s) != map.end()) {
            map[s]++;
        }
    }

    for (const auto& pair : map) {
        res2 += pair.first * pair.second;
    }

    std::cout << res2 << std::endl;

    return 0;
}
