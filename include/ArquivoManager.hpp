#ifndef ARQUIVO_MANAGER_HPP
#define ARQUIVO_MANAGER_HPP

#include <vector>
#include <string>
#include <map>

struct DadosTSP {
    std::string nomeArquivo;
    int totalCidades;
    std::vector<std::vector<int>> matrizAdjacencia;
};

class ArquivoManager {
public:
    // Le um arquivo especifico e retorna a matriz
    static std::vector<std::vector<int>> lerArquivo(const std::string& caminho, int& n);

    // Varre o diretorio e armazena todos os arquivos .txt encontrados
    static std::map<std::string, DadosTSP> carregarTodosOsArquivos(const std::string& diretorio);
};

#endif
