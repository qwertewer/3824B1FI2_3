#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "TStack.h"

class TPostfix {
private:
    std::string infix;          // Инфиксная запись
    std::string postfix;        // Постфиксная запись
    std::map<char, double> variables;  // Значения переменных

    // Приоритеты операций
    int GetPriority(char op) const;

    // Проверка символов
    bool IsOperator(char c) const;
    bool IsFunction(const std::string& str, size_t& pos) const;
    bool IsDigit(char c) const;
    bool IsLetter(char c) const;
    bool IsVariable(char c) const;

    // Вспомогательные методы
    void SkipSpaces(size_t& pos) const;
    std::string GetNumber(const std::string& expr, size_t& pos) const;
    std::string GetIdentifier(const std::string& expr, size_t& pos) const;
    double ApplyOperator(char op, double a, double b) const;
    double ApplyFunction(const std::string& func, double value) const;

public:
    // Конструкторы
    TPostfix();
    TPostfix(const std::string& expr);

    // Основные методы
    void SetExpression(const std::string& expr);
    std::string GetInfix() const { return infix; }
    std::string GetPostfix() const { return postfix; }

    // Проверка и преобразование
    bool ValidateExpression();
    std::string ToPostfix();

    // Вычисление
    double Calculate();
    void InputVariables();

    // Установка значений переменных
    void SetVariable(char name, double value);
    double GetVariable(char name) const;
};

#include "TPostfix.h"

using namespace std;

// Конструкторы
TPostfix::TPostfix() : infix(""), postfix("") {}

TPostfix::TPostfix(const string& expr) : infix(expr), postfix("") {
    ValidateExpression();
}

// Установка выражения
void TPostfix::SetExpression(const string& expr) {
    infix = expr;
    postfix = "";
    variables.clear();
    ValidateExpression();
}

// Приоритет операций
int TPostfix::GetPriority(char op) const {
    switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case '^': return 3;
    case '!': return 4; // Функции (синус возьмём как !)
    case '~': return 5; // Унарный минус
    default: return 0;
    }
}

// Проверка символов
bool TPostfix::IsOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool TPostfix::IsFunction(const string& str, size_t& pos) const {
    if (pos + 3 <= str.length()) {
        string sub = str.substr(pos, 3);
        if (sub == "sin") {
            return true;
        }
    }
    return false;
}

bool TPostfix::IsDigit(char c) const {
    return c >= '0' && c <= '9' || c == '.';
}

bool TPostfix::IsLetter(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool TPostfix::IsVariable(char c) const {
    if (!IsLetter(c)) {
        return false;
    }

    return true;
}

// Вспомогательные методы
void TPostfix::SkipSpaces(size_t& pos) const {
    while (pos < infix.length() && infix[pos] == ' ') {
        pos++;
    }
}

string TPostfix::GetNumber(const string& expr, size_t& pos) const {
    string number;
    bool hasDot = false;

    while (pos < expr.length() && (IsDigit(expr[pos]) || expr[pos] == '.')) {
        if (expr[pos] == '.') {
            if (hasDot) {
                break; // Вторая точка в числе
            }
            hasDot = true;
        }
        number += expr[pos];
        pos++;
    }
    pos--; // Корректировка позиции
    return number;
}

string TPostfix::GetIdentifier(const string& expr, size_t& pos) const {
    string ident;
    while (pos < expr.length() && IsLetter(expr[pos])) {
        ident += expr[pos];
        pos++;
    }
    pos--; // Корректировка позиции
    return ident;
}

// Применение операторов
double TPostfix::ApplyOperator(char op, double a, double b) const {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            throw runtime_error("Division by zero");
        }
        return a / b;
    case '^': return pow(a, b);
    default: throw runtime_error("Unknown operator");
    }
}

// Применение функций
double TPostfix::ApplyFunction(const string& func, double value) const {
    if (func == "sin") return sin(value);
    throw runtime_error("Unknown function");
}

