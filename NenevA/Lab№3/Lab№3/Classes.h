#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cmath>
#include <stdexcept>
#include <cctype>
#include <algorithm>

//Структура для упрощения работы
struct Token {
    std::string value;
    size_t start_pos;
    size_t end_pos;
};

// Собственное исключение для ошибок в выражении
// Хранит текст ошибки и список позиций, где она возникла
class ExpressionError : public std::runtime_error {
private:
    std::vector<size_t> error_positions;
public:
    ExpressionError(const std::string& msg, std::vector<size_t> positions) : std::runtime_error(msg), error_positions(std::move(positions)) {}

    const std::vector<size_t>& getPositions() const {
        return error_positions;
    }
};

template<typename T>
class TStack {
private:
    std::vector<T> elements;
public:
    bool empty() const;
    size_t size() const;
    void push(const T& element);
    void pop();
    T& top();
    const T& top() const;
};

template <class T>
bool TStack<T> ::empty() const {
    return elements.empty();
}

template <class T>
size_t TStack<T> ::size() const {
    return elements.size();
}

template <class T>
void TStack<T> ::push(const T& element) {
    elements.push_back(element);
}

template <class T>
void TStack<T> ::pop() {
    if (!elements.empty()) {
        elements.pop_back();
    }
    else {
        throw std::out_of_range("Stack<T>::pop(): empty stack");
    }
}

template <class T>
T& TStack<T> ::top() {
    if (!elements.empty()) {
        return elements.back();
    }
    else {
        throw std::out_of_range("Stack<T>::top(): empty stack");
    }
}

template <class T>
const T& TStack<T> ::top() const {
    if (!elements.empty()) {
        return elements.back();
    }
    else {
        throw std::out_of_range("Stack<T>::top(): empty stack");
    }
}

class TPostfix {
private:
    std::map<std::string, double> variables;

    // Проверка на бинарный оператор
    bool isBinaryOperator(const std::string& token) const;
    // Проверка на унарный минус
    bool isUnaryOperator(const std::string& token) const;

    // Общая проверка на любой оператор
    bool isOperator(const std::string& token) const;

    //Проверка на синус
    bool isFunction(const std::string& token) const;

    //Проверка на число
    bool isNumber(const std::string& token) const;

    //Проверка на переменную
    bool isVariable(const std::string& token) const;

    // Приоритет операторов: унарный минус имеет выше приоритет, чем умножение/деление
    int getPrecedence(const std::string& op) const;

    // Ассоциативность: унарный минус — правая ассоциативность
    bool isLeftAssociative(const std::string& op) const;

    // Проверка корректности последовательности токенов
    void validateTokenSequence(const std::vector<Token>& tokens);

    // Обработка унарного минуса: заменяем "-" на "u-" в случаях, когда это унарный оператор
    std::vector<Token> processUnaryMinus(const std::vector<Token>& tokens);

    //Превращение в постфиксную запись
    std::vector<Token> toPostfix(const std::vector<Token>& infixTokens);

    double evaluatePostfix(const std::vector<Token>& postfixTokens);

    // Токенизация с отслеживанием позиций
    std::vector<Token> tokenize(const std::string& expression);

public:
    //Метод для подсчета значения выражения
    double evaluate(const std::string& expression);
    //Для ввода в тестах
    void TPostfix::setVariable(const std::string& name, double value);

    bool TPostfix::hasVariable(const std::string& name) const;
    // Очистка сохраненных значений переменных
    void clearVariables();
};


bool TPostfix::isBinaryOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool TPostfix::isUnaryOperator(const std::string& token) const {
    return token == "u-";
}

bool TPostfix::isOperator(const std::string& token) const {
    return isBinaryOperator(token) || isUnaryOperator(token);
}

bool TPostfix::isFunction(const std::string& token) const {
    return token == "sin";
}

bool TPostfix::isNumber(const std::string& token) const {
    char* end;
    strtod(token.c_str(), &end);
    return end != token.c_str() && *end == '\0';
}

bool TPostfix::isVariable(const std::string& token) const {
    if (token.empty() || isOperator(token) || isFunction(token) || token == "(" || token == ")") {
        return false;
    }
    return std::all_of(token.begin(), token.end(), ::isalpha);
}

int TPostfix::getPrecedence(const std::string& op) const {
    if (isUnaryOperator(op)) {
        return 3;
    }
    if (op == "+" || op == "-") {
        return 1;
    }
    if (op == "*" || op == "/") {
        return 2;
    }
    if (isFunction(op)) {
        return 3;
    }
    return 0;
}

bool TPostfix::isLeftAssociative(const std::string& op) const {
    if (isUnaryOperator(op)) {
        return false;
    }
    return op == "+" || op == "-" || op == "*" || op == "/";
}

