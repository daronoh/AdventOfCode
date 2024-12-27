#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    vector<vector<int>> maze(71, vector<int>(71, -1));

    for (int i = 0; i < 1024; i++) {
        string line;
        getline(inputFile, line);
        int r, c;
        char comma;
        stringstream ss(line);
        ss >> r >> comma >> c;
        maze[r][c] = -2;
    }

    queue<pair<int, int>> queue;
    queue.emplace(0, 0);
    maze[0][0] = 0;
    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();

        if (curr.first == 70 && curr.second == 70) {
            return maze[70][70];
        }

        for (auto dir : dirs) {
            int newR = curr.first + dir[0];
            int newC = curr.second + dir[1];

            if (newR < 0 || newC < 0 || newR > 70 || newC > 70 || maze[newR][newC] != -1) {
                continue;
            }

            maze[newR][newC] = maze[curr.first][curr.second] + 1;
            queue.emplace(newR, newC);
        }
    }

    return -1;
}

bool simulate(vector<pair<int, int>>& fallingBytes, int limit) {
    vector<vector<int>> maze(71, vector<int>(71, -1));
    for (int i = 0; i <= limit; i++) {
        auto curr = fallingBytes[i];
        maze[curr.first][curr.second] = -2;
    }

    queue<pair<int, int>> queue;
    queue.emplace(0, 0);
    maze[0][0] = 0;
    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();

        if (curr.first == 70 && curr.second == 70) {
            return true;
        }

        for (auto dir : dirs) {
            int newR = curr.first + dir[0];
            int newC = curr.second + dir[1];

            if (newR < 0 || newC < 0 || newR > 70 || newC > 70 || maze[newR][newC] != -1) {
                continue;
            }

            maze[newR][newC] = maze[curr.first][curr.second] + 1;
            queue.emplace(newR, newC);
        }
    }

    return false;
}

void part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return;
    }

    vector<pair<int, int>> fallingBytes;
    string line;

    while (getline(inputFile, line)) {
        int r, c;
        char comma;
        stringstream ss(line);

        ss >> r >> comma >> c;
        
        fallingBytes.emplace_back(r, c);
    }

    int high = fallingBytes.size() - 1;
    int low = 0;

    while (low < high) {
        int mid = low + (high - low) / 2;

        bool hasPath = simulate(fallingBytes, mid);
        if (hasPath) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    cout << "Coordinate: " << fallingBytes[low].first << ", " << fallingBytes[low].second << endl;
}

int main() {
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << part1() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2: " << std::endl;
    part2();
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    return 0;
}