#include "../include/DFS.hpp"

void DFS::fazerDFS(int verticeAtual, const std::vector<std::vector<int>>& filhos, std::vector<int>& ordemDeVisita) {
    
    ordemDeVisita.push_back(verticeAtual);

    for (size_t i = 0; i < filhos[verticeAtual].size(); i++) {
        int proximoFilho = filhos[verticeAtual][i];
        
        fazerDFS(proximoFilho, filhos, ordemDeVisita); 
    }
}

int DFS::resolver(const std::vector<std::vector<int>>& matrizOriginal, const std::vector<int>& pais, int totalCidades) {
    
    std::vector<std::vector<int>> filhos(totalCidades);
    
    for (int i = 1; i < totalCidades; i++) {
        int paiDaCidade = pais[i];
        if (paiDaCidade != -1) {
            filhos[paiDaCidade].push_back(i);
        }
    }

    std::vector<int> ordemDeVisita;
    fazerDFS(0, filhos, ordemDeVisita);

    int custoTotal = 0;
    
    for (int i = 0; i < (int)ordemDeVisita.size() - 1; i++) {
        int cidadeAtual = ordemDeVisita[i];
        int proximaCidade = ordemDeVisita[i + 1];
        
        custoTotal += matrizOriginal[cidadeAtual][proximaCidade];
    }
    
    int ultimaCidade = ordemDeVisita[ordemDeVisita.size() - 1];
    int primeiraCidade = ordemDeVisita[0];
    
    custoTotal += matrizOriginal[ultimaCidade][primeiraCidade];

    return custoTotal;
}
