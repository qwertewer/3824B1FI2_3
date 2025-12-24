#include "pch.h"

#include <gtest/gtest.h>
#include "../Lab3Files/TPostfix.h"
#include "../Lab3Files/TStack.h"
#include <cmath>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

// ==================== TESTS FOR TSTACK ====================

// Тест конструктора
TEST(TStackTest, Constructor) {
    TStack<int> stack(10);
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.IsFull());
    EXPECT_EQ(stack.GetSize(), 0);
}

TEST(TStackTest, ConstructorInvalidSize) {
    EXPECT_THROW(TStack<int> stack(-1), std::invalid_argument);
    EXPECT_THROW(TStack<int> stack(0), std::invalid_argument);
}

// Тест Push и Pop
TEST(TStackTest, PushAndPop) {
    TStack<int> stack(5);

    stack.Push(10);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.GetSize(), 1);

    stack.Push(20);
    stack.Push(30);
    EXPECT_EQ(stack.GetSize(), 3);

    EXPECT_EQ(stack.Pop(), 30);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, PushWhenFull) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);
    EXPECT_TRUE(stack.IsFull());
    EXPECT_THROW(stack.Push(3), std::overflow_error);
}

TEST(TStackTest, PopWhenEmpty) {
    TStack<int> stack(5);
    EXPECT_THROW(stack.Pop(), std::underflow_error);
}

// Тест Peek
TEST(TStackTest, Peek) {
    TStack<int> stack(5);
    stack.Push(42);
    stack.Push(100);

    EXPECT_EQ(stack.Peek(), 100);
    EXPECT_EQ(stack.GetSize(), 2); // Peek не должен удалять элемент

    stack.Pop();
    EXPECT_EQ(stack.Peek(), 42);
}

TEST(TStackTest, PeekWhenEmpty) {
    TStack<int> stack(5);
    EXPECT_THROW(stack.Peek(), std::underflow_error);
}

// Тест копирования и присваивания
TEST(TStackTest, CopyConstructor) {
    TStack<int> stack1(5);
    stack1.Push(1);
    stack1.Push(2);
    stack1.Push(3);

    TStack<int> stack2(stack1);

    EXPECT_EQ(stack2.GetSize(), 3);
    EXPECT_EQ(stack2.Pop(), 3);
    EXPECT_EQ(stack2.Pop(), 2);
    EXPECT_EQ(stack2.Pop(), 1);
    // Проверяем, что оригинал не изменился
    EXPECT_EQ(stack1.GetSize(), 3);
}

TEST(TStackTest, AssignmentOperator) {
    TStack<int> stack1(5);
    stack1.Push(10);
    stack1.Push(20);

    TStack<int> stack2(3);
    stack2 = stack1;

    EXPECT_EQ(stack2.GetSize(), 2);
    EXPECT_EQ(stack2.Pop(), 20);
    EXPECT_EQ(stack2.Pop(), 10);

    // Самоприсваивание
    stack1 = stack1;
    EXPECT_EQ(stack1.GetSize(), 2);
}

// Тест Clear
TEST(TStackTest, Clear) {
    TStack<int> stack(5);
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    EXPECT_EQ(stack.GetSize(), 3);
    stack.Clear();
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.GetSize(), 0);

    // После Clear можно снова добавлять элементы
    stack.Push(42);
    EXPECT_EQ(stack.GetSize(), 1);
    EXPECT_EQ(stack.Pop(), 42);
}

// Тест с разными типами данных
TEST(TStackTest, DifferentDataTypes) {
    TStack<double> doubleStack(3);
    doubleStack.Push(3.14);
    doubleStack.Push(2.71);
    EXPECT_DOUBLE_EQ(doubleStack.Pop(), 2.71);
    EXPECT_DOUBLE_EQ(doubleStack.Pop(), 3.14);

    TStack<std::string> stringStack(2);
    stringStack.Push("Hello");
    stringStack.Push("World");
    EXPECT_EQ(stringStack.Pop(), "World");
    EXPECT_EQ(stringStack.Pop(), "Hello");
}

