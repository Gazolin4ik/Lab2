#include "Arr.h"

int main() {
    Array arr;
    initArray(arr);

    int numElements;
    cout << "Введите количество элементов в массиве: ";
    cin >> numElements;

    cout << "Введите элементы массива:\n";
    for (int i = 0; i < numElements; ++i) {
        string element;
        cout << "Элемент " << (i + 1) << ": ";
        cin >> element;
        addElement(arr, element);
    }

    cout << "Исходный массив: ";
    printArray(arr);

    // Вывод всех подмассивов
    printAllSubarrays(arr);

    // Освобождение памяти
    freeArray(arr);

    return 0;
}