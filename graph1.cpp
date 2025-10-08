#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class GraphMatrix {
private:
    int vertices;
    vector<vector<int>> adjMatrix;

public:
    // Конструктор
    GraphMatrix(int v) : vertices(v), adjMatrix(v, vector<int>(v, 0)) {}
    
    // Добавление ребра
    void addEdge(int u, int v, bool directed = false) {
        adjMatrix[u][v] = 1;
        if (!directed) {
            adjMatrix[v][u] = 1;
        }
    }
    
    // Вывод графа
    void printGraph() {
        cout << "Матрица смежности:\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // Обход в глубину (DFS)
    void DFS(int startVertex) {
        vector<bool> visited(vertices, false);
        stack<int> stack;
        
        cout << "DFS обход: ";
        stack.push(startVertex);
        visited[startVertex] = true;
        
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            cout << current << " ";
            
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    stack.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }
    
    // Обход в ширину (BFS)
    void BFS(int startVertex) {
        vector<bool> visited(vertices, false);
        queue<int> queue;
        
        cout << "BFS обход: ";
        queue.push(startVertex);
        visited[startVertex] = true;
        
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            cout << current << " ";
            
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }
    
    // Проверка на наличие ребра
    bool hasEdge(int u, int v) {
        return adjMatrix[u][v] == 1;
    }
};

// Демонстрация работы
void demoMatrixGraph() {
    cout << "=== ГРАФ НА МАТРИЦЕ СМЕЖНОСТИ ===\n";
    
    GraphMatrix g(6);
    
    // Добавляем ребра
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    
    g.printGraph();
    g.DFS(0);
    g.BFS(0);
    
    cout << "Есть ли ребро между 0 и 1: " << (g.hasEdge(0, 1) ? "Да" : "Нет") << endl;
    cout << "Есть ли ребро между 0 и 5: " << (g.hasEdge(0, 5) ? "Да" : "Нет") << endl;
}