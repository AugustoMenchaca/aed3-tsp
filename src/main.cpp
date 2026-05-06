#include "../include/BruteForce.hpp"
#include "../include/Prim.hpp"
#include "../include/DFS.hpp"
#include "../include/ArquivoManager.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

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
    return 0;
}
