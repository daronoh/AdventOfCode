#include <chrono>
#include <iostream>
#include <fstream>
#include <set>
#include <stack>
using namespace std;

bool check(const set<string>& patterns, const string& design) {
    stack<size_t> stack;
    stack.push(0);

    while (!stack.empty()) {
        auto curr = stack.top();
        stack.pop();

        if (curr == design.size()) {
            return true;
        }

        for (auto& p : patterns) {
            if (design.substr(curr, p.size()) == p) {
                stack.push(curr + p.size());
            }
        }
    }

    return false;
}

uint64_t dfs(const set<string>& patterns, const string& design, uint64_t memo[], int pos) {
    if (pos == design.size()) {
        memo[pos] = 1;
        return 1;
    }

    if (memo[pos] != 0) {
        return memo[pos];
    }

    uint64_t count = 0;
    for (auto& p : patterns) {
        if (design.substr(pos, p.size()) == p) {
            count += dfs(patterns, design, memo, pos + p.size());
        }
    }

    memo[pos] = count;
    return count;
}

int part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    set<string> patterns;
    size_t start = 0, end = 0;
    while ((end = line.find(", ", start)) != string::npos) {
        patterns.insert(line.substr(start, end - start));
        start = end + 2;  // Move past the ", "
    }
    patterns.insert(line.substr(start));

    getline(inputFile, line);

    int res = 0;

    while (getline(inputFile, line)) {
        if (check(patterns, line)) {
            res++;
        }
    }

    return res;
}

uint64_t part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    set<string> patterns;
    size_t start = 0, end = 0;
    while ((end = line.find(", ", start)) != string::npos) {
        patterns.insert(line.substr(start, end - start));
        start = end + 2;  // Move past the ", "
    }
    patterns.insert(line.substr(start));

    getline(inputFile, line);

    uint64_t res = 0;

    while (getline(inputFile, line)) {
        uint64_t memo[line.size()];
        fill(memo, memo + line.size(), 0);
        res += dfs(patterns, line, memo, 0);
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