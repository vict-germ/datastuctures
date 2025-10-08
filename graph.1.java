// на основе матрицы смежности
import java.util.*;

public class GraphMatrix {
    private int vertices;
    private int[][] adjMatrix;
    
    // Конструктор
    public GraphMatrix(int vertices) {
        this.vertices = vertices;
        this.adjMatrix = new int[vertices][vertices];
    }
    
    // Добавление ребра
    public void addEdge(int u, int v, boolean directed) {
        adjMatrix[u][v] = 1;
        if (!directed) {
            adjMatrix[v][u] = 1;
        }
    }
    
    public void addEdge(int u, int v) {
        addEdge(u, v, false);
    }
    
    // Вывод графа
    public void printGraph() {
        System.out.println("Матрица смежности:");
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                System.out.print(adjMatrix[i][j] + " ");
            }
            System.out.println();
        }
    }
    
    // Обход в глубину (DFS) - итеративный
    public void DFS(int startVertex) {
        boolean[] visited = new boolean[vertices];
        Stack<Integer> stack = new Stack<>();
        
        System.out.print("DFS обход: ");
        stack.push(startVertex);
        visited[startVertex] = true;
        
        while (!stack.isEmpty()) {
            int current = stack.pop();
            System.out.print(current + " ");
            
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    stack.push(i);
                    visited[i] = true;
                }
            }
        }
        System.out.println();
    }
    
    // Обход в ширину (BFS)
    public void BFS(int startVertex) {
        boolean[] visited = new boolean[vertices];
        Queue<Integer> queue = new LinkedList<>();
        
        System.out.print("BFS обход: ");
        queue.offer(startVertex);
        visited[startVertex] = true;
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
            System.out.print(current + " ");
            
            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    queue.offer(i);
                    visited[i] = true;
                }
            }
        }
        System.out.println();
    }
    
    // Рекурсивный DFS
    public void DFSRecursive(int startVertex) {
        boolean[] visited = new boolean[vertices];
        System.out.print("Рекурсивный DFS: ");
        DFSRecursiveUtil(startVertex, visited);
        System.out.println();
    }
    
    private void DFSRecursiveUtil(int v, boolean[] visited) {
        visited[v] = true;
        System.out.print(v + " ");
        
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[v][i] == 1 && !visited[i]) {
                DFSRecursiveUtil(i, visited);
            }
        }
    }
    
    // Проверка на наличие ребра
    public boolean hasEdge(int u, int v) {
        return adjMatrix[u][v] == 1;
    }
    
    // Получение соседей вершины
    public List<Integer> getNeighbors(int vertex) {
        List<Integer> neighbors = new ArrayList<>();
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[vertex][i] == 1) {
                neighbors.add(i);
            }
        }
        return neighbors;
    }
    
    // Демонстрация работы
    public static void main(String[] args) {
        System.out.println("=== ГРАФ НА МАТРИЦЕ СМЕЖНОСТИ ===\n");
        
        GraphMatrix graph = new GraphMatrix(6);
        
        // Добавляем ребра
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4);
        graph.addEdge(3, 5);
        graph.addEdge(4, 5);
        
        graph.printGraph();
        graph.DFS(0);
        graph.DFSRecursive(0);
        graph.BFS(0);
        
        System.out.println("Соседи вершины 0: " + graph.getNeighbors(0));
        System.out.println("Есть ли ребро между 0 и 1: " + graph.hasEdge(0, 1));
        System.out.println("Есть ли ребро между 0 и 5: " + graph.hasEdge(0, 5));
    }
}