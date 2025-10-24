#include <iostream>
#include <vector>
using namespace std;

// Функция для слияния двух отсортированных массивов
vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    int i = 0, j = 0;
    
    // Пока есть элементы в обоих массивах
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    
    // Добавляем оставшиеся элементы из левого массива
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    
    // Добавляем оставшиеся элементы из правого массива
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    
    return result;
}

// Функция сортировки слиянием
vector<int> mergeSort(const vector<int>& arr) {
    // Базовый случай: массив длиной 0 или 1 уже отсортирован
    if (arr.size() <= 1) {
        return arr;
    }
    
    // Находим середину массива
    int mid = arr.size() / 2;
    
    // Делим массив на две части
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    
    // Рекурсивно сортируем каждую часть
    left = mergeSort(left);
    right = mergeSort(right);
    
    // Сливаем отсортированные части
    return merge(left, right);
}

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    cout << "Исходный массив: ";
    printArray(arr);
    
    vector<int> sortedArr = mergeSort(arr);
    
    cout << "Отсортированный массив: ";
    printArray(sortedArr);
    
    return 0;
}