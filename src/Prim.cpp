#include "../include/Prim.hpp"

std::vector<int> Prim::solve(const std::vector<std::vector<int>>& adj, int n) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> inMST(n, false);

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int indice = pq.top().second;
        pq.pop();

        if (inMST[indice]) continue;
        inMST[indice] = true;

        for (int nei = 0; nei < n; nei++) {
            if (adj[indice][nei] != 0 && !inMST[nei] && adj[indice][nei] < dist[nei]) {
                dist[nei] = adj[indice][nei];
                parent[nei] = indice;
                pq.push({dist[nei], nei});
            }
        }
    }

    return parent;
}
