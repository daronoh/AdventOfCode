#include <iostream>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <vector>

bool in_bounds(std::vector<std::vector<bool>>& grid, int r, int c) {
    return !(r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size());
}

bool markAntinode(std::vector<std::vector<bool>>& grid, int r, int c) {
    if (!grid[r][c]) {
        grid[r][c] = true;
        return true;
    }
    return false;
}

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<char, std::vector<std::pair<int, int>>> map;
    int r = 0;
    int width;
    while (std::getline(inputFile, line)) {
        width = line.size();
        for (int c = 0; c < line.size(); c++) {
            if (line[c] == '.') {
                continue;
            } else {
                map[line[c]].push_back({r, c});
            }
        }
        r++;
    }

    std::vector<std::vector<bool>> antinodes(r, std::vector<bool>(width, false));
    int res = 0;

    for (const auto& p : map) {
        std::vector<std::pair<int, int>> listOfPoints = p.second;
        for (int i = 0; i < listOfPoints.size(); i++) {
            for (int j = i + 1; j < listOfPoints.size(); j++) {
                auto point1 = listOfPoints[i];
                auto point2 = listOfPoints[j];
                int rDist = std::abs(point2.first - point1.first);
                int cDist = std::abs(point2.second - point1.second);
                bool firstOnLeft = point1.second - point2.second < 0;
                std::pair<int, int> newPoint1;
                std::pair<int, int> newPoint2;
                newPoint1.first = point1.first - rDist;
                newPoint1.second = firstOnLeft ? point1.second - cDist : point1.second + cDist;
                newPoint2.first = point2.first + rDist;
                newPoint2.second = firstOnLeft ? point2.second + cDist : point2.second - cDist;

                if (in_bounds(antinodes, newPoint1.first, newPoint1.second)) {
                    if (markAntinode(antinodes, newPoint1.first, newPoint1.second)) {
                        res++;
                    }
                }

                if (in_bounds(antinodes, newPoint2.first, newPoint2.second)) {
                    if (markAntinode(antinodes, newPoint2.first, newPoint2.second)) {
                        res++;
                    }
                }
            }
        }
    }

    inputFile.close();

    return res;
}

int part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<char, std::vector<std::pair<int, int>>> map;
    int r = 0;
    int width;
    while (std::getline(inputFile, line)) {
        width = line.size();
        for (int c = 0; c < line.size(); c++) {
            if (line[c] == '.') {
                continue;
            } else {
                map[line[c]].push_back({r, c});
            }
        }
        r++;
    }

    std::vector<std::vector<bool>> antinodes(r, std::vector<bool>(width, false));
    int res = 0;

    for (const auto& p : map) {
        std::vector<std::pair<int, int>> listOfPoints = p.second;
        for (int i = 0; i < listOfPoints.size(); i++) {
            for (int j = i + 1; j < listOfPoints.size(); j++) {
                auto point1 = listOfPoints[i];
                auto point2 = listOfPoints[j];
                int rDist = std::abs(point2.first - point1.first);
                int cDist = std::abs(point2.second - point1.second);
                bool firstOnLeft = point1.second - point2.second < 0;
                std::pair<int, int> newPoint1 = point1;
                std::pair<int, int> newPoint2 = point2;
                while (in_bounds(antinodes, newPoint1.first, newPoint1.second)) {
                    if (markAntinode(antinodes, newPoint1.first, newPoint1.second)) {
                        res++;
                    }
                    newPoint1.first = newPoint1.first - rDist;
                    newPoint1.second = firstOnLeft ? newPoint1.second - cDist : newPoint1.second + cDist;
                }
                
                while (in_bounds(antinodes, newPoint2.first, newPoint2.second)) {
                    if (markAntinode(antinodes, newPoint2.first, newPoint2.second)) {
                        res++;
                    }
                    newPoint2.first = newPoint2.first + rDist;
                    newPoint2.second = firstOnLeft ? newPoint2.second + cDist : newPoint2.second - cDist;
                }
            }
        }
    }

    inputFile.close();
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