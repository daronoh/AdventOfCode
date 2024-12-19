#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void moveRobot(std::pair<int, int>& robot, std::vector<std::string>& grid, int dir) {
    int newR = robot.first + dirs[dir][0];
    int newC = robot.second + dirs[dir][1];

    if (grid[newR][newC] == '#') {
        return;
    } else if (grid[newR][newC] == '.') {
        grid[newR][newC] = '@';
        grid[robot.first][robot.second] = '.';
        robot.first = newR;
        robot.second = newC;
    } else {
        int oToJumpX = newR + dirs[dir][0];
        int oToJumpY = newC + dirs[dir][1];
        while (grid[oToJumpX][oToJumpY] == 'O') {
            oToJumpX += dirs[dir][0];
            oToJumpY += dirs[dir][1];
        }
        if (grid[oToJumpX][oToJumpY] != '#') {
            grid[oToJumpX][oToJumpY] = 'O';
            grid[newR][newC] = '@';
            grid[robot.first][robot.second] = '.';
            robot.first = newR;
            robot.second = newC;
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
    while(getline(inputFile, line)) {
        if (line == "") {
            break;
        }

        grid.push_back(line);
    }

    std::pair<int, int> robot({-1, -1});
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '@') {
                robot.first = i;
                robot.second = j;
                break;
            }
        }
        if (robot.first != -1) {
            break;
        }
    }

    while (getline(inputFile, line)) {
        for (auto c : line) {
            if (c == '^') {
                moveRobot(robot, grid, 0);
            } else if (c == '>') {
                moveRobot(robot, grid, 1);
            } else if (c == 'v') {
                moveRobot(robot, grid, 2);
            } else {
                moveRobot(robot, grid, 3);
            }
        }
    }

    int res = 0;
    for (int r = 1; r < grid.size() - 1; r++) {
        for (int c = 1; c < grid[0].size() - 1; c++) {
            if (grid[r][c] == 'O') {
                res += (100 * r + c);
            }
        }
    }

    return res;
}

int part2() {
    return 0;
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