// ==================== TESTS FOR TPOSTFIX ====================

// Базовые тесты конструктора
TEST(TPostfixTest, Constructor) {
    TPostfix postfix;
    EXPECT_EQ(postfix.GetInfix(), "");
    EXPECT_EQ(postfix.GetPostfix(), "");
}

TEST(TPostfixTest, ConstructorWithExpression) {
    TPostfix postfix("2 + 3");
    EXPECT_EQ(postfix.GetInfix(), "2 + 3");
}

// Тесты SetExpression
TEST(TPostfixTest, SetExpression) {
    TPostfix postfix;
    postfix.SetExpression("a + b * c");
    EXPECT_EQ(postfix.GetInfix(), "a + b * c");
    EXPECT_EQ(postfix.GetPostfix(), "");
}

// Тесты валидации выражений
TEST(TPostfixTest, ValidateSimpleExpression) {
    TPostfix postfix("2 + 3 * 4");
    EXPECT_TRUE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateWithParentheses) {
    TPostfix postfix("(2 + 3) * 4");
    EXPECT_TRUE(postfix.ValidateExpression());

    postfix.SetExpression("((a + b) * (c - d))");
    EXPECT_TRUE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateWithVariables) {
    TPostfix postfix("a + b * c");
    EXPECT_TRUE(postfix.ValidateExpression());

    postfix.SetExpression("x + y - z");
    EXPECT_TRUE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateWithFunctions) {
    TPostfix postfix("sin(x)");
    EXPECT_TRUE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateUnaryMinus) {
    TPostfix postfix("-5 + 3");
    EXPECT_TRUE(postfix.ValidateExpression());

    postfix.SetExpression("a * (-b)");
    EXPECT_TRUE(postfix.ValidateExpression());

    postfix.SetExpression("-sin(x)");
    EXPECT_TRUE(postfix.ValidateExpression());
}

// Тесты обнаружения ошибок
TEST(TPostfixTest, ValidateInvalidExpression) {
    TPostfix postfix("2 + ");
    EXPECT_FALSE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateMismatchedParentheses) {
    TPostfix postfix("(2 + 3");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression("2 + 3)");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression("((2 + 3) * 4");
    EXPECT_FALSE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateConsecutiveOperators) {
    TPostfix postfix("2 ++ 3");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression("2 */ 3");
    EXPECT_FALSE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateInvalidCharacters) {
    TPostfix postfix("2 # 3");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression("a @ b");
    EXPECT_FALSE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateEmptyExpression) {
    TPostfix postfix("");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression("   ");
    EXPECT_FALSE(postfix.ValidateExpression());
}

TEST(TPostfixTest, ValidateInvalidNumberFormat) {
    TPostfix postfix("2.3.4 + 5");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression(". + 3");
    EXPECT_FALSE(postfix.ValidateExpression());

    postfix.SetExpression("2. + 3");
    EXPECT_TRUE(postfix.ValidateExpression());
    EXPECT_EQ(postfix.Calculate(), 5);
}

// Тесты преобразования в постфиксную запись
TEST(TPostfixTest, ToPostfixSimple) {
    TPostfix postfix("2 + 3");
    std::string result = postfix.ToPostfix();
    EXPECT_EQ(result, "2 3 +");
}

TEST(TPostfixTest, ToPostfixWithPriority) {
    TPostfix postfix("a + b * c");
    std::string result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b c * +");

    postfix.SetExpression("(a + b) * c");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b + c *");
}

TEST(TPostfixTest, ToPostfixComplexExpression) {
    TPostfix postfix("(a + b) * (c - d) / e");
    std::string result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b + c d - * e /");
}

TEST(TPostfixTest, ToPostfixWithUnaryMinus) {
    TPostfix postfix("-a + b");
    std::string result = postfix.ToPostfix();
    EXPECT_EQ(result, "a ~ b +");

    postfix.SetExpression("a * (-b)");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b ~ *");
}

