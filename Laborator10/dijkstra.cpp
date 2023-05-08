#include <iostream>
#include <queue>

#define INF 2'000'000'000

int distance[10][10];
int min_path[10];
int prev[10];

// Priority queue with the smallest element on top
struct Compare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first > b.first;
    }
};

int main() {
    int nodes, edges;

    // fill the distance matrix with INF
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10 ; ++j) {
            distance[i][j] = INF;
        }
    }
    
    // fill the min_path array with INF
    for (int i = 0; i < 10; ++i) {
        min_path[i] = INF;
    }

    // fill the prev array with -1
    for (int i = 0; i < 10; ++i) {
        prev[i] = -1;
    }

    // read the number of nodes and edges
    std::cin >> nodes >> edges;
    for (int i = 0; i < nodes; ++i) {
        distance[i][i] = 0;
    }

    for (int i = 0; i < edges; ++i) {
        int x, y, cost;
        std::cin >> x >> y >> cost;
        distance[x][y] = cost;
    }

    // Dijkstra
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        int node = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (cost > min_path[node]) {
            continue;
        }

        for (int i = 0; i < nodes; ++i) {
            if (distance[node][i] != INF) {
                if (min_path[i] > cost + distance[node][i]) {
                    min_path[i] = cost + distance[node][i];
                    prev[i] = node;
                    pq.push({min_path[i], i});
                }
            }
        }
    }

    // print the min_path array
    for (int i = 0; i < nodes; ++i) {
        if (min_path[i] != INF)
            std::cout << min_path[i] << " ";
        else
            std::cout << "INF ";
    }
    std::cout << "\n";

    // print the paths to all nodes from 0
    for (int i = 1; i < nodes; ++i) {
        std::cout << "Path to " << i << ": ";
        int node = i;

        // if there is no path to node i
        if (prev[node] == -1) {
            std::cout << "No path\n";
            continue;
        }

        // print the path
        while (node > 0) {
            std::cout << node << " <- ";
            node = prev[node];
        }
        std::cout << "0\n";
    }
}