#include "../include/BruteForce.hpp"
#include "../include/Prim.hpp"
#include "../include/DFS.hpp"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "uso: " << argv[0] << " <arquivo> [--exato-max N]\n";
        return 1;
    }

    int exatoMax = 14;
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--exato-max" && i + 1 < argc) {
            exatoMax = std::atoi(argv[++i]);
        }
    }

    std::ifstream arquivo(argv[1]);
    if (!arquivo) {
        std::cerr << "nao foi possivel abrir " << argv[1] << "\n";
        return 1;
    }

    std::vector<std::vector<int>> matriz;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        std::vector<int> linhaMatriz;
        int v;
        while (iss >> v) linhaMatriz.push_back(v);
        if (!linhaMatriz.empty()) matriz.push_back(std::move(linhaMatriz));
    }

    int n = (int)matriz.size();
    std::cout << "arquivo: " << argv[1] << "  n=" << n << "\n";

    auto inicioAprox = std::chrono::steady_clock::now();
    std::vector<int> pais = Prim::solve(matriz, n);
    int custoAprox = DFS::resolver(matriz, pais, n);
    auto fimAprox = std::chrono::steady_clock::now();
    double tempoAprox = std::chrono::duration<double>(fimAprox - inicioAprox).count();
    std::cout << "aproximativo (Prim+DFS):  custo=" << custoAprox
              << "  tempo=" << tempoAprox << "s\n";

    if (n <= exatoMax) {
        auto inicioExato = std::chrono::steady_clock::now();
        int custoExato = BruteForce::solve(matriz, n);
        auto fimExato = std::chrono::steady_clock::now();
        double tempoExato = std::chrono::duration<double>(fimExato - inicioExato).count();
        std::cout << "exato (brute force):      custo=" << custoExato
                  << "  tempo=" << tempoExato << "s\n";
    } else {
        std::cout << "exato (brute force):      pulado (n=" << n
                  << " > " << exatoMax << ", inviavel)\n";
    }

    return 0;
}
