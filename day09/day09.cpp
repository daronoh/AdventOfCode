#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

void swap(std::vector<int>& vec, int pos1, int pos2) {
    int temp = vec[pos1];
    vec[pos1] = vec[pos2];
    vec[pos2] = temp;

    return;
}

long long int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::string line;
    bool isBlock = true;
    int id = 0;
    while (std::getline(inputFile, line)) {
        for (auto c : line) {
            int num = c - '0';
            if (isBlock) {
                for (int i = 0; i < num; i++) {
                    vec.push_back(id);
                }
                id++;
            } else {
                for (int i = 0; i < num; i++) {
                    vec.push_back(-1);
                }
            }
            isBlock = !isBlock;
        }
    }

    int left = 0; 
    int right = vec.size() - 1;
    while (true) {
        while (vec[left] != -1) {
            left++;
        }
        while (vec[right] == -1) {
            right--;
        }
        if (left >= right) {
            break;
        }
        swap(vec, left, right);
    }

    long long int res = 0;
    for (int i = 0; i <= right; i++) {
        res += vec[i] * i;
    }

    return res;
}

long long int part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int>> vec;
    std::string line;
    bool isBlock = true;
    int id = 0;
    while (std::getline(inputFile, line)) {
        for (auto c : line) {
            int num = c - '0';
            if (num == 0) {
                isBlock = !isBlock;
                continue;
            }
            
            if (isBlock) {
                vec.push_back({id, num});
                id++;
            } else {
                vec.push_back({-1, num});
            }
            isBlock = !isBlock;
        }
    }

    for (int r = vec.size() - 1; r > 0; r--) {
        if (vec[r].first == -1) {
            continue;
        }
        for (int l = 0; l < r; l++) {
            if (vec[l].first != -1) {
                continue;
            }

            if (vec[l].second >= vec[r].second) {
                if (vec[l].second == vec[r].second) {
                    vec[l].first = vec[r].first;
                } else {
                    vec[l].second -= vec[r].second;
                    vec.insert(vec.begin() + l, vec[r]); // optimization would be to not use insert, potentially by keeping track of the position of each block instead of using the vector's position
                    r++;
                }
                vec[r].first = -1;
                break;
            }
        }
    }

    long long int res = 0;
    int pos = 0;

    for (int i = 0; i < vec.size(); i++) {
        int id = vec[i].first;
        int num = vec[i].second;
        
        if (id != -1) {
            // Calculate the sum directly instead of looping
            long long int sum = num * (2 * pos + num - 1) / 2;
            res += id * sum;
            pos += num;
        } else {
            pos += num;
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