#include "Stack.h"

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);
    
    try {
        string postfix = infixToPostfix(expression);
        int result = evaluatePostfix(postfix);
        cout << "Result: " << result << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}