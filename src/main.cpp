#include "../include/BruteForce.hpp"
#include "../include/Prim.hpp"
#include "../include/DFS.hpp"
<<<<<<< HEAD
#include "../include/ArquivoManager.hpp"

#include <chrono>
=======

#include <chrono>
#include <cstdlib>
#include <fstream>
>>>>>>> 9d7b42259205d2c0804d911b88e1dfc6ce594239
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

<<<<<<< HEAD
void executarAlgoritmos(const std::string& nome, const std::vector<std::vector<int>>& matriz, int n) {
    std::cout << "\n---------------------------------------------------" << std::endl;
    std::cout << "Arquivo: " << nome << " (n=" << n << ")" << std::endl;

    // 1. Testando Prim + DFS (Aproximacao)
    auto inicioPrim = std::chrono::steady_clock::now();
    std::vector<int> paisPrim = Prim::solve(matriz, n);
    int custoDFS = DFS::resolver(matriz, paisPrim, n);
    auto fimDFS = std::chrono::steady_clock::now();
    double tempoAprox = std::chrono::duration<double>(fimDFS - inicioPrim).count();

    std::cout << "[APROX] Prim + DFS -> Custo: " << custoDFS << " | Tempo: " << std::fixed << std::setprecision(6) << tempoAprox << "s" << std::endl;

    // 2. Testando Brute Force (Apenas para n pequenos, ex: n <= 12)
    if (n <= 12) {
        auto inicioBF = std::chrono::steady_clock::now();
        int custoBF = BruteForce::solve(matriz, n);
        auto fimBF = std::chrono::steady_clock::now();
        double tempoBF = std::chrono::duration<double>(fimBF - inicioBF).count();
        std::cout << "[EXATO] Brute Force -> Custo: " << custoBF << " | Tempo: " << tempoBF << "s" << std::endl;
    } else {
        std::cout << "[EXATO] Brute Force -> Ignorado (n muito grande)" << std::endl;
    }
}

int main() {
    std::string pastaData = "data";
    std::map<std::string, DadosTSP> arquivosCarregados = ArquivoManager::carregarTodosOsArquivos(pastaData);

    if (arquivosCarregados.empty()) {
        std::cerr << "Nenhum arquivo .txt encontrado na pasta " << pastaData << std::endl;
        return 1;
    }

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n======= MENU SISTEMA TSP =======" << std::endl;
        std::cout << "1. Listar e escolher um arquivo" << std::endl;
        std::cout << "2. Rodar todos os arquivos (Lote)" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        if (opcao == 1) {
            std::vector<std::string> nomes;
            int i = 1;
            std::cout << "\nArquivos disponiveis:" << std::endl;
            for (auto const& [nome, dados] : arquivosCarregados) {
                std::cout << i << ". " << nome << " (n=" << dados.totalCidades << ")" << std::endl;
                nomes.push_back(nome);
                i++;
            }

            int escolhaArq;
            std::cout << "Escolha o numero do arquivo: ";
            std::cin >> escolhaArq;

            if (escolhaArq > 0 && escolhaArq <= (int)nomes.size()) {
                std::string arqSelecionado = nomes[escolhaArq - 1];
                executarAlgoritmos(arqSelecionado, arquivosCarregados[arqSelecionado].matrizAdjacencia, arquivosCarregados[arqSelecionado].totalCidades);
            }

        } else if (opcao == 2) {
            std::cout << "\nIniciando processamento em lote..." << std::endl;
            for (auto const& [nome, dados] : arquivosCarregados) {
                executarAlgoritmos(nome, dados.matrizAdjacencia, dados.totalCidades);
            }
        }
    }

    std::cout << "\nSaindo do sistema..." << std::endl;
=======
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

>>>>>>> 9d7b42259205d2c0804d911b88e1dfc6ce594239
    return 0;
}
