#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <unordered_map>

long long int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line; 
    getline(inputFile, line);
    std::stringstream ss(line);
    long long int stone;
    std::unordered_map<long long int, long long int> stones;
    while (ss >> stone) {
        stones[stone]++;
    }

    for (int i = 0; i < 25; i++) {
        std::unordered_map<long long int, long long int> temp;
        for (auto p : stones) {
            long long int value = p.first;
            long long int count = p.second;
            if (value == 0) {
                temp[1] += count;
            } else if (std::to_string(value).size() % 2 == 0) {
                std::string stoneStr = std::to_string(value);
                long long int mid = stoneStr.size() / 2;
                std::string substr1 = stoneStr.substr(0, mid);
                std::string substr2 = stoneStr.substr(mid);
                long long int left = std::stoi(substr1);
                long long int right = std::stoi(substr2);
                temp[left] += count;
                temp[right] += count;
            } else {
                temp[value * 2024] += count;
            }
        }
        stones = temp;
    }

    long long int res = 0;
    for (auto p : stones) {
        res += p.second;
    }

    return res;
}

long long int part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line; 
    getline(inputFile, line);
    std::stringstream ss(line);
    long long int stone;
    std::unordered_map<long long int, long long int> stones;
    while (ss >> stone) {
        stones[stone]++;
    }

    for (int i = 0; i < 75; i++) {
        std::unordered_map<long long int, long long int> temp;
        for (auto p : stones) {
            long long int value = p.first;
            long long int count = p.second;
            if (value == 0) {
                temp[1] += count;
            } else if (std::to_string(value).size() % 2 == 0) {
                std::string stoneStr = std::to_string(value);
                long long int mid = stoneStr.size() / 2;
                std::string substr1 = stoneStr.substr(0, mid);
                std::string substr2 = stoneStr.substr(mid);
                long long int left = std::stoi(substr1);
                long long int right = std::stoi(substr2);
                temp[left] += count;
                temp[right] += count;
            } else {
                temp[value * 2024] += count;
            }
        }
        stones = temp;
    }

    long long int res = 0;
    for (auto p : stones) {
        res += p.second;
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