#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdint>

void adv(int* regA, int combo) {
    *regA = *regA >> combo;
}

void bxl(int* regB, int literal) {
    *regB = *regB ^ literal;
}

void bst(int* regB, int combo) {
    *regB = combo % 8;
}

bool jnz(int* PC, int* regA, int literal) {
    if (*regA != 0) {
        *PC = literal;
        return true;
    }

    return false;
}

void bxc(int* regB, int* regC) {
    *regB = *regB ^ *regC;
}

std::string out(int combo) {
    combo = combo % 8;
    std::string res = std::to_string(combo);
    std::ostringstream oss;
    for (size_t i = 0; i < res.size(); i++) {
        oss << res[i];
        oss << ',';
    }

    return oss.str();
}

void bdv(int* regA, int* regB, int combo) {
    *regB = *regA >> combo;
}

void cdv(int* regA, int* regC, int combo) {
    *regC = *regA >> combo;
}

int getCombo(int* regA, int* regB, int* regC, int combo) {
    if (combo < 4) {
        return combo;
    } else if (combo == 4) {
        return *regA;
    } else if (combo == 5) {
        return *regB;
    } else if (combo == 6) {
        return *regC;
    } else {
        std::cerr << "Invalid combo input!" << std::endl;
        return -1;
    }
}


// reverse engineer the input specific operations, assuming B and C are always 0
uint64_t dfs(std::string& progs, int PC, uint64_t curr) {
    if (PC < 0) return curr;

    for (int i = 0; i < 8; i++) {
        uint64_t a = (curr << 3) | i;
        uint64_t b = a % 8;
        b = b ^ 1;
        uint64_t c = a >> b;
        b = b ^ 5;
        b = b ^ c;
        if (b % 8 + '0' == progs[PC]) {
            uint64_t sub = dfs(progs, PC - 1, a);
            if (sub == -1) {
                continue;
            }
            return sub;
        }
    }

    return -1;
}

std::string part1() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return "error!";
    }

    std::string strA;
    getline(inputFile, strA);
    std::string strB;
    getline(inputFile, strB);
    std::string strC;
    getline(inputFile, strC);

    int regA = std::stoi(strA = strA.substr(12));
    int regB = std::stoi(strB = strB.substr(12));
    int regC = std::stoi(strC = strC.substr(12));

    std::string programmes;
    getline(inputFile,programmes);
    getline(inputFile,programmes);
    programmes = programmes.substr(9);
    programmes.erase(remove(programmes.begin(), programmes.end(), ','), programmes.end());

    int PC = 0;
    std::stringstream ss;
    while (PC < programmes.size()) {
        char opcode = programmes[PC];
        int literal = programmes[PC + 1] - '0';
        if (opcode == '0') {
            adv(&regA, getCombo(&regA, &regB, &regC, literal));
            PC += 2;
        } else if (opcode == '1') {
            bxl(&regB, literal);
            PC += 2;
        } else if (opcode == '2') {
            bst(&regB, getCombo(&regA, &regB, &regC, literal));
            PC += 2;
        } else if (opcode == '3') {
            if (!jnz(&PC, &regA, literal)) {
                PC += 2;
            }
        } else if (opcode == '4') {
            bxc(&regB, &regC);
            PC += 2;
        } else if (opcode == '5') {
            ss << out(getCombo(&regA, &regB, &regC, literal));
            PC += 2;
        } else if (opcode == '6') {
            bdv(&regA, &regB, getCombo(&regA, &regB, &regC, literal));
            PC += 2;
        } else if (opcode == '7') {
            cdv(&regA, &regC, getCombo(&regA, &regB, &regC, literal));
            PC += 2;
        } else {
            std::cerr << "Invalid opcode input!" << std::endl;
            return "error!";
        }

        /*
        std::cout << "A: " << regA << std::endl;
        std::cout << "B: " << regB << std::endl;
        std::cout << "C: " << regC << std::endl;
        std::cout << "PC: " << PC << std::endl;
        */
    }

    std::string res = ss.str();
    if (res != "") {
        res.pop_back();
    }
    return res;
}

uint64_t part2() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Unable to open input.txt" << std::endl;
        return -1;
    }

    std::string programmes;
    getline(inputFile,programmes);
    getline(inputFile,programmes);
    getline(inputFile,programmes);
    getline(inputFile,programmes);
    getline(inputFile,programmes);
    programmes = programmes.substr(9);
    programmes.erase(remove(programmes.begin(), programmes.end(), ','), programmes.end());

    return dfs(programmes, programmes.size() - 1, 0);
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