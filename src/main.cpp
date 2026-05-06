#include "../include/BruteForce.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::vector<std::vector<int>> readMatrix(const std::string& path, int& n) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Could not open " << path << "\n";
        std::exit(1);
    }

    std::vector<std::vector<int>> rows;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int v;
        while (iss >> v) row.push_back(v);
        if (!row.empty()) rows.push_back(std::move(row));
    }

    n = (int)rows.size();
    return rows;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <tsp_file>\n";
        return 1;
    }

    int n = 0;
    auto adj = readMatrix(argv[1], n);
    std::cout << "file: " << argv[1] << "  n=" << n << "\n";

    auto t0 = std::chrono::steady_clock::now();
    int cost = BruteForce::solve(adj, n);
    auto t1 = std::chrono::steady_clock::now();

    double secs = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "cost = " << cost << "   time = " << secs << " s\n";
    return 0;
}
