#include "Arr.h"

// Функция для инициализации динамического массива
void initArray(Array& arr, int initialCapacity) {
    arr.data = new string[initialCapacity];
    arr.capacity = initialCapacity;
    arr.size = 0;
}

// Функция для добавления элемента в динамический массив
void addElement(Array& arr, const string& value) {
    if (arr.size == arr.capacity) {
        // Расширяем массив, если достигнута максимальная ёмкость
        arr.capacity *= 2;
        string* newData = new string[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    arr.data[arr.size++] = value;
}

// Функция для освобождения памяти динамического массива
void freeArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.capacity = 0;
    arr.size = 0;
}

// Функция для вывода содержимого динамического массива
void printArray(const Array& arr) {
    cout << "{ ";
    for (int i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << " ";
    }
    cout << "}" << endl;
}

// Функция для вывода всех подмассивов массива
void printAllSubarrays(const Array& arr) {
    cout << "Все подмассивы:" << endl;
    for (int start = 0; start < arr.size; ++start) {
        for (int end = start; end < arr.size; ++end) {
            cout << "{ ";
            for (int i = start; i <= end; ++i) {
                cout << arr.data[i] << " ";
            }
            cout << "}" << endl;
        }
    }
}