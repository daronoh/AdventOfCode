#include <fstream>
#include <iostream>
#include <vector>

int checkXmas(int r, int c, const std::vector<std::string>& grid) {
    int num = 0;
    if (r > 2) {
        // check north
        if (grid[r - 1][c] == 'M' && grid[r - 2][c] == 'A' && grid[r - 3][c] == 'S') {
            num++;
        }

        if (c > 2) {
            // check northwest
            if (grid[r - 1][c - 1] == 'M' && grid[r - 2][c - 2] == 'A' && grid[r - 3][c - 3] == 'S') {
                num++;
            }
        }

        if (grid[0].size() - c > 3) {
            // check northeast
            if (grid[r - 1][c + 1] == 'M' && grid[r - 2][c + 2] == 'A' && grid[r - 3][c + 3] == 'S') {
                num++;
            }
        }
    }

    if (grid.size() - r > 3) {
        // check south
        if (grid[r + 1][c] == 'M' && grid[r + 2][c] == 'A' && grid[r + 3][c] == 'S') {
            num++;
        }

        if (c > 2) {
            // check southwest
            if (grid[r + 1][c - 1] == 'M' && grid[r + 2][c - 2] == 'A' && grid[r + 3][c - 3] == 'S') {
                num++;
            }
        }

        if (grid[0].size() - c > 3) {
            // check southeast
            if (grid[r + 1][c + 1] == 'M' && grid[r + 2][c + 2] == 'A' && grid[r + 3][c + 3] == 'S') {
                num++;
            }
        }
    }

    if (c > 2) {
        // check west
        if (grid[r][c - 1] == 'M' && grid[r][c - 2] == 'A' && grid[r][c - 3] == 'S') {
            num++;
        }
    }

    if (grid[0].size() - c > 3) {
        //  check east
        if (grid[r][c + 1] == 'M' && grid[r][c + 2] == 'A' && grid[r][c + 3] == 'S') {
            num++;
        }
    }

    return num;
}

bool checkCrossMas(int r, int c, const std::vector<std::string>& grid) {
    std::string diagonal1;
    std::string diagonal2;
    for (int i = -1; i < 2; i++) {
        diagonal1.push_back(grid[r + i][c + i]);
        diagonal2.push_back(grid[r - i][c + i]);
    }

    return (diagonal1 == "MAS" || diagonal1 == "SAM") && (diagonal2 == "MAS" || diagonal2 == "SAM");
}

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;

    while (std::getline(inputFile, line)) {
        grid.push_back(line);
    }

    inputFile.close();

    // part 1
    int res = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X') {
                res += checkXmas(i, j, grid);
            }
        }
    }

    std::cout << res << std::endl;

    // part 2
    int res2 = 0;

    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid[0].size() - 1; j++) {
            if (grid[i][j] == 'A' && checkCrossMas(i, j, grid)) {
                res2++;
            }
        }
    }

    std::cout << res2 << std::endl;

    return 0;

}
