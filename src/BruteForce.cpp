#include "../include/BruteForce.hpp"

#include <algorithm>
#include <limits>
#include <numeric>

int BruteForce::solve(const std::vector<std::vector<int>>& adj, int n) {
    // Fix city 0 as the start: tours are rotation-invariant, so only (n-1)! permutations matter.
    std::vector<int> perm(n - 1);
    std::iota(perm.begin(), perm.end(), 1);

    int bestCost = std::numeric_limits<int>::max();

    do {
        int cost = adj[0][perm[0]];
        for (int i = 0; i < n - 2; i++) {
            cost += adj[perm[i]][perm[i + 1]];
        }
        cost += adj[perm[n - 2]][0];

        if (cost < bestCost) {
            bestCost = cost;
        }
    } while (std::next_permutation(perm.begin(), perm.end()));

    return bestCost;
}
