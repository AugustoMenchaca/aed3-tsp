#include "../include/BruteForce.hpp"

#include <algorithm>
#include <limits>
#include <numeric>

int BruteForce::solve(const std::vector<std::vector<int>>& weight, int cities) {
    std::vector<int> tour(cities - 1);
    std::iota(tour.begin(), tour.end(), 1);

    int record = std::numeric_limits<int>::max();

    do {
        int sum = weight[0][tour[0]];
        for (int i = 0; i < cities - 2; i++) {
            sum += weight[tour[i]][tour[i + 1]];
        }
        sum += weight[tour[cities - 2]][0];

        if (sum < record) {
            record = sum;
        }
    } while (std::next_permutation(tour.begin(), tour.end()));

    return record;
}
