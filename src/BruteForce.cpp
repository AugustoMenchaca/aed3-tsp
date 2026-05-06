#include "../include/BruteForce.hpp"

#include <algorithm>
#include <limits>
#include <numeric>

int BruteForce::solve(const std::vector<std::vector<int>>& adj, int n) {
    std::vector<int> perm(n - 1);
    std::iota(perm.begin(), perm.end(), 1);

    int melhorCusto = std::numeric_limits<int>::max();

    do {
        int custo = adj[0][perm[0]];
        for (int i = 0; i < n - 2; i++) {
            custo += adj[perm[i]][perm[i + 1]];
        }
        custo += adj[perm[n - 2]][0];

        if (custo < melhorCusto) {
            melhorCusto = custo;
        }
    } while (std::next_permutation(perm.begin(), perm.end()));

    return melhorCusto;
}
