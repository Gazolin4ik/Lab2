#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int value;
    Node* next;
};

// Структура для хранения множества
struct Set {
    Node* head;  // Указатель на начало списка
    int size;    // Количество элементов в множестве

    // Конструктор множества
    Set() : head(nullptr), size(0) {}

    // Добавление элемента в множество
    void add(int value) {
        if (contains(value)) {
            throw runtime_error("Ошибка: элемент " + to_string(value) + " уже существует в множестве.");
        }
        Node* newNode = new Node{value, head};
        head = newNode;
        size++;
    }

    // Проверка, находится ли элемент в множестве
    bool contains(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Удаление элемента из множества
    void remove(int value) {
        Node* current = head;
        Node* previous = nullptr;
        
        while (current != nullptr) {
            if (current->value == value) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                size--;
                return;
            }
            previous = current;
            current = current->next;
        }
        throw runtime_error("Ошибка: элемент " + to_string(value) + " не найден в множестве.");
    }

    // Вывод всех элементов множества
    void print() {
        Node* current = head;
        cout << "{ ";
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << "}" << endl;
    }

    // Функция для очистки множества
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    // Функция для вычисления суммы всех элементов в множестве
    int sum() {
        int total = 0;
        Node* current = head;
        while (current != nullptr) {
            total += current->value;
            current = current->next;
        }
        return total;
    }
};

// Рекурсивная функция для поиска подмножества с заданной суммой
bool findSubset(Set& set, Set& subset, int targetSum, Node* startNode) {
    if (targetSum == 0) {
        return true;
    }
    if (startNode == nullptr || targetSum < 0) {
        return false;
    }
    Node* current = startNode;
    while (current != nullptr) {
        int value = current->value;
        subset.add(value);            // Добавляем текущий элемент во временное подмножество
        set.remove(value);            // Убираем его из исходного множества
        if (findSubset(set, subset, targetSum - value, set.head)) {
            return true;
        }
        subset.remove(value);         // Удаляем элемент из подмножества, если он не подошел
        set.add(value);               // Возвращаем элемент обратно в множество
        current = current->next;
    }
    return false;
}

// Основная функция для разбиения множества на подмножества с заданной суммой
void splitSet(Set& set, int targetSum) {
    int totalSum = set.sum();
    if (totalSum % targetSum != 0) {
        throw runtime_error("Ошибка: множество не может быть разбито на подмножества с суммой " + to_string(targetSum) + ".");
    }

    int numSubsets = totalSum / targetSum;  // Количество необходимых подмножеств
    for (int i = 0; i < numSubsets; ++i) {
        Set subset;  // Временное подмножество
        if (findSubset(set, subset, targetSum, set.head)) {
            cout << "Подмножество " << (i + 1) << ": ";
            subset.print();
        } else {
            throw runtime_error("Ошибка: не удалось найти подмножество с суммой " + to_string(targetSum) + ".");
        }
    }
}