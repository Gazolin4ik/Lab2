#include "Stack.h"

// Узел стека
struct StackNode {
    int value;
    StackNode* next;
};

// Функция для добавления элемента в стек
void push(StackNode*& top, int value) {
    StackNode* newNode = new StackNode{value, top};  // Создаем новый узел, инициализируем значением и указателем на текущий top.
    top = newNode;                                   // Обновляем top, чтобы указывать на новый узел.
}

// Функция для удаления элемента из стека и возврата его значения
int pop(StackNode*& top) {
    if (top == nullptr) {                            // Проверяем, что стек не пуст.
        throw runtime_error("Stack underflow");      // Бросаем исключение, если стек пуст.
    }
    int value = top->value;                          // Сохраняем значение верхнего узла.
    StackNode* temp = top;                           // Сохраняем указатель на текущий top.
    top = top->next;                                 // Обновляем top, чтобы он указывал на следующий элемент.
    delete temp;                                     // Освобождаем память удаленного узла.
    return value;                                    // Возвращаем значение удаленного узла.
}

// Функция для получения значения верхнего элемента стека без его удаления
int peek(StackNode* top) {
    if (top == nullptr) {                            // Проверяем, что стек не пуст.
        throw runtime_error("Stack is empty");       // Бросаем исключение, если стек пуст.
    }
    return top->value;                               // Возвращаем значение верхнего элемента.
}

// Функция для проверки, пуст ли стек
bool isEmpty(StackNode* top) {
    return top == nullptr;                           // Возвращаем true, если top равен nullptr, иначе false.
}

// Функция для определения приоритета операций
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;            // Операторы сложения и вычитания имеют приоритет 1.
    if (op == '*' || op == '/') return 2;            // Операторы умножения и деления имеют приоритет 2.
    return 0;                                        // Другие символы (например, скобки) имеют приоритет 0.
}

// Функция для выполнения арифметической операции над двумя операндами
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;                      // Сложение.
        case '-': return a - b;                      // Вычитание.
        case '*': return a * b;                      // Умножение.
        case '/': 
            if (b == 0) throw runtime_error("Division by zero"); // Проверка деления на ноль.
            return a / b;                            // Деление.
        default: throw runtime_error("Invalid operator"); // Исключение для недопустимого оператора.
    }
}

// Преобразование выражения в постфиксную нотацию
string infixToPostfix(const string& expression) {
    StackNode* operators = nullptr;                  // Инициализируем пустой стек для операторов.
    string postfix;                                  // Переменная для хранения постфиксной нотации.

    

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];                     // Текущий символ выражения.
        
        if (isspace(ch)) continue;                   // Пропускаем пробелы.
        
        if (isdigit(ch)) {                           // Если символ — цифра (начало числа).
            while (i < expression.length() && isdigit(expression[i])) {  // Считываем все цифры числа.
                postfix += expression[i++];          // Добавляем цифру к постфиксной строке.
            }
            postfix += ' ';                          // Разделяем числа пробелом в постфиксной строке.
            --i;                                     // Корректируем индекс, так как for-loop увеличит его снова.
        } else if (ch == '(') {                      // Если символ — открывающая скобка.
            push(operators, ch);                     // Добавляем её в стек операторов.
        } else if (ch == ')') {                      // Если символ — закрывающая скобка.
            while (!isEmpty(operators) && peek(operators) != '(') { // Пока не найдем открывающую скобку.
                postfix += static_cast<char>(pop(operators));  // Добавляем операторы из стека в постфиксную строку.
                postfix += ' ';
            }
            if (!isEmpty(operators)) pop(operators); // Удаляем открывающую скобку из стека.
        } else {                                     // Если символ — оператор (+, -, *, /).
            while (!isEmpty(operators) && getPrecedence(peek(operators)) >= getPrecedence(ch)) {
                postfix += static_cast<char>(pop(operators));  // Добавляем оператор из стека в постфиксную строку.
                postfix += ' ';
            }
            push(operators, ch);                     // Добавляем текущий оператор в стек.
        }
    }
    
    // Выгружаем все оставшиеся операторы из стека в постфиксную строку
    while (!isEmpty(operators)) {
        postfix += static_cast<char>(pop(operators));
        postfix += ' ';
    }
    
    return postfix;                                  // Возвращаем постфиксное выражение.
}

// Функция для вычисления постфиксного выражения
int evaluatePostfix(const string& postfix) {
    StackNode* values = nullptr;                     // Инициализируем пустой стек для операндов.
    string token;                                    // Переменная для хранения числа или оператора.

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];                        // Текущий символ в постфиксном выражении.
        
        if (isspace(ch)) continue;                   // Пропускаем пробелы.
        
        if (isdigit(ch) || (ch == '-' && i + 1 < postfix.length() && isdigit(postfix[i + 1]))) {
            int num = 0;
            int sign = 1;
            if (ch == '-') {                         // Обрабатываем отрицательные числа.
                sign = -1;
                ++i;
            }
            while (i < postfix.length() && isdigit(postfix[i])) {  // Считываем все цифры числа.
                num = num * 10 + (postfix[i] - '0'); // Строим число из цифр.
                ++i;
            }
            push(values, sign * num);                // Добавляем число в стек.
            --i;                                     // Корректируем индекс, так как for-loop увеличит его снова.
        } else {                                     // Если символ — оператор (+, -, *, /).
            int b = pop(values);                     // Извлекаем правый операнд из стека.
            int a = pop(values);                     // Извлекаем левый операнд из стека.
            int result = applyOperation(a, b, ch);   // Выполняем операцию.
            push(values, result);                    // Добавляем результат в стек.
        }
    }
    
    return pop(values);                              // Возвращаем результат из стека.
}