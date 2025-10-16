//на java 
import java.util.*;

public class TSP {
    private int[][] distanceMatrix;
    private int n;
    private int minCost;
    private List<Integer> bestPath;
    
    public TSP(int[][] matrix) {
        this.distanceMatrix = matrix;
        this.n = matrix.length;
        this.minCost = Integer.MAX_VALUE;
        this.bestPath = new ArrayList<>();
    }
    
    // Точное решение методом полного перебора
    public void solveBruteForce() {
        List<Integer> path = new ArrayList<>();
        boolean[] visited = new boolean[n];
        
        // Начинаем с города 0
        path.add(0);
        visited[0] = true;
        
        bruteForceRecursive(path, visited, 0);
        
        // Замыкаем цикл
        bestPath.add(bestPath.get(0));
    }
    
    private void bruteForceRecursive(List<Integer> path, boolean[] visited, int currentCost) {
        // Базовый случай: все города посещены
        if (path.size() == n) {
            // Добавляем стоимость возврата в начальный город
            int totalCost = currentCost + distanceMatrix[path.get(path.size()-1)][path.get(0)];
            
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = new ArrayList<>(path);
            }
            return;
        }
        
        // Рекурсивный случай: пробуем все непосещенные города
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                // Вычисляем стоимость перехода к следующему городу
                int lastCity = path.get(path.size() - 1);
                int newCost = currentCost + distanceMatrix[lastCity][i];
                
                // Отсечение неоптимальных ветвей
                if (newCost < minCost) {
                    visited[i] = true;
                    path.add(i);
                    
                    bruteForceRecursive(path, visited, newCost);
                    
                    // Backtracking
                    path.remove(path.size() - 1);
                    visited[i] = false;
                }
            }
        }
    }
    
    // Жадный алгоритм (ближайший сосед)
    public void solveGreedy() {
        List<Integer> path = new ArrayList<>();
        boolean[] visited = new boolean[n];
        int currentCost = 0;
        
        // Начинаем с города 0
        int currentCity = 0;
        path.add(currentCity);
        visited[currentCity] = true;
        
        // Посещаем остальные города
        for (int i = 1; i < n; i++) {
            int nextCity = -1;
            int minDistance = Integer.MAX_VALUE;
            
            // Ищем ближайший непосещенный город
            for (int j = 0; j < n; j++) {
                if (!visited[j] && distanceMatrix[currentCity][j] < minDistance) {
                    minDistance = distanceMatrix[currentCity][j];
                    nextCity = j;
                }
            }
            
            if (nextCity != -1) {
                currentCost += minDistance;
                currentCity = nextCity;
                path.add(currentCity);
                visited[currentCity] = true;
            }
        }
        
        // Замыкаем цикл
        currentCost += distanceMatrix[currentCity][0];
        path.add(path.get(0));
        
        this.bestPath = path;
        this.minCost = currentCost;
    }
    
    public void printSolution() {
        System.out.println("Минимальная стоимость: " + minCost);
        System.out.println("Оптимальный маршрут: " + bestPath);
    }
    
    public int getMinCost() { return minCost; }
    public List<Integer> getBestPath() { return bestPath; }
}