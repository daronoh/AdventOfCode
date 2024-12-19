#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

struct robot {
    int pX, pY, vX, vY;

    robot(int startX, int startY, int startVX, int startVY) : pX(startX), pY(startY), vX(startVX), vY(startVY) {}

    void move() {
        int newX = pX + vX;
        int newY = pY + vY;
        if (newX < 0) {
            newX = 101 + newX;
        } else if (newX > 100) {
            newX -= 101;
        }

        if (newY < 0) {
            newY = 103 + newY;
        } else if (newY > 102) {
            newY -= 103;
        }

        pX = newX;
        pY = newY;
    }
};

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<robot> robots;
    while (std::getline(inputFile, line)) {
        int pX, pY, vX, vY;
        auto p_pos = line.find("p=");
        auto v_pos = line.find("v=");
        std::string p_str = line.substr(p_pos + 2, v_pos - p_pos - 3);
        std::string v_str = line.substr(v_pos + 2);
        std::stringstream p_stream(p_str), v_stream(v_str);

        char comma;
        p_stream >> pX >> comma >> pY;
        v_stream >> vX >> comma >> vY;

        robots.emplace_back(pX, pY, vX, vY);
    }

    for (int i = 0; i < 100; i++) {
        for (auto& r : robots) {
            r.move();
        }
    }

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;
    for (auto& r : robots) {
        if (r.pX >= 0 && r.pX < 50 && r.pY >= 0 && r.pY < 51) {
            q1++;
        } else if (r.pX >= 51 && r.pX < 101 && r.pY >= 0 && r.pY < 51) {
            q2++;
        } else if (r.pX >= 0 && r.pX < 50 && r.pY >= 52 && r.pY < 103) {
            q3++;
        } else if (r.pX >= 51 && r.pX <101 && r.pY >= 52 && r.pY <103) {
            q4++;
        }
    }

    return q1 * q2 * q3 * q4;
}

void part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return;
    }

    std::string line;
    std::vector<robot> robots;
    while (std::getline(inputFile, line)) {
        int pX, pY, vX, vY;
        auto p_pos = line.find("p=");
        auto v_pos = line.find("v=");
        std::string p_str = line.substr(p_pos + 2, v_pos - p_pos - 3);
        std::string v_str = line.substr(v_pos + 2);
        std::stringstream p_stream(p_str), v_stream(v_str);

        char comma;
        p_stream >> pX >> comma >> pY;
        v_stream >> vX >> comma >> vY;

        robots.emplace_back(pX, pY, vX, vY);
    }

    for (int i = 0; i < 10000; i++) {
        std::set<std::pair<int,int>> next_set;
        std::set<std::pair<int,int>> matching;
        for (auto& r : robots) {
            r.move();
            if (next_set.find({r.pX, r.pY}) != next_set.end()) {
                matching.insert({r.pX, r.pY});
            }
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    next_set.insert({r.pX + i, r.pY + j});
                }
            }
        }

        if (matching.size() > 256) {
            std::cout << i + 1 << std::endl;
            for (int i = 0; i < 103; i++) {
                for (int j = 0; j < 101; j++) {
                    if(matching.find({j, i}) != matching.end()) {
                        std::cout << "*";
                    } else {
                        std::cout << ".";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}

int main() {
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << part1() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    t_begin = std::chrono::high_resolution_clock::now();
    part2();
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    return 0;
}
