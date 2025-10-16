//На с++
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class TSP {
private:
    vector<vector<int>> graph;
    int n;
    vector<int> bestPath;
    int minCost;

public:
    TSP(vector<vector<int>> matrix) {
        graph = matrix;
        n = matrix.size();
        minCost = INT_MAX;
    }

    // Рекурсивная функция для перебора всех путей
    void tspRecursive(vector<int>& path, vector<bool>& visited, int currentCost) {
        // Если все города посещены
        if (path.size() == n) {
            // Добавляем стоимость возврата в начальный город
            int totalCost = currentCost + graph[path.back()][path[0]];
            
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = path;
            }
            return;
        }

        // Перебираем все непосещенные города
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                // Вычисляем стоимость перехода
                int cost = currentCost;
                if (!path.empty()) {
                    cost += graph[path.back()][i];
                }

                // Отсечение неоптимальных ветвей
                if (cost < minCost) {
                    visited[i] = true;
                    path.push_back(i);
                    
                    tspRecursive(path, visited, cost);
                    
                    path.pop_back();
                    visited[i] = false;
                }
            }
        }
    }

    // Основная функция решения
    void solve() {
        if (n == 0) return;

        vector<int> path;
        vector<bool> visited(n, false);

        // Начинаем с города 0
        path.push_back(0);
        visited[0] = true;

        tspRecursive(path, visited, 0);

        // Добавляем начальный город в конец для завершения цикла
        bestPath.push_back(bestPath[0]);
    }

    void printSolution() {
        cout << "Минимальная стоимость: " << minCost << endl;
        cout << "Оптимальный маршрут: ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
    }

    int getMinCost() { return minCost; }
    vector<int> getBestPath() { return bestPath; }
};

// Жадный алгоритм (быстрый, но не всегда оптимальный)
vector<int> greedyTSP(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path;
    vector<bool> visited(n, false);
    
    path.push_back(0);
    visited[0] = true;
    
    for (int i = 1; i < n; i++) {
        int current = path.back();
        int nextCity = -1;
        int minDist = INT_MAX;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[current][j] < minDist) {
                minDist = graph[current][j];
                nextCity = j;
            }
        }
        
        path.push_back(nextCity);
        visited[nextCity] = true;
    }
    
    // Замыкаем цикл
    path.push_back(path[0]);
    return path;
}

int calculateCost(vector<int>& path, vector<vector<int>>& graph) {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += graph[path[i]][path[i+1]];
    }
    return cost;
}

int main() {
    // Пример матрицы расстояний между городами
    vector<vector<int>> distanceMatrix = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cout << "=== Точное решение (полный перебор) ===" << endl;
    TSP tsp(distanceMatrix);
    tsp.solve();
    tsp.printSolution();

    cout << "\n=== Жадный алгоритм ===" << endl;
    vector<int> greedyPath = greedyTSP(distanceMatrix);
    int greedyCost = calculateCost(greedyPath, distanceMatrix);
    
    cout << "Стоимость: " << greedyCost << endl;
    cout << "Маршрут: ";
    for (int city : greedyPath) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}