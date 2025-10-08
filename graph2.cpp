// на основе списка смежности 
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class GraphList {
private:
    int vertices;
    vector<list<int>> adjList;

public:
    // Конструктор
    GraphList(int v) : vertices(v), adjList(v) {}
    
    // Добавление ребра
    void addEdge(int u, int v, bool directed = false) {
        adjList[u].push_back(v);
        if (!directed) {
            adjList[v].push_back(u);
        }
    }
    
    // Вывод графа
    void printGraph() {
        cout << "Список смежности:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    // Рекурсивный DFS
    void DFSRecursive(int startVertex) {
        vector<bool> visited(vertices, false);
        cout << "Рекурсивный DFS: ";
        DFSRecursiveUtil(startVertex, visited);
        cout << endl;
    }
    
    void DFSRecursiveUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFSRecursiveUtil(neighbor, visited);
            }
        }
    }
    
    // Итеративный DFS
    void DFSIterative(int startVertex) {
        vector<bool> visited(vertices, false);
        stack<int> stack;
        
        cout << "Итеративный DFS: ";
        stack.push(startVertex);
        
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                
                // Добавляем соседей в обратном порядке для сохранения порядка обхода
                for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                    if (!visited[*it]) {
                        stack.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
    
    // BFS обход
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
            
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }
    
    // Поиск кратчайшего пути (BFS-based)
    vector<int> shortestPath(int start, int end) {
        vector<bool> visited(vertices, false);
        vector<int> parent(vertices, -1);
        queue<int> queue;
        
        queue.push(start);
        visited[start] = true;
        
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            
            if (current == end) break;
            
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
        
        // Восстановление пути
        vector<int> path;
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        
        return path;
    }
    
    // Проверка на связность
    bool isConnected() {
        if (vertices == 0) return true;
        
        vector<bool> visited(vertices, false);
        stack<int> stack;
        int count = 0;
        
        stack.push(0);
        visited[0] = true;
        count++;
        
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                    visited[neighbor] = true;
                    count++;
                }
            }
        }
        
        return count == vertices;
    }
};

// Демонстрация работы
void demoListGraph() {
    cout << "\n=== ГРАФ НА СПИСКЕ СМЕЖНОСТИ ===\n";
    
    GraphList g(7);
    
    // Создаем более сложный граф
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    
    g.printGraph();
    g.DFSRecursive(0);
    g.DFSIterative(0);
    g.BFS(0);
    
    // Поиск кратчайшего пути
    vector<int> path = g.shortestPath(0, 6);
    cout << "Кратчайший путь от 0 до 6: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    
    cout << "Граф связный: " << (g.isConnected() ? "Да" : "Нет") << endl;
}

// Главная функция
int main() {
    demoMatrixGraph();
    demoListGraph();
    
    return 0;
}