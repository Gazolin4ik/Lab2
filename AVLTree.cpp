#include "AVLTree.h"

// 7 3 2 1 9 5 4 6 8 0

// Структура для узла дерева
struct Node {
    int value;          // Значение узла
    Node* left;         // Указатель на левое поддерево
    Node* right;        // Указатель на правое поддерево
};

// Функция для создания нового узла
Node* createNode(int value) {
    Node* newNode = new Node;   // Выделяем память для нового узла
    newNode->value = value;     // Инициализируем значение узла
    newNode->left = nullptr;    // Устанавливаем левый указатель в nullptr (узел не имеет левого поддерева)
    newNode->right = nullptr;   // Устанавливаем правый указатель в nullptr (узел не имеет правого поддерева)
    return newNode;             // Возвращаем указатель на новый узел
}

// Функция для вставки элемента в бинарное дерево поиска
Node* insert(Node* root, int value) {
    if (root == nullptr) {            // Если дерево пустое (или достигнут конец поддерева)
        return createNode(value);     // Создаем новый узел с данным значением
    }
    if (value < root->value) {        // Если значение меньше значения текущего узла
        root->left = insert(root->left, value);  // Рекурсивно вставляем значение в левое поддерево
    } else if (value > root->value) { // Если значение больше значения текущего узла
        root->right = insert(root->right, value); // Рекурсивно вставляем значение в правое поддерево
    }
    return root;                      // Возвращаем корень дерева после вставки
}

// Функция для вычисления высоты дерева и проверки сбалансированности
int checkBalance(Node* root, bool& isBalanced) {
    if (root == nullptr) {             // Базовый случай: если узел пустой
        return 0;                      // Высота пустого поддерева равна 0
    }

    int leftHeight = checkBalance(root->left, isBalanced);    // Рекурсивно вычисляем высоту левого поддерева
    int rightHeight = checkBalance(root->right, isBalanced);  // Рекурсивно вычисляем высоту правого поддерева

    // Проверяем сбалансированность текущей вершины
    if (abs(leftHeight - rightHeight) > 1) { // Если разница высот поддеревьев больше 1
        isBalanced = false;                  // Дерево несбалансированное
    }

    // Возвращаем высоту текущего поддерева
    return 1 + max(leftHeight, rightHeight); // Высота узла — это 1 + высота самого высокого поддерева
}

// Функция для освобождения памяти дерева
void freeTree(Node* root) {
    if (root != nullptr) {            // Проверяем, что узел не пустой
        freeTree(root->left);         // Рекурсивно освобождаем память левого поддерева
        freeTree(root->right);        // Рекурсивно освобождаем память правого поддерева
        delete root;                  // Удаляем текущий узел
    }
}