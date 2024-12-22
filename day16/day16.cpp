#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <array>

int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Point {
    int r;
    int c;
    int dir;
    int score;

    Point(int r, int c, int dir, int score) : r(r), c(c), dir(dir), score(score) {}

};

std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "Point(" << p.r << ", " << p.c << ", " << p.dir << ", " << p.score << ")";
        return os;
}

template<typename T>
struct ComparePoint {
    bool operator()(const T& p1, const T& p2) {
        return p1.score > p2.score;
    }
};

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> maze;
    int startR, startC;
    int endR, endC;
    while (getline(inputFile, line)) {
        maze.push_back(line);
    }
    bool startFound = false;
    bool endFound = false;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == 'S') {
                startR = i;
                startC = j;
                startFound = true;
            } else if (maze[i][j] == 'E') {
                endR = i;
                endC = j;
                endFound = true;
            }
        }
        if (startFound && endFound) {
            break;
        }
    }

    std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size(), false));
    std::priority_queue<Point, std::vector<Point>, ComparePoint<Point>> pq;
    pq.emplace(startR, startC, 1, 0);
    while (!pq.empty()) {
        Point curr = pq.top();
        pq.pop();
        if (curr.r == endR && curr.c == endC) {
            return curr.score;
        }
        if (visited[curr.r][curr.c]) {
            continue;
        }
        visited[curr.r][curr.c] = true;
        for (int i = 0; i < 4; i++) {
            if (i == curr.dir) {
                if (maze[curr.r + dirs[i][0]][curr.c + dirs[i][1]] != '#') {
                    pq.emplace(curr.r + dirs[i][0], curr.c + dirs[i][1], i, curr.score + 1);
                }
            } else if (maze[curr.r + dirs[i][0]][curr.c + dirs[i][1]] != '#') {
                pq.emplace(curr.r + dirs[i][0], curr.c + dirs[i][1], i, curr.score + 1001);
            }
        }
    }

    return 0;
}

/*
int part2() {
    std::ifstream inputFile("test.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> maze;
    int startR, startC;
    int endR, endC;
    while (getline(inputFile, line)) {
        maze.push_back(line);
    }
    bool startFound = false;
    bool endFound = false;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == 'S') {
                startR = i;
                startC = j;
                startFound = true;
            } else if (maze[i][j] == 'E') {
                endR = i;
                endC = j;
                endFound = true;
            }
        }
        if (startFound && endFound) {
            break;
        }
    }

    std::vector<std::vector<std::array<int, 4>>> score(maze.size(), 
        std::vector<std::array<int, 4>>(maze[0].size(), {-1, -1, -1, -1}));

    std::vector<std::vector<std::vector<Point>>> predecessors(maze.size(), 
        std::vector<std::vector<Point>>(maze[0].size()));
    
    std::priority_queue<Point, std::vector<Point>, ComparePoint<Point>> pq;
    pq.emplace(startR, startC, 1, 0);
    int targetScore;
    while (!pq.empty()) {
        Point curr = pq.top();
        std::cout << curr << std::endl;
        pq.pop();
        if (!predecessors[endR][endC].empty()) {
            if (curr.score > targetScore) {
                break;
            }

            if (curr.c == endC && curr.r == endR) {
                predecessors[curr.r][curr.c].emplace_back(curr.r - dirs[curr.dir][0], curr.c - dirs[curr.dir][1], 0, 0);
                continue;
            } else {
                continue;
            }
        }

        if (curr.c == endC && curr.r == endR) {
            predecessors[curr.r][curr.c].emplace_back(curr.r - dirs[curr.dir][0], curr.c - dirs[curr.dir][1], 0, 0);
            targetScore = curr.score;
            continue;
        }

        std::array<int, 4> baseArray = {-1, -1, -1, -1};

        if (score[curr.r][curr.c] != baseArray) {
            // have visited before
            if (score[curr.r][curr.c][curr.dir] == curr.score) {
                predecessors[curr.r][curr.c].emplace_back(curr.r - dirs[curr.dir][0], curr.c - dirs[curr.dir][1], 0, 0);
                continue;
            } else {
                continue;
            }
        }

        score[curr.r][curr.c][curr.dir] = curr.score;
        predecessors[curr.r][curr.c].emplace_back(curr.r - dirs[curr.dir][0], curr.c - dirs[curr.dir][1], 0, 0);

        for (int i = 0; i < 4; i++) {
            if (i == curr.dir) {
                if (maze[curr.r + dirs[i][0]][curr.c + dirs[i][1]] != '#') {
                    pq.emplace(curr.r + dirs[i][0], curr.c + dirs[i][1], i, curr.score + 1);
                }
            } else if (curr.dir + 2 % 4  == i) {
                if (maze[curr.r + dirs[i][0]][curr.c + dirs[i][1]] != '#') {
                    pq.emplace(curr.r + dirs[i][0], curr.c + dirs[i][1], i, curr.score + 2001);
                }
            } else if (maze[curr.r + dirs[i][0]][curr.c + dirs[i][1]] != '#') {
                pq.emplace(curr.r + dirs[i][0], curr.c + dirs[i][1], i, curr.score + 1001);
            }
        }
    }

    std::cout << "End size: " << predecessors[endR][endC].size() << std::endl;
    std::cout << "7, 15 size: " << predecessors[7][15].size() << std::endl;
    std::cout << "12, 11 size: " << predecessors[12][11].size() << std::endl;

    for (auto p : predecessors[12][11]) {
        std::cout << p << std::endl;
    }
    
    std::vector<std::vector<bool>> inPath(maze.size(), std::vector<bool>(maze[0].size(), false));
    std::queue<Point> queue;
    int res = 1;
    inPath[endR][endC] = true;
    for (auto p : predecessors[endR][endC]) {
        queue.push(p);
    }

    while (!queue.empty()) {
        auto p = queue.front();
        // std::cout << p << std::endl;
        queue.pop();
        if (!inPath[p.r][p.c]) {
            res++;
            inPath[p.r][p.c] = true;
        }

        for (auto h : predecessors[p.r][p.c]) {
        queue.push(h);
        }
    }

    return res;
}
*/
int main() {
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << part1() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    
    /*
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2: " << part2() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    */
    return 0;
}