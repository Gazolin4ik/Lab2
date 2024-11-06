#include "ATDset.h"

int main(int argc, char* argv[]) {
    int capacity = 10;  // Начальный размер хеш-таблицы
    HashSet mySet(capacity);  // Создаем множество

    string command;
    int element;

    // Ввод команд
    while (true) {
        cout << "Введите команду (SETADD, SETDEL, SET_AT, PRINT, EXIT): ";
        cin >> command;

        try {
            if (command == "SETADD") {
                cout << "Введите элемент для добавления: ";
                cin >> element;
                mySet.setAdd(element);
                cout << "Элемент " << element << " добавлен.\n";
            }
            else if (command == "SETDEL") {
                cout << "Введите элемент для удаления: ";
                cin >> element;
                mySet.setDel(element);
                cout << "Элемент " << element << " удален.\n";
            }
            else if (command == "SET_AT") {
                cout << "Введите элемент для проверки: ";
                cin >> element;
                if (mySet.setAt(element)) {
                    cout << "Элемент " << element << " найден в множестве.\n";
                } else {
                    cout << "Элемент " << element << " не найден в множестве.\n";
                }
            }
            else if (command == "PRINT") {
                mySet.printSet();  // Выводим все элементы множества
            }
            else if (command == "EXIT") {
                break;
            }
            else {
                cout << "Неизвестная команда.\n";
            }
        } catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    return 0;
}