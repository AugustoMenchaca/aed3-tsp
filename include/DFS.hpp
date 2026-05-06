#ifndef DFS_HPP
#define DFS_HPP

#include <vector>

class DFS {
public:
    static int resolver(const std::vector<std::vector<int>>& matrizOriginal, const std::vector<int>& pais, int totalCidades);

private:
    static void fazerDFS(int verticeAtual, const std::vector<std::vector<int>>& filhos, std::vector<int>& ordemDeVisita);
};

#endif
