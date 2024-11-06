#include "AVLTree.h"

int main() {
    Node* root = nullptr;             // Инициализируем корень дерева как пустой
    int value;

    cout << "Введите последовательность целых чисел, заканчивающуюся нулем:" << endl;
    while (true) {
        cin >> value;                 // Вводим значение
        if (value == 0) {             // Если введено значение 0, завершаем ввод
            break;
        }
        root = insert(root, value);   // Вставляем значение в дерево
    }

    // Проверка сбалансированности дерева
    bool isBalanced = true;           // Инициализируем флаг сбалансированности как true
    checkBalance(root, isBalanced);   // Вызываем функцию проверки сбалансированности

    if (isBalanced) {                 // Если дерево сбалансировано
        cout << "YES" << endl;
    } else {                          // Если дерево не сбалансировано
        cout << "NO" << endl;
    }

    // Освобождение памяти
    freeTree(root);                   // Освобождаем память, занятую деревом

    return 0;
}