// Проверка корректности выражения
bool TPostfix::ValidateExpression() {
    TStack<char> parenStack(100);
    bool lastWasOperator = true;  // Начало выражения считается как оператор
    bool lastWasOperand = false;
    bool expectOperand = true;

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') {
            continue;
        }

        // Проверка на число
        if (IsDigit(c) || c == '.') {
            if (!expectOperand) {
                //errors.push_back({ "Unexpected number", static_cast<int>(i) });
                return false;
            }

            string number = GetNumber(infix, i);
            // Проверка корректности числа
            if (number.empty() || number == ".") {
                //errors.push_back({ "Invalid number format", static_cast<int>(i) });
                return false;
            }
            lastWasOperator = false;
            lastWasOperand = true;
            expectOperand = false;
            continue;
        }

        // Проверка на функцию (sin)
        if (c == 's') {
            if (i + 2 < infix.length() && infix.substr(i, 3) == "sin") {
                if (!expectOperand) {
                    //errors.push_back({ "Unexpected function", static_cast<int>(i) });
                    return false;
                }
                i += 2; // Пропускаем "in"
                lastWasOperator = true;
                lastWasOperand = false;
                continue;
            }
        }

        // Проверка на переменную
        if (IsVariable(c)) {
            if (!expectOperand) {
                //errors.push_back({ "Unexpected variable", static_cast<int>(i) });
                return false;
            }
            lastWasOperator = false;
            lastWasOperand = true;
            expectOperand = false;
            continue;
        }

        

        // Проверка на унарный минус
        if (c == '-' && (lastWasOperator || i == 0 || infix[i - 1] == '(')) {
            // Это унарный минус
            if (!expectOperand) {
                //errors.push_back({ "Unexpected unary minus", static_cast<int>(i) });
                return false;
            }
            lastWasOperator = true;
            continue;
        }

        // Проверка на бинарный оператор
        if (IsOperator(c)) {
            if (expectOperand) {
                //errors.push_back({ "Unexpected operator", static_cast<int>(i) });
                return false;
            }
            lastWasOperator = true;
            lastWasOperand = false;
            expectOperand = true;
            continue;
        }

        // Проверка на скобки
        if (c == '(') {
            parenStack.Push(c);
            lastWasOperator = true;
            expectOperand = true;
            continue;
        }

        if (c == ')') {
            if (expectOperand || parenStack.IsEmpty()) {
                //errors.push_back({ "Mismatched parenthesis", static_cast<int>(i) });
                return false;
            }
            parenStack.Pop();
            lastWasOperator = false;
            lastWasOperand = true;
            expectOperand = false;
            continue;
        }

        // Неизвестный символ
        //errors.push_back({ "Unknown character", static_cast<int>(i) });
        return false;
    }

    // Проверка ожидания операнда в конце
    if (expectOperand) {
        //errors.push_back({ "Expression ends with operator", static_cast<int>(infix.length()) });
        return false;
    }

    // Проверка скобок
    if (!parenStack.IsEmpty()) {
        //errors.push_back({ "Unclosed parenthesis", static_cast<int>(infix.length()) });
        return false;
    }

    return 1;
}

