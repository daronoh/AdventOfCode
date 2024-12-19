#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int costOfPrize(int matrix[2][2], int target[2]) {
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if (det == 0) {
        return -1;  // No solution if determinant is zero
    }
    float x = (static_cast<float>(matrix[1][1]) * target[0] - static_cast<float>(matrix[0][1]) * target[1]) / det;
    float y = (static_cast<float>(-matrix[1][0]) * target[0] + static_cast<float>(matrix[0][0]) * target[1]) / det;
    if (std::fmod(x, 1.0) == 0.0 && std::fmod(y, 1.0) == 0.0) {
        return 3 * x + y;
    } else {
        return -1;
    }
}

long long int costOfPrize(int matrix[2][2], long long int target[2]) {
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if (det == 0) {
        return -1;  // No solution if determinant is zero
    }
    double x = (static_cast<double>(matrix[1][1]) * target[0] - static_cast<double>(matrix[0][1]) * target[1]) / det;
    double y = (static_cast<double>(-matrix[1][0]) * target[0] + static_cast<double>(matrix[0][0]) * target[1]) / det;
    if (std::fmod(x, 1.0) == 0.0 && std::fmod(y, 1.0) == 0.0) {
        return 3 * x + y;
    } else {
        return -1;
    }
}

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    int matrix[2][2];
    int target[2];
    int res = 0;
    while(getline(inputFile, line)) {
        if (line.find("Button A") != std::string::npos) {
            auto posX = line.find("X+");
            auto posY = line.find("Y+");
            matrix[0][0] = std::stoi(line.substr(posX + 2, posY - posX - 3));
            matrix[1][0] = std::stoi(line.substr(posY + 2));
        } else if (line.find("Button B") != std::string::npos) {
            auto posX = line.find("X+");
            auto posY = line.find("Y+");
            matrix[0][1] = std::stoi(line.substr(posX + 2, posY - posX - 3));
            matrix[1][1] = std::stoi(line.substr(posY + 2));
        } else if (line.find("Prize") != std::string::npos) {
            auto posX = line.find("X=");
            auto posY = line.find("Y=");
            target[0] = std::stoi(line.substr(posX + 2, posY - posX - 3));
            target[1] = std::stoi(line.substr(posY + 2));

            int calc = costOfPrize(matrix, target);

            if (calc != -1) {
                res += calc;
            }
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

    std::string line;
    int matrix[2][2];
    long long int target[2];
    long long int res = 0;
    while(getline(inputFile, line)) {
        if (line.find("Button A") != std::string::npos) {
            auto posX = line.find("X+");
            auto posY = line.find("Y+");
            matrix[0][0] = std::stoi(line.substr(posX + 2, posY - posX - 3));
            matrix[1][0] = std::stoi(line.substr(posY + 2));
        } else if (line.find("Button B") != std::string::npos) {
            auto posX = line.find("X+");
            auto posY = line.find("Y+");
            matrix[0][1] = std::stoi(line.substr(posX + 2, posY - posX - 3));
            matrix[1][1] = std::stoi(line.substr(posY + 2));
        } else if (line.find("Prize") != std::string::npos) {
            auto posX = line.find("X=");
            auto posY = line.find("Y=");
            target[0] = std::stoi(line.substr(posX + 2, posY - posX - 3)) + 10000000000000;
            target[1] = std::stoi(line.substr(posY + 2)) + 10000000000000;
            long long int calc = costOfPrize(matrix, target);

            if (calc != -1) {
                res += calc;
            }
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