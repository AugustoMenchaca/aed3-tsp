#include "../include/ArquivoManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::vector<int>> ArquivoManager::lerArquivo(const std::string& caminho, int& n) {
    std::ifstream arquivoEntrada(caminho);
    if (!arquivoEntrada) {
        std::cerr << "Nao foi possivel abrir o arquivo: " << caminho << "\n";
        return {};
    }

    // Verificacao para o arquivo tsp4 que esta duplicado
    bool ehArquivoTsp4 = (caminho.find("tsp4_7013.txt") != std::string::npos);
    int limiteLinhas = ehArquivoTsp4 ? 22 : 1000000; // Valor alto caso nao seja o tsp4
    int contadorLinhas = 0;

    std::vector<std::vector<int>> matrizLocal;
    std::string linha;
    
    while (std::getline(arquivoEntrada, linha) && contadorLinhas < limiteLinhas) {
        std::istringstream iss(linha);
        std::vector<int> linhaMatriz;
        int valor;
        int contadorColunas = 0;
        int limiteColunas = ehArquivoTsp4 ? 22 : 1000000;
        
        while (iss >> valor && contadorColunas < limiteColunas) {
            linhaMatriz.push_back(valor);
            contadorColunas++;
        }
        
        if (!linhaMatriz.empty()) {
            matrizLocal.push_back(linhaMatriz);
            contadorLinhas++;
        }
    }

    n = (int)matrizLocal.size();
    return matrizLocal;
}

std::map<std::string, DadosTSP> ArquivoManager::carregarTodosOsArquivos(const std::string& diretorio) {
    std::map<std::string, DadosTSP> mapaArquivos;

    try {
        for (const auto& entrada : fs::directory_iterator(diretorio)) {
            if (entrada.is_regular_file() && entrada.path().extension() == ".txt") {
                std::string caminho = entrada.path().string();
                std::string nome = entrada.path().filename().string();
                
                int n = 0;
                std::vector<std::vector<int>> matriz = lerArquivo(caminho, n);
                
                if (n > 0) {
                    DadosTSP dados;
                    dados.nomeArquivo = nome;
                    dados.totalCidades = n;
                    dados.matrizAdjacencia = matriz;
                    mapaArquivos[nome] = dados;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao ler diretorio: " << e.what() << "\n";
    }

    return mapaArquivos;
}