// Преобразование в постфиксную запись
string TPostfix::ToPostfix() {
    if (!ValidateExpression()) {
        throw runtime_error("Invalid expression");
    }

    TStack<char> opStack(100);
    postfix = "";
    bool lastWasOperator = true;

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') {
            continue;
        }

        // Число
        else if (IsDigit(c)) {
            string number = GetNumber(infix, i);
            postfix += number + " ";
            lastWasOperator = false;
            continue;
        }
        // Функция sin
        else if (c == 's' && IsFunction(infix, i)) {
            // Код 'f' для функции в стеке
            opStack.Push('!');
            // Пропускаем имя функции
            string func = infix.substr(i, 3);
            i += 2; // Пропускаем "in"
            lastWasOperator = true;
        }
        // Унарный минус
        else if (c == '-' && (lastWasOperator || i == 0 || infix[i - 1] == '(')) {
            opStack.Push('~'); // 'u' для унарного минуса
            continue;
        }

        // Переменная
        else if (IsVariable(c)) {
            postfix += c;
            postfix += " ";
            lastWasOperator = false;
            continue;
        }
        
        // Открывающая скобка
        else if (c == '(') {
            opStack.Push(c);
            lastWasOperator = true;
            continue;
        }

        // Закрывающая скобка
        else if (c == ')') {
            while (!opStack.IsEmpty() && opStack.Peek() != '(') {
                postfix += opStack.Pop();
                postfix += " ";
            }
            if (!opStack.IsEmpty() && opStack.Peek() == '(') {
                opStack.Pop();
            }
            // Если на вершине функция
            lastWasOperator = false;
            continue;
        }

        // Бинарный оператор
        else if (IsOperator(c)) {
            while (!opStack.IsEmpty() &&
                GetPriority(opStack.Peek()) >= GetPriority(c) &&
                opStack.Peek() != '(') {
                postfix += opStack.Pop();
                postfix += " ";
            }
            opStack.Push(c);
            lastWasOperator = true;
            continue;
        }
    }

    // Выталкиваем оставшиеся операторы
    while (!opStack.IsEmpty()) {
        postfix += opStack.Pop();
        postfix += " ";
    }

    // Удаляем лишний пробел в конце
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

// Вычисление выражения
double TPostfix::Calculate() {
    if (postfix.empty()) {
        ToPostfix();
    }

    TStack<double> calcStack(100);
    istringstream iss(postfix);
    string token;

    while (iss >> token) {
        // Число
        if (IsDigit(token[0]) || (token[0] == '-' && token.length() > 1 && IsDigit(token[1]))) {
            double value = stod(token);
            calcStack.Push(value);
        }
        // Функция sin
        else if (token == "!") {
            if (calcStack.IsEmpty()) {
                throw runtime_error("Not enough operands for function");
            }
            double arg = calcStack.Pop();
            calcStack.Push(sin(arg));
        }
        // Унарный минус
        else if (token == "~") {
            if (calcStack.IsEmpty()) {
                throw runtime_error("Not enough operands for unary minus");
            }
            double value = calcStack.Pop();
            calcStack.Push(-value);
        }
        // Переменная
        else if (IsVariable(token[0])) {
            if (variables.find(token[0]) == variables.end()) {
                throw runtime_error("Variable " + string(1, token[0]) + " not defined");
            }
            calcStack.Push(variables[token[0]]);
        }
        // Бинарный оператор
        else if (token.length() == 1 && IsOperator(token[0])) {
            if (calcStack.GetSize() < 2) {
                throw runtime_error("Not enough operands for operator");
            }
            double b = calcStack.Pop();
            double a = calcStack.Pop();
            double result = ApplyOperator(token[0], a, b);
            calcStack.Push(result);
        }
        else {
            throw runtime_error("Unknown token in postfix expression");
        }
    }

    if (calcStack.GetSize() != 1) {
        throw runtime_error("Invalid expression evaluation");
    }

    return calcStack.Pop();
}

// Ввод переменных
void TPostfix::InputVariables() {
    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (IsVariable(c) && variables.find(c) == variables.end()) {
            cout << "Enter value for variable " << c << ": ";
            double value;
            cin >> value;
            variables[c] = value;
        }
    }
}

// Установка значений переменных
void TPostfix::SetVariable(char name, double value) {
    if (!IsVariable(name)) {
        throw invalid_argument("Invalid variable name");
    }
    variables[name] = value;
}

double TPostfix::GetVariable(char name) const {
    if (variables.find(name) == variables.end()) {
        throw runtime_error("Variable not found");
    }
    return variables.at(name);
}