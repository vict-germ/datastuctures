
#include <iostream>
#include <vector>

// Функция сортировки выбором
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // Проходим по всем элементам массива
    for (int i = 0; i < n - 1; i++) {
        // Предполагаем, что текущий элемент - минимальный
        int minIndex = i;
        
        // Ищем минимальный элемент в оставшейся части массива
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // Нашли новый минимальный элемент
            }
        }
        
        // Меняем местами найденный минимальный элемент с текущим
        // Используем std::swap из стандартной библиотеки
        std::swap(arr[i], arr[minIndex]);
    }
}

// Вспомогательная функция для вывода массива
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Создаем тестовый массив
    std::vector<int> testArray = {64, 25, 12, 22, 11};
    
    std::cout << "Исходный массив: ";
    printArray(testArray);
    
    // Сортируем массив
    selectionSort(testArray);
    
    std::cout << "Отсортированный массив: ";
    printArray(testArray);
    
    return 0;
}