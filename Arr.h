#pragma once

#include <iostream>
#include <string>

using namespace std;

// Структура для динамического массива
struct Array {
    string* data;     // Указатель на массив строк
    int capacity;     // Текущая ёмкость массива
    int size;         // Текущее количество элементов
};
void initArray(Array& arr, int initialCapacity = 2);
void addElement(Array& arr, const string& value);
void freeArray(Array& arr);
void printArray(const Array& arr);
void printAllSubarrays(const Array& arr);
