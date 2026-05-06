#include "../include/ArquivoManager.hpp"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStringList>
#include <QRegularExpression>
std::vector<std::vector<int>> ArquivoManager::lerArquivo(QString caminho) {
    QFile arquivoEntrada(caminho);
    if (!arquivoEntrada.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }

    QTextStream fluxoDados(&arquivoEntrada);
    std::vector<std::vector<int>> matrizLocal;

    // Define o limite para evitar a duplicacao do tsp4 (22x22)
    int limiteMatriz = caminho.contains("tsp4_7013.txt") ? 22 : 10000;

    while (!fluxoDados.atEnd() && (int)matrizLocal.size() < limiteMatriz) {
        QString linhaAtual = fluxoDados.readLine().trimmed();
        if (linhaAtual.isEmpty()) continue;

        // Separa os valores tratando qualquer espaco ou tab
        QStringList listaValores = linhaAtual.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        std::vector<int> linhaMatriz;
        for (int i = 0; i < listaValores.size() && i < limiteMatriz; i++) {
            linhaMatriz.push_back(listaValores[i].toInt());
        }

        if (!linhaMatriz.empty()) {
            matrizLocal.push_back(linhaMatriz);
        }
    }

    arquivoEntrada.close();
    return matrizLocal;
}

std::map<std::string, DadosTSP> ArquivoManager::carregarTodosOsArquivos(QString diretorio) {
    std::map<std::string, DadosTSP> mapaArquivos;
    QDir pasta(diretorio);

    if (!pasta.exists()) {
        qWarning() << "Diretorio nao encontrado:" << diretorio;
        return mapaArquivos;
    }

    // Filtra apenas arquivos .txt
    QStringList filtros;
    filtros << "*.txt";
    QStringList listaArquivos = pasta.entryList(filtros, QDir::Files);

    for (const QString& nome : listaArquivos) {
        QString caminhoCompleto = pasta.absoluteFilePath(nome);
        std::vector<std::vector<int>> matriz = lerArquivo(caminhoCompleto);

        if (!matriz.empty()) {
            DadosTSP dados;
            dados.nomeArquivo = nome;
            dados.totalCidades = (int)matriz.size();
            dados.matrizAdjacencia = matriz;
            mapaArquivos[nome.toStdString()] = dados;
        }
    }

    return mapaArquivos;
}
