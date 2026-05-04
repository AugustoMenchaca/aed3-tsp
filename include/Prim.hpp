#ifndef PRIM_HPP
#define PRIM_HPP

#include <vector>
#include <queue>
#include <limits>

class Prim {
public:
    static std::vector<int> solve(const std::vector<std::vector<int>>& adj, int n);
};

#endif
