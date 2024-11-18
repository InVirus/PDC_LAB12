#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1000000000;

void loadGraph(const char* filename, int**& matrix, int& n, int& m) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Помилка відкриття файлу." << std::endl;
        return;
    }

    file >> n >> m;

    if (n <= 0 || m < 0) {
        std::cerr << "Некоректні значення для n або m." << std::endl;
        return;
    }

    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = INF;
        }
        matrix[i][i] = 0;
    }

    int u, v, w;
    for (int i = 0; i < m; ++i) {
        file >> u >> v >> w;
        if (u < 1 || u > n || v < 1 || v > n) {
            std::cerr << "Помилка: індекси ребер виходять за межі матриці. u=" << u << ", v=" << v << std::endl;
            continue;
        }
        matrix[u - 1][v - 1] = w;
    }

    file.close();
}

void printMatrix(int** matrix, int n, const char* outputFile) {
    std::ofstream file(outputFile);
    if (!file) {
        std::cerr << "Помилка відкриття файлу для запису." << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INF) {
                std::cout << "INF ";
                file << "INF ";
            }
            else {
                std::cout << matrix[i][j] << " ";
                file << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
        file << std::endl;
    }

    file.close();
}

void freeMatrix(int** matrix, int n) {
    if (matrix != nullptr) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void dijkstra(int** matrix, int n, int start, std::vector<int>& dist, std::vector<int>& prev) {
    dist.assign(n, INF);
    prev.assign(n, -1);
    dist[start] = 0;

    using PII = std::pair<int, int>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u]) continue;

        for (int v = 0; v < n; ++v) {
            if (matrix[u][v] < INF) {
                int newDist = dist[u] + matrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({ newDist, v });
                }
            }
        }
    }
}

void printShortestPath(int end, const std::vector<int>& prev) {
    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Найкоротший маршрут: ";
    for (int v : path) {
        std::cout << v + 1 << " ";
    }
    std::cout << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* inputFilename = "in.txt";
    const char* outputFilename = "out.txt";
    int n, m;
    int** matrix = nullptr;

    loadGraph(inputFilename, matrix, n, m);

    if (matrix != nullptr) {
        printMatrix(matrix, n, outputFilename);

        int start, end;
        std::cout << "Введіть початкову вершину: ";
        std::cin >> start;
        std::cout << "Введіть кінцеву вершину: ";
        std::cin >> end;

        std::vector<int> dist, prev;
        dijkstra(matrix, n, start - 1, dist, prev);

        std::cout << "Найкоротша відстань від " << start << " до " << end << ": " << dist[end - 1] << std::endl;
        printShortestPath(end - 1, prev);

        std::cout << "Найкоротші відстані від вершини " << start << " до всіх інших вершин:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << "До вершини " << i + 1 << ": " << dist[i] << std::endl;
        }

        freeMatrix(matrix, n);
    }

    return 0;
}
