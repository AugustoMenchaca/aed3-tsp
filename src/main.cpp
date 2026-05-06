#include "../include/BruteForce.hpp"
#include "../include/Prim.hpp"
#include "../include/DFS.hpp"
#include "../include/ArquivoManager.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <QString>

// Funcao auxiliar para rodar os algoritmos e imprimir resultados
void executarAlgoritmos(QString nomeArquivo, const std::vector<std::vector<int>>& matrizAdj, int totalCidades, bool forcarBruteForce) {
    std::cout << "\n---------------------------------------------------" << std::endl;
    std::cout << "Processando: " << nomeArquivo.toStdString() << " (n=" << totalCidades << ")" << std::endl;

    // 1. Calculando via Aproximacao (Prim + DFS)
    auto tempoInicioAprox = std::chrono::steady_clock::now();
    std::vector<int> paisMST = Prim::solve(matrizAdj, totalCidades);
    int custoAprox = DFS::resolver(matrizAdj, paisMST, totalCidades);
    auto tempoFimAprox = std::chrono::steady_clock::now();
    double duracaoAprox = std::chrono::duration<double>(tempoFimAprox - tempoInicioAprox).count();
    
    std::cout << "[APROX] Prim + DFS -> Custo: " << custoAprox << " | Tempo: " << std::fixed << std::setprecision(6) << duracaoAprox << "s" << std::endl;

    // 2. Calculando via Brute Force (Exato)
    if (forcarBruteForce || totalCidades <= 12) {
        auto tempoInicioBF = std::chrono::steady_clock::now();
        int custoExato = BruteForce::solve(matrizAdj, totalCidades);
        auto tempoFimBF = std::chrono::steady_clock::now();
        double duracaoBF = std::chrono::duration<double>(tempoFimBF - tempoInicioBF).count();
        std::cout << "[EXATO] Brute Force -> Custo: " << custoExato << " | Tempo: " << duracaoBF << "s" << std::endl;
    } else {
        std::cout << "[EXATO] Brute Force -> Ignorado (Tempo inviavel para n=" << totalCidades << ")" << std::endl;
    }
}

int main() {
    QString pastaData = "data";
    // Carrega todos os arquivos da pasta usando a infraestrutura Qt
    std::map<std::string, DadosTSP> arquivosCarregados = ArquivoManager::carregarTodosOsArquivos(pastaData);

    if (arquivosCarregados.empty()) {
        std::cerr << "Nenhum arquivo .txt encontrado na pasta data" << std::endl;
        return 1;
    }

    int opcao = -1;
    while (true) {
        std::cout << "\n======= MENU SISTEMA TSP (Qt Edition) =======" << std::endl;
        std::cout << "1. Listar e escolher um arquivo especifico" << std::endl;
        std::cout << "2. Rodar lote (Brute Force apenas no viavel n <= 12)" << std::endl;
        std::cout << "3. Rodar lote COMPLETO (Brute Force em tudo)" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        
        if (!(std::cin >> opcao)) break;
        if (opcao == 0) break;

        if (opcao == 1) {
            std::vector<std::string> nomes;
            int i = 1;
            std::cout << "\nArquivos encontrados via QDir:" << std::endl;
            for (auto const& [nome, dados] : arquivosCarregados) {
                std::cout << i << ". " << nome << " (n=" << dados.totalCidades << ")" << std::endl;
                nomes.push_back(nome);
                i++;
            }

            int escolhaArq;
            std::cout << "Escolha o numero do arquivo: ";
            if (!(std::cin >> escolhaArq)) break;

            if (escolhaArq > 0 && escolhaArq <= (int)nomes.size()) {
                std::string chave = nomes[escolhaArq - 1];
                executarAlgoritmos(arquivosCarregados[chave].nomeArquivo, arquivosCarregados[chave].matrizAdjacencia, arquivosCarregados[chave].totalCidades, false);
            } else {
                std::cout << "Opcao de arquivo invalida!" << std::endl;
            }

        } else if (opcao == 2 || opcao == 3) {
            bool forcarTudo = (opcao == 3);
            std::cout << "\nIniciando processamento em lote (" << (forcarTudo ? "COMPLETO" : "VIAVEL") << ")..." << std::endl;
            
            for (auto const& [nome, dados] : arquivosCarregados) {
                executarAlgoritmos(dados.nomeArquivo, dados.matrizAdjacencia, dados.totalCidades, forcarTudo);
            }
        }
    }

    return 0;
}
