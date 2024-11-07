#include "AVLTree.h"
#include <limits>

int main() {
    Node* root = nullptr;
    int value;

    cout << "Введите последовательность целых чисел, заканчивающуюся нулем:" << endl;
    while (true) {
        try {
            cin >> value;
            if (cin.fail()) {  // Проверка на некорректный ввод (например, буквы вместо цифр)
                throw runtime_error("Ошибка: введите корректное целое число.");
            }

            if (value == 0) {  // Завершаем ввод при вводе 0
                break;
            }

            root = insert(root, value);
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
            cin.clear();  // Сброс состояния ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очистка входного буфера
        }
    }

    // Проверка сбалансированности дерева
    try {
        bool isBalanced = true;  // Инициализируем флаг сбалансированности
        checkBalance(root, isBalanced);

        if (isBalanced) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } catch (const runtime_error& e) {
        cerr << "Ошибка при проверке сбалансированности дерева: " << e.what() << endl;
    }

    // Освобождение памяти
    freeTree(root);

    return 0;
}