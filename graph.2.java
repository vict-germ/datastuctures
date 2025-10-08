// на основе списка смежности 
import java.util.*;

public class GraphList {
    private int vertices;
    private Map<Integer, List<Integer>> adjList;
    
    // Конструктор
    public GraphList(int vertices) {
        this.vertices = vertices;
        this.adjList = new HashMap<>();
        
        // Инициализируем список для каждой вершины
        for (int i = 0; i < vertices; i++) {
            adjList.put(i, new LinkedList<>());
        }
    }
    
    // Добавление ребра
    public void addEdge(int u, int v, boolean directed) {
        adjList.get(u).add(v);
        if (!directed) {
            adjList.get(v).add(u);
        }
    }
    
    public void addEdge(int u, int v) {
        addEdge(u, v, false);
    }
    
    // Вывод графа
    public void printGraph() {
        System.out.println("Список смежности:");
        for (int i = 0; i < vertices; i++) {
            System.out.print(i + " -> ");
            for (Integer neighbor : adjList.get(i)) {
                System.out.print(neighbor + " ");
            }
            System.out.println();
        }
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
        
        for (int neighbor : adjList.get(v)) {
            if (!visited[neighbor]) {
                DFSRecursiveUtil(neighbor, visited);
            }
        }
    }
    
    // Итеративный DFS
    public void DFSIterative(int startVertex) {
        boolean[] visited = new boolean[vertices];
        Stack<Integer> stack = new Stack<>();
        
        System.out.print("Итеративный DFS: ");
        stack.push(startVertex);
        
        while (!stack.isEmpty()) {
            int current = stack.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                System.out.print(current + " ");
                
                // Добавляем соседей в обратном порядке
                List<Integer> neighbors = adjList.get(current);
                for (int i = neighbors.size() - 1; i >= 0; i--) {
                    int neighbor = neighbors.get(i);
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }
        System.out.println();
    }
    
    // BFS обход
    public void BFS(int startVertex) {
        boolean[] visited = new boolean[vertices];
        Queue<Integer> queue = new LinkedList<>();
        
        System.out.print("BFS обход: ");
        queue.offer(startVertex);
        visited[startVertex] = true;
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
            System.out.print(current + " ");
            
            for (int neighbor : adjList.get(current)) {
                if (!visited[neighbor]) {
                    queue.offer(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        System.out.println();
    }
    
    // Поиск кратчайшего пути (BFS-based)
    public List<Integer> shortestPath(int start, int end) {
        if (start == end) {
            return Arrays.asList(start);
        }
        
        boolean[] visited = new boolean[vertices];
        int[] parent = new int[vertices];
        Arrays.fill(parent, -1);
        
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        visited[start] = true;
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
            
            if (current == end) break;
            
            for (int neighbor : adjList.get(current)) {
                if (!visited[neighbor]) {
                    queue.offer(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
        
        // Восстановление пути
        List<Integer> path = new ArrayList<>();
        for (int v = end; v != -1; v = parent[v]) {
            path.add(v);
        }
        Collections.reverse(path);
        
        // Если путь не найден
        if (path.get(0) != start) {
            return new ArrayList<>();
        }
        
        return path;
    }
    
    // Проверка на связность
    public boolean isConnected() {
        if (vertices == 0) return true;
        
        boolean[] visited = new boolean[vertices];
        Stack<Integer> stack = new Stack<>();
        int count = 0;
        
        stack.push(0);
        visited[0] = true;
        count++;
        
        while (!stack.isEmpty()) {
            int current = stack.pop();
            
            for (int neighbor : adjList.get(current)) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                    visited[neighbor] = true;
                    count++;
                }
            }
        }
        
        return count == vertices;
    }
    
    // Поиск циклов
    public boolean hasCycle() {
        boolean[] visited = new boolean[vertices];
        
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                if (hasCycleUtil(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    private boolean hasCycleUtil(int v, boolean[] visited, int parent) {
        visited[v] = true;
        
        for (int neighbor : adjList.get(v)) {
            if (!visited[neighbor]) {
                if (hasCycleUtil(neighbor, visited, v)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }
    
    // Демонстрация работы
    public static void main(String[] args) {
        System.out.println("=== ГРАФ НА СПИСКЕ СМЕЖНОСТИ ===\n");
        
        GraphList graph = new GraphList(7);
        
        // Создаем граф
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 5);
        graph.addEdge(3, 6);
        graph.addEdge(4, 6);
        graph.addEdge(5, 6);
        
        graph.printGraph();
        graph.DFSRecursive(0);
        graph.DFSIterative(0);
        graph.BFS(0);
        
        // Поиск кратчайшего пути
        List<Integer> path = graph.shortestPath(0, 6);
        System.out.println("Кратчайший путь от 0 до 6: " + path);
        
        // Проверка свойств графа
        System.out.println("Граф связный: " + graph.isConnected());
        System.out.println("Граф содержит цикл: " + graph.hasCycle());
        
        // Тест с несвязным графом
        GraphList disconnectedGraph = new GraphList(5);
        disconnectedGraph.addEdge(0, 1);
        disconnectedGraph.addEdge(2, 3);
        disconnectedGraph.addEdge(3, 4);
        
        System.out.println("\nНесвязный граф:");
        System.out.println("Граф связный: " + disconnectedGraph.isConnected());
    }
}