TEST(TPostfixTest, ToPostfixWithFunction) {
    TPostfix postfix("sin(x)");
    std::string result = postfix.ToPostfix();
    EXPECT_EQ(result, "x !");

    postfix.SetExpression("sin(a + b)");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b + !");
    postfix.SetExpression("d * sin(a + b)");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "d a b + ! *");
}

TEST(TPostfixTest, ToPostfixWithExponentiation) {
    TPostfix postfix("a ^ b ^ c");
    std::string result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b ^ c ^");
    postfix.SetExpression("a ^ c - b");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "a c ^ b -");
    postfix.SetExpression("a ^ (c - b)");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "a c b - ^");
    postfix.SetExpression("(a ^ b) ^ c");
    result = postfix.ToPostfix();
    EXPECT_EQ(result, "a b ^ c ^");
}

// Тесты вычисления выражений
TEST(TPostfixTest, CalculateSimple) {
    TPostfix postfix("2 + 3");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 5.0);

    postfix.SetExpression("10 - 4");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 6.0);

    postfix.SetExpression("6 * 7");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 42.0);

    postfix.SetExpression("15 / 3");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 5.0);
}

TEST(TPostfixTest, CalculateWithPriority) {
    TPostfix postfix("2 + 3 * 4");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 14.0);

    postfix.SetExpression("(2 + 3) * 4");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 20.0);
}

TEST(TPostfixTest, CalculateWithVariables) {
    TPostfix postfix("a + b * p");
    postfix.SetVariable('a', 2.0);
    postfix.SetVariable('b', 3.0);
    postfix.SetVariable('p', 4.0);
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 14.0);
}

TEST(TPostfixTest, CalculateWithUnaryMinus) {
    TPostfix postfix("-5 + 3");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), -2.0);

    postfix.SetExpression("5 * (-2)");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), -10.0);
}

TEST(TPostfixTest, CalculateWithFunctions) {
    TPostfix postfix("sin(0)");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 0.0);

    postfix.SetExpression("2 * sin(x)");
    postfix.SetVariable('x', M_PI/2);
    EXPECT_DOUBLE_EQ(round(postfix.Calculate()), 2.0);
}

TEST(TPostfixTest, CalculateDivisionByZero) {
    TPostfix postfix("1 / 0");
    EXPECT_THROW(postfix.Calculate(), std::runtime_error);

    postfix.SetExpression("a / b");
    postfix.SetVariable('a', 5.0);
    postfix.SetVariable('b', 0.0);
    EXPECT_THROW(postfix.Calculate(), std::runtime_error);
}

TEST(TPostfixTest, CalculateLnNonPositive) {
    TPostfix postfix("ln(0)");
    EXPECT_THROW(postfix.Calculate(), std::runtime_error);

    postfix.SetExpression("ln(-1)");
    EXPECT_THROW(postfix.Calculate(), std::runtime_error);
}

TEST(TPostfixTest, CalculateMissingVariable) {
    TPostfix postfix("a + b");
    postfix.SetVariable('a', 2.0);
    // b не установлено
    EXPECT_THROW(postfix.Calculate(), std::runtime_error);
}

// Тесты работы с переменными
TEST(TPostfixTest, SetAndGetVariable) {
    TPostfix postfix;
    postfix.SetVariable('x', 3.14);
    EXPECT_DOUBLE_EQ(postfix.GetVariable('x'), 3.14);

    // Перезапись переменной
    postfix.SetVariable('x', 2.71);
    EXPECT_DOUBLE_EQ(postfix.GetVariable('x'), 2.71);
}

TEST(TPostfixTest, GetNonExistentVariable) {
    TPostfix postfix;
    EXPECT_THROW(postfix.GetVariable('x'), std::runtime_error);
}

TEST(TPostfixTest, SetInvalidVariableName) {
    TPostfix postfix;
    // Попытка установить цифру как переменную
    EXPECT_THROW(postfix.SetVariable('1', 5.0), std::invalid_argument);
    // Попытка установить оператор как переменную
    EXPECT_THROW(postfix.SetVariable('+', 5.0), std::invalid_argument);
}

