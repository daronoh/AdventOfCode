#include <fstream>
#include <iostream>
#include <regex>

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return 1;
    }

    // part 1
    int res = 0;
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    std::string input((std::istreambuf_iterator<char>(inputFile)),
                      std::istreambuf_iterator<char>());

    auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; it++) {
        int firstNum = std::stoi(it->str(1));
        int secondNum = std::stoi(it->str(2));

        res += (firstNum * secondNum);
    }

    std::cout << res << std::endl;


    // part 2
    int res2 = 0;
    std::regex pattern2(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don\'t\(\))");
    bool isActive = true;

    auto begin2 = std::sregex_iterator(input.begin(), input.end(), pattern2);


    for (auto it = begin2; it != end; it++) {
        std::string instruction = it->str();
        if (instruction == "do()") {
            isActive = true;
        } else if (instruction == "don't()") {
            isActive = false;
        } else if (isActive) {
            int firstNum = std::stoi(it->str(1));
            int secondNum = std::stoi(it->str(2));

            res2 += (firstNum * secondNum);
        }
    }

    std::cout << res2 << std::endl;

    inputFile.close();
}
