#include "Arr.h"

// Функция для инициализации динамического массива
void initArray(Array& arr, int initialCapacity) {
    arr.data = new string[initialCapacity]; // Выделяем память для массива строк с заданной начальной ёмкостью.
    arr.capacity = initialCapacity;        // Устанавливаем ёмкость массива.
    arr.size = 0;                          // Устанавливаем начальный размер массива как 0 (массив пустой).
}
 
// Функция для добавления элемента в динамический массив
void addElement(Array& arr, const string& value) {
    if (arr.size == arr.capacity) { // Проверяем, достиг ли массив своей максимальной ёмкости.
        arr.capacity *= 2;          // Удваиваем ёмкость массива.
        string* newData = new string[arr.capacity]; // Выделяем память для нового массива увеличенной ёмкости.
        for (int i = 0; i < arr.size; ++i) { // Копируем элементы из старого массива в новый.
            newData[i] = arr.data[i];
        }
        delete[] arr.data; // Освобождаем память старого массива.
        arr.data = newData; // Устанавливаем указатель на новый массив.
    }
    arr.data[arr.size++] = value; // Добавляем новый элемент в массив и увеличиваем размер на 1.
}
 
// Функция для освобождения памяти динамического массива
void freeArray(Array& arr) {
    delete[] arr.data; // Освобождаем память, выделенную для массива.
    arr.data = nullptr; // Устанавливаем указатель на массив в nullptr, чтобы избежать использования удалённой памяти.
    arr.capacity = 0;   // Обнуляем ёмкость массива.
    arr.size = 0;       // Обнуляем размер массива.
}
 
// Функция для вывода содержимого динамического массива
void printArray(const Array& arr) {
    cout << "{ ";
    for (int i = 0; i < arr.size; ++i) { // Перебираем все элементы массива.
        cout << arr.data[i] << " ";     // Выводим текущий элемент.
    }
    cout << "}" << endl; // Завершаем вывод фигурной скобкой.
}
 
// Функция для вывода всех подмассивов массива
void printAllSubarrays(const Array& arr) {
    cout << "All subarrays:" << endl;
    for (int start = 0; start < arr.size; ++start) { // Устанавливаем начальную позицию подмассива.
        for (int end = start; end < arr.size; ++end) { // Устанавливаем конечную позицию подмассива.
            cout << "{ ";
            for (int i = start; i <= end; ++i) { // Перебираем элементы от начальной до конечной позиции.
                cout << arr.data[i] << " ";    // Выводим текущий элемент подмассива.
            }
            cout << "}" << endl; // Завершаем вывод текущего подмассива.
        }
    }
}