//Функция для проверки корректности выражения
void TPostfix::validateTokenSequence(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        throw ExpressionError("Empty expression", {});
    }

    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& current = tokens[i];

        // Проверка на неизвестный токен
        if (!isNumber(current.value) && !isVariable(current.value) &&
            !isOperator(current.value) && !isFunction(current.value) &&
            current.value != "(" && current.value != ")") {

            throw ExpressionError("Unknown token: '" + current.value + "'", { current.start_pos });
        }

        // Проверка первой позиции выражения
        if (i == 0) {
            // Разрешаем унарные операторы, операнды, скобки и функции в начале
            if (isBinaryOperator(current.value)) {
                throw ExpressionError("Binary operator cannot be at the start of expression", { current.start_pos });
            }
            continue;
        }

        const Token& prev = tokens[i - 1];
        bool both_binary = isBinaryOperator(current.value) && isBinaryOperator(prev.value);
        bool both_unary = isUnaryOperator(current.value) && isUnaryOperator(prev.value);

        //Проверка на два оператора подряд
        if (both_binary || both_unary) {
            std::string error_msg = both_binary ? "Two binary operators in a row" : "Two unary operators in a row";
            throw ExpressionError(error_msg, { prev.start_pos, current.start_pos });
        }

        // Проверка на оператор после закрывающей скобки
        if (isBinaryOperator(current.value) && prev.value == ")") {
            continue;
        }

        // Проверка на унарный оператор после закрывающей скобки
        if (isUnaryOperator(current.value) && prev.value == ")") {
            throw ExpressionError("Unary operator cannot follow closing bracket", { prev.end_pos, current.start_pos });
        }

        // Проверка на открывающую скобку после операнда (подразумевает неуказанное умножение)
        if (current.value == "(" && (isNumber(prev.value) || isVariable(prev.value) || prev.value == ")")) {
            throw ExpressionError("Missing operator before opening bracket (implied multiplication is not available)", { prev.end_pos, current.start_pos });
        }

        // Проверка на операнд после закрывающей скобки
        if ((isNumber(current.value) || isVariable(current.value) || isFunction(current.value)) && prev.value == ")") {
            throw ExpressionError("Missing operator after closing bracket (implied multiplication is not available)", { prev.end_pos, current.start_pos });
        }

        // Проверка на функцию после операнда
        if (isFunction(current.value) && (isNumber(prev.value) || isVariable(prev.value) || prev.value == ")")) {
            throw ExpressionError("Missing operator before function (implied multiplication is not available)", { prev.end_pos, current.start_pos });
        }
    }

    // Проверка последнего токена отдельно
    const Token& last = tokens.back();
    if (isOperator(last.value) || last.value == "(" || isFunction(last.value)) {
        std::string error_msg;
        if (isUnaryOperator(last.value)) {
            error_msg = "Expression cannot end with unary operator";
        }
        else if (isBinaryOperator(last.value)) {
            error_msg = "Expression cannot end with binary operator";
        }
        else if (last.value == "(") {
            error_msg = "Expression cannot end with opening bracket";
        }
        else {
            error_msg = "Expression cannot end with function (missing arguments)";
        }

        throw ExpressionError(error_msg, { last.start_pos });
    }
}

std::vector<Token> TPostfix::processUnaryMinus(const std::vector<Token>& tokens) {
    std::vector<Token> processedTokens;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& currentToken = tokens[i];
        if (currentToken.value == "-") {
            bool isUnary = false;
            // Унарный минус в начале выражения
            if (i == 0) {
                isUnary = true;
            }
            // Унарный минус после другого оператора, открывающей скобки или функции
            else {
                const Token& prevToken = tokens[i - 1];
                if (isOperator(prevToken.value) || prevToken.value == "(" || isFunction(prevToken.value)) {
                    isUnary = true;
                }
            }
            Token newToken = currentToken;
            newToken.value = isUnary ? "u-" : "-";
            processedTokens.push_back(newToken);
        }
        else {
            processedTokens.push_back(currentToken);
        }
    }
    return processedTokens;
}