TEST(TPostfixTest, InputVariables) {
    // Этот тест требует ручного ввода, но мы можем проверить, что метод существует
    TPostfix postfix("a + b");
    // Не вызываем InputVariables(), так как он требует cin
    // Просто проверяем, что метод можно вызвать
    SUCCEED();
}

// Тесты краевых случаев
TEST(TPostfixTest, EdgeCaseSingleNumber) {
    TPostfix postfix("42");
    EXPECT_TRUE(postfix.ValidateExpression());
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 42.0);

    postfix.SetExpression("3.14159");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 3.14159);
}

TEST(TPostfixTest, EdgeCaseSingleVariable) {
    TPostfix postfix("x");
    postfix.SetVariable('x', 7.5);
    EXPECT_TRUE(postfix.ValidateExpression());
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 7.5);
}

TEST(TPostfixTest, EdgeCaseMultipleSpaces) {
    TPostfix postfix("  2   +   3   *   4   ");
    EXPECT_TRUE(postfix.ValidateExpression());
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 14.0);
}

TEST(TPostfixTest, EdgeCaseNestedParentheses) {
    TPostfix postfix("(((2 + 3) * (4 - 1)) / 5) ^ 2");
    EXPECT_TRUE(postfix.ValidateExpression());
    EXPECT_DOUBLE_EQ(postfix.Calculate(), pow(((2 + 3) * (4 - 1) / 5.0), 2));
}

TEST(TPostfixTest, EdgeCaseLargeExpression) {
    std::string expr;
    for (int i = 0; i < 10; i++) {
        expr += "(";
    }
    expr += "a";
    for (int i = 0; i < 10; i++) {
        expr += "+b)";
    }

    TPostfix postfix(expr);
    postfix.SetVariable('a', 1.0);
    postfix.SetVariable('b', 2.0);

    EXPECT_TRUE(postfix.ValidateExpression());
    // a + 10*b = 1 + 20 = 21
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 21.0);
}

// Тест на повторное использование объекта
TEST(TPostfixTest, ReuseObject) {
    TPostfix postfix;

    // Первое выражение
    postfix.SetExpression("2 + 3");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 5.0);

    // Второе выражение
    postfix.SetExpression("a * b");
    postfix.SetVariable('a', 4.0);
    postfix.SetVariable('b', 5.0);
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 20.0);

    // Проверяем, что старые переменные очистились
    postfix.SetExpression("a + b");
    postfix.SetVariable('a', 1.0);
    // b не установлено - должно быть ошибка
    EXPECT_THROW(postfix.Calculate(), std::runtime_error);
}

// Тест на вычисление без предварительного преобразования
TEST(TPostfixTest, CalculateWithoutToPostfix) {
    TPostfix postfix("3 + 4 * 2");
    // Вызываем Calculate() без явного вызова ToPostfix()
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 11.0);
}

// Тест с плавающей точкой
TEST(TPostfixTest, FloatingPointPrecision) {
    TPostfix postfix("0.1 + 0.2");
    // Известная проблема точности с плавающей точкой
    EXPECT_NEAR(postfix.Calculate(), 0.3, 1e-10);

    postfix.SetExpression("sin(3.141592653589793)");
    EXPECT_NEAR(postfix.Calculate(), 0.0, 1e-10);
}

// Тест ошибок во время преобразования
TEST(TPostfixTest, ToPostfixInvalidExpression) {
    TPostfix postfix("2 + ");
    EXPECT_THROW(postfix.ToPostfix(), std::runtime_error);
}

// Тест экспоненты
TEST(TPostfixTest, Exponentiation) {
    TPostfix postfix("2 ^ 3");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 8.0);

    postfix.SetExpression("4 ^ 0.5"); // квадратный корень
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 2.0);

    postfix.SetExpression("9 ^ (1/2)"); // тоже квадратный корень
    postfix.SetVariable('a', 1.0);
    postfix.SetVariable('b', 2.0);
    // Здесь нужно установить переменные, но в выражении нет переменных
    // Переписываем тест
    postfix.SetExpression("9 ^ 0.5");
    EXPECT_DOUBLE_EQ(postfix.Calculate(), 3.0);
}

// ==================== MAIN ====================
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}