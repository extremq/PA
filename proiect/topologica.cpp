#include <list>
#include <iostream>
#include <stack>

std::list<int> adj[100];
bool visited[100] = {false};
std::stack<int> result;

void top_sort(int i) {
    visited[i] = true;

    for (auto v : adj[i])
        if (!visited[v])
            top_sort(v);

    result.push(i);
}

// Topological sort
int main() {
    int vertices = 0;
    int edges = 0;

    std::cin >> vertices >> edges;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 0; i < vertices; ++i)
        if (!visited[i])
            top_sort(i);
    
    while (!result.empty()) {
        std::cout << result.top() << ' ';
        result.pop();
    }

    return 0;
}