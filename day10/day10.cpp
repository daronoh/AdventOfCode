#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>

int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool outOfBounds(const std::vector<std::vector<int>>& grid, int r, int c) {
    return r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size();
}

void findTrails(std::set<std::pair<int, int>>& set, std::vector<std::vector<int>>& grid, int r, int c, int height) {
    if (height == 9) {
        set.insert({r, c});
    } else {
        for (auto dir : dirs) {
            if (!outOfBounds(grid, r + dir[0], c + dir[1]) && grid[r + dir[0]][c + dir[1]] == height + 1) {
                findTrails(set, grid, r + dir[0], c + dir[1], height + 1);
            }
        }
    }
}

int findRating(std::vector<std::vector<int>>& grid, int r, int c, int height) {
    if (height == 9) {
        return 1;
    } else {
        int res = 0;
        for (auto dir : dirs) {
            if (!outOfBounds(grid, r + dir[0], c + dir[1]) && grid[r + dir[0]][c + dir[1]] == height + 1) {
                res += findRating(grid, r + dir[0], c + dir[1], height + 1);
            }
        }
        return res;
    }
}

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int>> trailheads;
    std::vector<std::vector<int>> grid;
    std::string line;
    int r = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> gridLine;
        for (int c = 0; c < line.size(); c++) {
            if (line[c] == '0') {
                trailheads.push_back({r, c});
            }
            gridLine.push_back(line[c] - '0');
        }
        grid.push_back(gridLine);
        r++;
    }

    int res = 0;
    for (auto p : trailheads) {
        std::set<std::pair<int, int>> set;
        findTrails(set, grid, p.first, p.second, 0);
        res += set.size();
    }

    return res;
}

int part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int>> trailheads;
    std::vector<std::vector<int>> grid;
    std::string line;
    int r = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> gridLine;
        for (int c = 0; c < line.size(); c++) {
            if (line[c] == '0') {
                trailheads.push_back({r, c});
            }
            gridLine.push_back(line[c] - '0');
        }
        grid.push_back(gridLine);
        r++;
    }

    int res = 0;
    for (auto p : trailheads) {
        res += findRating(grid, p.first, p.second, 0);
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