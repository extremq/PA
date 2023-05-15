#include <iostream>

const int INF = 100000;

int pred[100][100];
int dist[100][100];

int main () {
    int vertices = 0;
    int edges = 0;

    std::cin >> vertices >> edges;
    // Predecesori
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < vertices; ++j) {
            pred[i][j] = i;
        }

    // Matricea de distanta
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < vertices; ++j)
            dist[i][j] = INF;
    
    for (int i = 0; i < vertices; ++i)
        dist[i][i] = 0;

    // Citirea muchiilor
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        dist[u][v] = w;
    }

    // Algoritmul Floyd-Warshall
    for (int k = 0; k < vertices; ++k)
        for (int i = 0; i < vertices; ++i)
            for (int j = 0; j < vertices; ++j)  {
                int temp;
                if (dist[i][k] != INF && dist[k][j] != INF)
                    temp = dist[i][k] + dist[k][j];
                else
                    temp = INF;
                
                if (temp < dist[i][j]) {
                    dist[i][j] = temp;

                    pred[i][j] = pred[k][j];
                }
            }
    
    // Afisare
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (dist[i][j] == INF)
                std::cout << "INF ";
            else
                std::cout << dist[i][j] << ' ';
        }   
        std::cout << '\n';
    }
}