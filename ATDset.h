#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Константы для состояния ячейки
const int EMPTY = -1; // Константа, обозначающая пустую ячейку в таблице.
const int DELETED = -2; // Константа, обозначающая удалённую ячейку.
 
// Определение структуры хеш-таблицы для множества
struct HashSet {
    int* table;            // Указатель на массив для хранения значений множества.
    int capacity;          // Размер хеш-таблицы (максимальное количество ячеек).
    int size;              // Текущее количество элементов в множестве.
 
    // Конструктор
    HashSet(int cap) : capacity(cap), size(0) { // Инициализирует множество с заданной ёмкостью.
        table = new int[capacity]; // Создаём массив нужного размера.
        for (int i = 0; i < capacity; ++i) { 
            table[i] = EMPTY;  // Инициализируем каждую ячейку как пустую.
        }
    }
 
    // Деструктор
    ~HashSet() {
        delete[] table; // Освобождаем память, выделенную под массив.
    }
 
    // Хеш-функция
    int hash(int key) {
        return key % capacity; // Возвращает остаток от деления ключа на размер таблицы (хеш).
    }
 
    // Функция для добавления элемента в множество
    void setAdd(int key) {
        int idx = hash(key); // Вычисляем начальный индекс для вставки элемента.
        int startIdx = idx; // Сохраняем начальный индекс для проверки цикла.
 
        while (table[idx] != EMPTY && table[idx] != DELETED && table[idx] != key) { 
            // Если текущая ячейка занята (не пустая и не удалённая) и не равна ключу:
            idx = (idx + 1) % capacity; // Переходим к следующей ячейке (линейное пробирование).
            if (idx == startIdx) throw runtime_error("HashSet is full"); // Если вернулись в начало, таблица заполнена.
        }
 
        if (table[idx] == key) {  // Если элемент уже существует в таблице:
            throw runtime_error("Element already exists in the set"); // Генерируем исключение.
        }
 
        table[idx] = key;  // Вставляем элемент в найденную подходящую ячейку.
        size++; // Увеличиваем количество элементов.
    }
 
    // Функция для удаления элемента из множества
    void setDel(int key) {
        int idx = hash(key); // Вычисляем индекс хеша для ключа.
        int startIdx = idx; // Сохраняем начальный индекс для проверки цикла.
 
        while (table[idx] != EMPTY) { // Пока не найдена пустая ячейка:
            if (table[idx] == key) { // Если текущая ячейка содержит ключ:
                table[idx] = DELETED;  // Помечаем ячейку как удалённую.
                size--; // Уменьшаем количество элементов.
                return; // Завершаем выполнение функции.
            }
            idx = (idx + 1) % capacity; // Переходим к следующей ячейке.
            if (idx == startIdx) break; // Если вернулись в начало, элемент не найден.
        }
        throw runtime_error("Element not found in the set"); // Генерируем исключение, если элемент отсутствует.
    }
 
    // Функция для проверки, является ли элемент частью множества
    bool setAt(int key) {
        int idx = hash(key); // Вычисляем индекс хеша для ключа.
        int startIdx = idx; // Сохраняем начальный индекс для проверки цикла.
 
        while (table[idx] != EMPTY) { // Пока не найдена пустая ячейка:
            if (table[idx] == key) { // Если текущая ячейка содержит ключ:
                return true;  // Возвращаем true, элемент найден.
            }
            idx = (idx + 1) % capacity; // Переходим к следующей ячейке.
            if (idx == startIdx) return false;  // Если вернулись в начало, элемент не найден.
        }
        return false;  // Если дошли до пустой ячейки, элемент не найден.
    }
 
    // Функция для вывода всех элементов множества
    void printSet() {
        cout << "Элементы множества: ";
        bool isEmpty = true;  // Флаг для проверки, если множество пусто.
        for (int i = 0; i < capacity; ++i) { 
            if (table[i] != EMPTY && table[i] != DELETED) { 
                // Если ячейка не пуста и не помечена как удалённая:
                cout << table[i] << " "; // Выводим элемент.
                isEmpty = false;  // Указываем, что множество не пусто.
            }
        }
        if (isEmpty) { // Если не найдено ни одного элемента:
            cout << "множество пусто."; // Сообщаем, что множество пусто.
        }
        cout << endl; // Завершаем вывод.
    }
};