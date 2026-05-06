#ifndef ARQUIVO_MANAGER_HPP
#define ARQUIVO_MANAGER_HPP

#include <vector>
#include <string>
#include <map>
#include <QString>

struct DadosTSP {
    QString nomeArquivo;
    int totalCidades;
    std::vector<std::vector<int>> matrizAdjacencia;
};

class ArquivoManager {
public:
    // Le um arquivo especifico usando QFile e QTextStream
    static std::vector<std::vector<int>> lerArquivo(QString caminho);

    // Varre o diretorio usando QDir e armazena todos os arquivos .txt encontrados
    static std::map<std::string, DadosTSP> carregarTodosOsArquivos(QString diretorio);
};

#endif