std::vector<Token> TPostfix::toPostfix(const std::vector<Token>& infixTokens) {
    std::vector<Token> postfixTokens;
    TStack<Token> opStack;
    std::vector<size_t> open_paren_positions;

    //Реализация для избегания ошибок с индексами
    for (const auto& token : infixTokens) {
        if (isNumber(token.value) || isVariable(token.value)) {
            postfixTokens.push_back(token);
        }
        else if (isFunction(token.value)) {
            opStack.push(token);
        }
        else if (token.value == "(") {
            opStack.push(token);
            open_paren_positions.push_back(token.start_pos);
        }
        else if (token.value == ")") {
            if (open_paren_positions.empty()) {
                throw ExpressionError("Mismatched bracket: extra closing bracket", { token.start_pos });
            }
            open_paren_positions.pop_back();

            while (!opStack.empty() && opStack.top().value != "(") {
                postfixTokens.push_back(opStack.top());
                opStack.pop();
            }
            if (opStack.empty()) {
                throw ExpressionError("Mismatched bracket: extra closing bracket", { token.start_pos });
            }
            opStack.pop();
            if (!opStack.empty() && isFunction(opStack.top().value)) {
                postfixTokens.push_back(opStack.top());
                opStack.pop();
            }
        }
        else if (isOperator(token.value)) {
            while (!opStack.empty() && opStack.top().value != "(" &&
                ((isLeftAssociative(token.value) && getPrecedence(token.value) <= getPrecedence(opStack.top().value)) ||
                    (!isLeftAssociative(token.value) && getPrecedence(token.value) < getPrecedence(opStack.top().value)))) {
                postfixTokens.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }

    // Проверка на незакрытые скобки
    if (!open_paren_positions.empty()) {
        throw ExpressionError("Mismatched bracket: unclosed opening bracket", open_paren_positions);
    }

    while (!opStack.empty()) {
        postfixTokens.push_back(opStack.top());
        opStack.pop();
    }

    return postfixTokens;
}

double TPostfix::evaluatePostfix(const std::vector<Token>& postfixTokens) {
    TStack<double> stack;
    //Упрощенная реализация чтобы не перепутать индексы
    for (const Token& token : postfixTokens) {
        if (isNumber(token.value)) {
            stack.push(std::stod(token.value));
        }
        else if (isVariable(token.value)) {
            if (variables.find(token.value) == variables.end()) {
                double value;
                std::cout << "Enter value for variable '" << token.value << "': ";
                std::cin >> value;
                variables[token.value] = value;
            }
            stack.push(variables[token.value]);
        }
        else if (isFunction(token.value)) {
            if (stack.size() < 1) {
                throw ExpressionError("Not enough operands for function '" + token.value + "'", { token.start_pos });
            }
            double operand = stack.top(); stack.pop();
            if (token.value == "sin") {
                stack.push(sin(operand));
            }
            else {
                throw ExpressionError("Unknown function: '" + token.value + "'", { token.start_pos });
            }
        }
        else if (isOperator(token.value)) {
            // Обработка унарного оператора
            if (isUnaryOperator(token.value)) {
                if (stack.size() < 1) {
                    throw ExpressionError("Not enough operands for unary operator '-'", { token.start_pos });
                }
                double operand = stack.top(); stack.pop();
                stack.push(-operand);
            }
            // Обработка бинарного оператора
            else {
                if (stack.size() < 2) {
                    throw ExpressionError("Not enough operands for operator '" + token.value + "'", { token.start_pos });
                }
                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();

                if (token.value == "+") {
                    stack.push(operand1 + operand2);
                }
                else if (token.value == "-") {
                    stack.push(operand1 - operand2);
                }
                else if (token.value == "*") {
                    stack.push(operand1 * operand2);
                }
                else if (token.value == "/") {
                    if (operand2 == 0) {
                        throw ExpressionError("Division by zero", { token.start_pos });
                    }
                    stack.push(operand1 / operand2);
                }
            }
        }
    }

    if (stack.size() != 1) {
        throw ExpressionError("Invalid expression: extra operands left on stack", {});
    }
    return stack.top();
}

std::vector<Token> TPostfix::tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    std::string token;
    size_t current_pos = 1; // Позиции начинаются с 1

    for (char ch : expression) {
        if (std::isspace(ch)) {
            current_pos++;
            continue;
        }

        if (ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (!token.empty()) {
                tokens.push_back({ token, current_pos - token.size(), current_pos - 1 });
                token.clear();
            }
            tokens.push_back({ std::string(1, ch), current_pos, current_pos });
            current_pos++;
        }
        else {
            token += ch;
            current_pos++;
        }
    }

    if (!token.empty()) {
        tokens.push_back({ token, current_pos - token.size(), current_pos - 1 });
    }

    return tokens;
}

void TPostfix::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

bool TPostfix::hasVariable(const std::string& name) const {
    return variables.find(name) != variables.end();
}

double TPostfix::evaluate(const std::string& expression) {
    try {
        std::vector<Token> infixTokens = tokenize(expression);
        infixTokens = processUnaryMinus(infixTokens);
        validateTokenSequence(infixTokens);

        std::vector<Token> postfixTokens = toPostfix(infixTokens);
        return evaluatePostfix(postfixTokens);
    }
    catch (const ExpressionError& e) {
        std::cerr << "Error: " << e.what() << "\n";
        if (!e.getPositions().empty()) {
            std::cerr << "Error positions: ";
            for (size_t pos : e.getPositions()) {
                std::cerr << pos << " ";
            }
            std::cerr << std::endl;
        }
        throw; // Перебрасывает исключение для обработки внешней частью программы
    }
}

void TPostfix::clearVariables() {
    variables.clear();
}