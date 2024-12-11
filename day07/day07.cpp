#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

bool verifyEquation(long long int sum, long long int target, const std::vector<int>& nums, int index) {
    if (index == nums.size() && sum == target) {
        return true;
    } else if (index >= nums.size()) {
        return false;
    }

    return verifyEquation(sum + nums[index], target, nums, index + 1) || verifyEquation(sum * nums[index], target, nums, index + 1);
}

bool verifyEquation2(long long int sum, long long int target, const std::vector<int>& nums, int index) {
    if (index == nums.size() && sum == target) {
        return true;
    } else if (index >= nums.size()) {
        return false;
    }

    int numOfDigits = std::log10(nums[index]) + 1;
    long long int concat = sum * std::pow(10, numOfDigits) + nums[index];

    return verifyEquation2(sum + nums[index], target, nums, index + 1) || verifyEquation2(sum * nums[index], target, nums, index + 1) || verifyEquation2(concat, target, nums, index + 1);
}

long long int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    long long int res = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        // parse the equation
        size_t colonPos = line.find(':');
        long long int target = std::stoll(line.substr(0, colonPos));
        line = line.substr(colonPos + 1);
        std::vector<int> nums;
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            nums.push_back(num);
        }

        if (verifyEquation(nums[0], target, nums, 1)) {
            res += target;
        }
    }

    return res;
}

long long int part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    long long int res = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        // parse the equation
        size_t colonPos = line.find(':');
        long long int target = std::stoll(line.substr(0, colonPos));
        line = line.substr(colonPos + 1);
        std::vector<int> nums;
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            nums.push_back(num);
        }

        if (verifyEquation2(nums[0], target, nums, 1)) {
            res += target;
        }
    }

    return res;
}

int main() {
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << part1() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2: " << part2() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    return 0;
}
