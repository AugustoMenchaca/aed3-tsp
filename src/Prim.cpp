#include "../include/Prim.hpp"

std::vector<int> Prim::solve(const std::vector<std::vector<int>>& adj, int n) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> inMST(n, false);

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0 && !inMST[v] && adj[u][v] < dist[v]) {
                dist[v] = adj[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return parent;
}
