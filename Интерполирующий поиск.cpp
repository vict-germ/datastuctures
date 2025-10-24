#include <iostream>
#include <vector>
using namespace std;

// Функция интерполяционного поиска
int interpolationSearch(vector<int>& arr, int lo, int hi, int x) {
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
        // Вычисляем позицию с помощью интерполяционной формулы
        int pos = lo + (((hi - lo) * (x - arr[lo])) / (arr[hi] - arr[lo]));
        
        // Если элемент найден
        if (arr[pos] == x) {
            return pos;
        }
        
        // Если x больше, ищем в правом подмассиве
        if (arr[pos] < x) {
            return interpolationSearch(arr, pos + 1, hi, x);
        }
        
        // Если x меньше, ищем в левом подмассиве
        if (arr[pos] > x) {
            return interpolationSearch(arr, lo, pos - 1, x);
        }
    }
    return -1; // Элемент не найден
}

// Вспомогательная функция для вызова поиска без указания границ
int interpolationSearch(vector<int>& arr, int x) {
    return interpolationSearch(arr, 0, arr.size() - 1, x);
}

// Функция для вывода массива
void printArray(vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
    int target = 18;
    
    cout << "Массив: ";
    printArray(arr);
    cout << "Ищем элемент: " << target << endl;
    
    int result = interpolationSearch(arr, target);
    
    if (result != -1) {
        cout << "Элемент найден на позиции: " << result << endl;
    } else {
        cout << "Элемент не найден" << endl;
    }
    
    return 0;
}