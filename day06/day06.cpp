#include <fstream>
#include <iostream>
#include <vector>
#include <array>

bool simulate(std::vector<std::vector<bool>>& grid, int rPos, int cPos, int dir, int dirs[4][2], std::vector<std::vector<std::array<bool, 4>>> visitedWithDir, int rBlock, int cBlock) {
    grid[rBlock][cBlock] = true;
    while (true) {
        visitedWithDir[rPos][cPos][dir] = true;

        int nextR = rPos + dirs[dir][0];
        int nextC = cPos + dirs[dir][1];
        if (nextR < 0 || nextR >= grid.size() || nextC < 0 || nextC >= grid[0].size()) {
            break;
        }
        while (grid[nextR][nextC]) {
            dir = (dir + 1) % 4;
            nextR = rPos + dirs[dir][0];
            nextC = cPos + dirs[dir][1];
        }

        rPos = nextR;
        cPos = nextC;

        if (visitedWithDir[rPos][cPos][dir]) {
            grid[rBlock][cBlock] = false;
            return true;
        }
    }
    grid[rBlock][cBlock] = false;
    return false;
}

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::vector<bool>> grid;

    std::string line;
    int rPos, cPos;
    int r = 0;
    while (std::getline(inputFile, line)) {
        std::vector<bool> currentRow(line.size(), false);
        for (int c = 0; c < line.size(); c++) {
            if (line[c] == '#') {
                currentRow[c] = true;
            } else if (line[c] == '^') {
                rPos = r;
                cPos = c;
            }
        }
        grid.push_back(currentRow);
        r++;
    }

    inputFile.close();

    // part 1
    int height = grid.size();
    int width = grid[0].size();
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int dir = 0;
    int res = 0;
    int rPos1 = rPos;
    int cPos1 = cPos;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    while (true) {
        if (!visited[rPos1][cPos1]) {
            visited[rPos1][cPos1] = true;
            res++;
        }
        int nextR = rPos1 + dirs[dir][0];
        int nextC = cPos1 + dirs[dir][1];
        if (nextR < 0 || nextR >= height || nextC < 0 || nextC >= width) {
            break;
        }
        if (grid[nextR][nextC]) {
            dir = (dir + 1) % 4;
        } else {
            rPos1 = nextR;
            cPos1 = nextC;
        }
    }

    std::cout << res << std::endl;

    // part 2


    dir = 0;
    res = 0;
    std::vector<std::vector<bool>> tried(height, std::vector<bool>(width, false));
    std::vector<std::vector<std::array<bool, 4>>> visitedWithDir(height, std::vector<std::array<bool, 4>>(width, {false, false, false, false}));

    while (true) {
        visitedWithDir[rPos][cPos][dir] = true;

        int nextR = rPos + dirs[dir][0];
        int nextC = cPos + dirs[dir][1];
        if (nextR < 0 || nextR >= height || nextC < 0 || nextC >= width) {
            break;
        }

        if (grid[nextR][nextC]) {
            dir = (dir + 1) % 4;
        } else {
            if (!tried[nextR][nextC]) {
                if (simulate(grid, rPos, cPos, dir, dirs, visitedWithDir, nextR, nextC)) {
                    res++;
                }
                tried[nextR][nextC] = true;
            }

            rPos = nextR;
            cPos = nextC;
        }
    }

    std::cout << res << std::endl;

    return 0;
}