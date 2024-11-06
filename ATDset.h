#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Константы для состояния ячейки
const int EMPTY = -1;
const int DELETED = -2;

// Определение хеш-таблицы для множества
struct HashSet {
    int* table;            // Массив для хранения значений множества
    int capacity;          // Размер хеш-таблицы
    int size;              // Текущее количество элементов в множестве

    // Конструктор
    HashSet(int cap) : capacity(cap), size(0) {
        table = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = EMPTY;  // Инициализация всех ячеек как пустых
        }
    }

    // Деструктор
    ~HashSet() {
        delete[] table;
    }

    // Хеш-функция
    int hash(int key) {
        return key % capacity;
    }

    // Функция для добавления элемента в множество
    void setAdd(int key) {
        int idx = hash(key);
        int startIdx = idx;

        while (table[idx] != EMPTY && table[idx] != DELETED && table[idx] != key) {
            idx = (idx + 1) % capacity;  // Переход к следующей ячейке (линейное пробирование)
            if (idx == startIdx) throw runtime_error("HashSet is full"); // Таблица полная
        }

        if (table[idx] == key) {  // Если элемент уже существует
            throw runtime_error("Element already exists in the set");
        }

        table[idx] = key;  // Добавляем элемент в таблицу
        size++;
    }

    // Функция для удаления элемента из множества
    void setDel(int key) {
        int idx = hash(key);
        int startIdx = idx;

        while (table[idx] != EMPTY) {
            if (table[idx] == key) {
                table[idx] = DELETED;  // Помечаем ячейку как удаленную
                size--;
                return;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break; // Элемент не найден
        }
        throw runtime_error("Element not found in the set"); // Элемент отсутствует
    }

    // Функция для проверки, является ли элемент частью множества
    bool setAt(int key) {
        int idx = hash(key);
        int startIdx = idx;

        while (table[idx] != EMPTY) {
            if (table[idx] == key) {
                return true;  // Элемент найден
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) return false;  // Элемент не найден
        }
        return false;  // Элемент не найден
    }

    // Функция для вывода всех элементов множества
    void printSet() {
        cout << "Элементы множества: ";
        bool isEmpty = true;  // Флаг для проверки, если множество пусто
        for (int i = 0; i < capacity; ++i) {
            if (table[i] != EMPTY && table[i] != DELETED) {
                cout << table[i] << " ";
                isEmpty = false;  // Найден хотя бы один элемент
            }
        }
        if (isEmpty) {
            cout << "множество пусто.";
        }
        cout << endl;
    }
};