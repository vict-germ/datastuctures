def shell_sort(arr):
    """
    Функция для сортировки Шелла
    """
    n = len(arr)
    
    # Начинаем с большого промежутка и уменьшаем его
    gap = n // 2
    while gap > 0:
        # Проходим по всем элементам с текущим промежутком
        for i in range(gap, n):
            # Сохраняем текущий элемент
            temp = arr[i]
            j = i
            
            # Сдвигаем элементы, которые больше temp, вправо
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            
            # Вставляем temp на правильное место
            arr[j] = temp
        
        # Уменьшаем промежуток
        gap //= 2


def print_array(arr):
    """
    Функция для вывода массива
    """
    for num in arr:
        print(num, end=" ")
    print()


# Пример использования
if __name__ == "__main__":
    arr = [12, 34, 54, 2, 3]
    
    print("Исходный массив:", end=" ")
    print_array(arr)
    
    shell_sort(arr)
    
    print("Отсортированный массив:", end=" ")
    print_array(arr)