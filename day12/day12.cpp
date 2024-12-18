#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int dirs[4][2] = {{-1, 0}, // up
                    {0, 1}, // right
                    {1, 0}, // down
                    {0, -1}}; // left

bool inBound(const std::vector<std::string>& grid, int r, int c) {
    return !(r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size());
}

void calcRegion(std::vector<std::string>& grid, std::vector<std::vector<bool>>& visited, int r, int c, char curr, std::pair<int, int>& res) {
    if (visited[r][c]) {
        return;
    }

    res.first += 1;
    visited[r][c] = true;

    for (auto dir : dirs) {
        int newR = r + dir[0];
        int newC = c + dir[1];
        if (!inBound(grid, newR, newC) || grid[newR][newC] != curr) {
            res.second += 1;
        } else if (!visited[newR][newC]){
            calcRegion(grid, visited, newR, newC, curr, res);
        }
    }
}

void calcRegion2(std::vector<std::string>& grid, std::vector<std::vector<bool>>& visited, int r, int c, char curr, std::pair<int, int>& res) {
    if (visited[r][c]) {
        return;
    }

    res.first += 1;
    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
        int r1 = r + dirs[i][0] + dirs[i == 0 ? 3 : i - 1][0];
        int r2 = r + dirs[i][0];
        int r3 = r + dirs[i == 0 ? 3 : i - 1][0];
        int c1 = c + dirs[i][1] + dirs[i == 0 ? 3 : i - 1][1];
        int c2 = c + dirs[i][1];
        int c3 = c + dirs[i == 0 ? 3 : i - 1][1];
        if ((!inBound(grid, r2, c2) || grid[r2][c2] != curr) && 
        (!inBound(grid, r3, c3) || grid[r3][c3] != curr)) {
            res.second += 1;
        } else if ((inBound(grid, r2, c2) && grid[r2][c2] == curr) && 
        (inBound(grid, r3, c3) && grid[r3][c3] == curr) && (grid[r1][c1] != curr)) {
            res.second += 1;
        }

        if (inBound(grid, r2, c2) && grid[r2][c2] == curr && !visited[r2][c2]) {
            calcRegion2(grid, visited, r2, c2, curr, res);
        }
    }
}

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> grid;
    while (std::getline(inputFile, line)) {
        grid.push_back(line);
    }

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

    int res = 0;
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[0].size(); j++) {
            if (!visited[i][j]) {
                std::pair<int, int> resPair = {0, 0};
                calcRegion(grid, visited, i, j, grid[i][j], resPair);
                res += (resPair.first * resPair.second);
            }
        }
    }

    return res;
}

int part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> grid;
    while (std::getline(inputFile, line)) {
        grid.push_back(line);
    }

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

    int res = 0;
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[0].size(); j++) {
            if (!visited[i][j]) {
                std::pair<int, int> resPair = {0, 0};
                calcRegion2(grid, visited, i, j, grid[i][j], resPair);
                res += (resPair.first * resPair.second);
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