def insertion_sort(arr):
    """
    Функция для сортировки массива методом вставок
    """
    # Проходим по всем элементам массива, начиная со второго
    for i in range(1, len(arr)):
        key = arr[i]  # Текущий элемент, который нужно вставить
        j = i - 1     # Индекс предыдущего элемента
        
        # Перемещаем элементы arr[0..i-1], которые больше key,
        # на одну позицию вперед
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j = j - 1
        
        # Вставляем key на правильное место
        arr[j + 1] = key


def print_array(arr):
    """
    Функция для вывода массива
    """
    for value in arr:
        print(value, end=" ")
    print()  # Перевод строки


# Основная программа
if __name__ == "__main__":
    array = [12, 11, 13, 5, 6]
    
    print("Исходный массив:")
    print_array(array)
    
    insertion_sort(array)
    
    print("Отсортированный массив:")
    print_array(array)