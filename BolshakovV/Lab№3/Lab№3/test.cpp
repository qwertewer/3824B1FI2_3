#include "pch.h"
#include "../Project1/Header.h"
#include <sstream>

TEST(Stack_test, test_emp) { //проверка методов size, empty, push, top, pop
	TStack<int> s1;
	EXPECT_EQ(s1.size(), 0);
	EXPECT_TRUE(s1.empty());

	s1.push(5);
	s1.push(45);

	EXPECT_EQ(s1.size(), 2);
	EXPECT_EQ(s1.top(), 45);
	EXPECT_FALSE(s1.empty());

	s1.pop();
	s1.pop();
	EXPECT_EQ(s1.size(), 0);
	EXPECT_TRUE(s1.empty());
}

TEST(Stack_test, test_error) { //выброс исключений
	TStack<double>s;
	EXPECT_THROW(s.pop(), std::runtime_error);
	try {
		s.pop();
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "Stack is empty");
	}

	EXPECT_THROW(s.top(), std::runtime_error);
	try {
		s.top();
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "Stack is empty");
	}
}

TEST(Stack_test, test_swap) { //метод swap
	TStack<int>s1;
	TStack<int>s2;
	s1.push(56);
	s1.push(34);

	s1.swap(s2);

	EXPECT_EQ(s1.size(), 0);
	EXPECT_EQ(s2.size(), 2);
	EXPECT_EQ(s2.top(), 34);
}

//TPostfix
TEST(TPostfix_test0, tect_inf_correct) { //корректное создание объекта
	TPostfix expr("(a+b*c)*(c/d-e)+cos(1.5)");
	EXPECT_EQ(expr.GetInfix(), "(a+b*c)*(c/d-e)+cos(1.5)");
}

TEST(TPostfix_test0, test_inf_correct_1) { //корректное создание объекта

	TPostfix expr("-(a+b)*ken+cos(a)");
}

//некорректные символы
TEST(TPostfix_test0, test_inf_incorretc_symbol) {
	EXPECT_THROW(TPostfix expr("a+b!"), std::invalid_argument); //некорректный символ !
	try {
		TPostfix expr("a+b!");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "This character cannot be used in the expression. Error position: 3");
	}
}

TEST(TPostfix_test0, test_inf_incorrect_symbol) {
	EXPECT_THROW(TPostfix expr("a + b"), std::invalid_argument); //пробел - некорректный символ
	try {
		TPostfix expr("a + b");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "This character cannot be used in the expression. Error position: 1");
	}
}
//ошибки со скобками
TEST(TPostfix_test0, test_inf_bracket) { //символ, отличный от знака операции (и от знака самой скобки), перед (
	EXPECT_THROW(TPostfix expr("a+b(c-d)"), std::invalid_argument);
	try {
		TPostfix expr("a+b(c-d)");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Only operations (+,-,*,/) and symbol ( can be placed before the parenthesis. Error position: 2");
	}
}
TEST(TPostfix_test0, test_inf_bracket_1) {
	EXPECT_THROW(TPostfix expr("a+78(c-d)"), std::invalid_argument);
	try {
		TPostfix expr("a+78(c-d)");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Only operations (+,-,*,/) and symbol ( can be placed before the parenthesis. Error position: 3");
	}
}
TEST(TPostfix_test0, test_inf_bracket_2) { //некорректный символ после (
	EXPECT_THROW(TPostfix expr("a+(c-d)b)"), std::invalid_argument);
	try {
		TPostfix expr("a+(c-d)b");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Only operations (+,-,*,/) and symbol ) can be placed after the parenthesis. Error position: 7");
	}
}
TEST(TPostfix_test0, test_inf_bracket_3) {
	try {
		TPostfix expr("a+(c-d)17");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Only operations (+,-,*,/) and symbol ) can be placed after the parenthesis. Error position: 7");
	}
}
TEST(TPostfix_test0, test_inf_bracket_4) {  //некорректное количество открывающих/закрывающих скобок
	EXPECT_THROW(TPostfix expr("cos(a"), std::invalid_argument);
	try {
		TPostfix expr("cos(a");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The closing parenthesis is missing. The position of the opening bracket for which there is no closing bracket: 3");
	}
}
TEST(TPostfix_test0, test_inf_bracket_5) {
	EXPECT_THROW(TPostfix expr("(a+(b+c)"), std::invalid_argument);
	try {
		TPostfix expr("(a+(b+c)");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The closing parenthesis is missing. The position of the opening bracket for which there is no closing bracket: 0");
	}
}
TEST(TPostfix_test0, test_inf_bracket_6) {
	EXPECT_THROW(TPostfix expr("c+(a+b))"), std::invalid_argument);
	try {
		TPostfix expr("c+(a+b))");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Extra closing parenthesis. Error position: 7");
	}
}
TEST(TPostfix_test0, test_inf_bracket_7) {  //исключения не происходит
	TPostfix expr("((a+b))");
}
TEST(TPostfix_test0, test_inf_bracket_8) { //пустые скобки
	EXPECT_THROW(TPostfix expr("a+b+()"), std::invalid_argument);
	try {
		TPostfix expr("a+b+()");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "An invalid expression of the form: (). Error position: 5");
	}
}
TEST(TPostfix_test0, test_inf_bracket_9) { //также некорректный символ после )
	EXPECT_THROW(TPostfix expr("(a+b)(c+d)"), std::invalid_argument);
	try {
		TPostfix expr("(a+b)(c+d)");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Only operations (+,-,*,/) and symbol ) can be placed after the parenthesis. Error position: 5");
	}
}

//ошибки с точками
TEST(TPostfix_test0, test_inf_dot) { //точка вначале выражения
	EXPECT_THROW(TPostfix expr(".+1+5"), std::invalid_argument);
	try {
		TPostfix expr(".+1+5");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The use of the < . > symbol is incorrect. Error position: 0");
	}
}
TEST(TPostfix_test0, test_inf_dot_1) { //точка в конце выражения
	EXPECT_THROW(TPostfix expr("a+1."), std::invalid_argument);
	try {
		TPostfix expr("a+1.");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The use of the < . > symbol is incorrect. Error position: 3");
	}
}
TEST(TPostfix_test0, test_inf_dot_2) { //некорректный символ слева от точки
	EXPECT_THROW(TPostfix expr("a.1"), std::invalid_argument);
	try {
		TPostfix expr("a.1");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "There can only be a digit before the < . >. Error position: 0");
	}
}
TEST(TPostfix_test0, test_inf_dot_3) { //некорректный символ справа от точки
	EXPECT_THROW(TPostfix expr("1.a"), std::invalid_argument);
	try {
		TPostfix expr("1.a");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "There can only be a digit after the < . >. Error position: 2");
	}
}
TEST(TPostfix_test0, test_inf_dot_4) { //большое количество точек в числе
	EXPECT_THROW(TPostfix expr("a+1.34.85"), std::invalid_argument);
	try {
		TPostfix expr("a+1.34.85");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The number cannot contain more than one dot. Error position: 6");
	}
}

//ошибки с цифрами
TEST(TPostfix_test0, test_inf_digit) { //некорректный символ перед цифрой
	EXPECT_THROW(TPostfix expr("b+q1"), std::invalid_argument);
	try {
		TPostfix expr("b+q1");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The digit may be preceded by other digits, a dot, symbol (, or operation symbols (+,-,*,/). Error position: 2");
	}
}
TEST(TPostfix_test0, test_inf_digit_1) { //некорректный символ после цифры
	EXPECT_THROW(TPostfix expr("b+1q"), std::invalid_argument);
	try {
		TPostfix expr("b+1q");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The digit may be followed by other digits, a dot, symbol ), or operation symbols (+,-,*,/). Error position: 3");
	}
}
////ошибки с операциями
TEST(TPostfix_test0, test_inf_operation) { //использование операции в начале строки
	EXPECT_THROW(TPostfix expr("+a-b"), std::invalid_argument);
	try {
		TPostfix expr("+a-b");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "You cannot use operations (+) at the beginning of an expression. Error position: 0");
	}
}
TEST(TPostfix_test0, test_inf_operation_1) {//использование операции перед (
	EXPECT_THROW(TPostfix expr("(*ded+1)"), std::invalid_argument);
	try {
		TPostfix expr("(*ded+1)");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Operation after the opening parenthesis. Error position: 1");
	}
}
TEST(TPostfix_test0, test_inf_operation_2) { //унарный минус
	TPostfix expr("-a+1");
}
TEST(TPostfix_test0, test_inf_operation_3) { //унарный минус
	TPostfix expr("(-a+1)");
}
TEST(TPostfix_test0, test_inf_operation_4) {//использование операции в конце выражения
	EXPECT_THROW(TPostfix expr("a-"), std::invalid_argument);
	try {
		TPostfix expr("a-");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "You cannot use operations (-) at the end of an expression. Error position: 1");
	}
}
TEST(TPostfix_test0, test_inf_operation_5) { //использование операции перед )
	EXPECT_THROW(TPostfix expr("(b+a/)"), std::invalid_argument);
	try {
		TPostfix expr("(b+a/)");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "The operation is not applied to the operand. Error position: 4");
	}
}
TEST(TPostfix_test0, test_inf_operation_6) { //использование операции после другой операции
	EXPECT_THROW(TPostfix expr("a/-b"), std::invalid_argument);
	try {
		TPostfix expr("a/-b");
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "There is another operation before this operation (-). Error position: 2");
	}
}
TEST(TPostfix_test0, test_inf_operation_7) { //исключения нет
	TPostfix expr("cos(x)-a");
}
//получение постфиксной формы
//
TEST(TPostfix_test1, test_get_postfix_infix) {
	TPostfix expr("a+b");
	EXPECT_EQ(expr.GetInfix(), "a+b");
	EXPECT_EQ(expr.GetPostfix(), "ab+");
}
TEST(TPostfix_test1, test_get_postfix_1) {
	TPostfix expr("a-b");
	EXPECT_EQ(expr.GetPostfix(), "ab-");
}
TEST(TPostfix_test1, test_get_postfix_2) {
	TPostfix expr("a/b");
	EXPECT_EQ(expr.GetPostfix(), "ab/");
}
TEST(TPostfix_test1, test_get_postfix_3) {
	TPostfix expr("a*b");
	EXPECT_EQ(expr.GetPostfix(), "ab*");
}
TEST(TPostfix_test1, test_get_postfix_4) {
	TPostfix expr("cos(x)");
	EXPECT_EQ(expr.GetPostfix(), "xcos");
}
TEST(TPostfix_test1, test_get_postfix_5) {
	TPostfix expr("-x");
	EXPECT_EQ(expr.GetPostfix(), "x~");
}
/// 
TEST(TPostfix_test1, test_get_postfix_6) {
	TPostfix expr("-(-x)");
	EXPECT_EQ(expr.GetPostfix(), "x~~");
}
TEST(TPostfix_test1, test_get_postfix_7) { //не унарный минус
	TPostfix expr("a-(d+c)");
	EXPECT_EQ(expr.GetPostfix(), "adc+-");
}
TEST(TPostfix_test1, test_get_postfix_8) {
	TPostfix expr("(a+b*c)*(c/d-e)+(-h)/cos(x)");
	EXPECT_EQ(expr.GetPostfix(), "abc*+cd/e-*h~xcos/+");
}
TEST(TPostfix_test1, test_get_postfix_9) {//унарный минус
	TPostfix expr("-(a+b)");
	EXPECT_EQ(expr.GetPostfix(), "ab+~");
}
TEST(TPostfix_test1, test_get_postfix_10) {
	TPostfix expr("-(a+b)*k");
	EXPECT_EQ(expr.GetPostfix(), "ab+k*~");
}
TEST(TPostfix_test1, test_get_postfix_11) {
	TPostfix expr("-(a+b)/k");
	EXPECT_EQ(expr.GetPostfix(), "ab+k/~");
}
TEST(TPostfix_test1, test_get_postfix_16) {
	TPostfix expr("-3*(-4+5)");
	EXPECT_EQ(expr.GetPostfix(), "34~5+*~");
}
TEST(TPostfix_test1, test_get_postfix_12) {
	TPostfix expr("(-a+0.8)*(-h)");
	EXPECT_EQ(expr.GetPostfix(), "a~0.8+h~*");
}
TEST(TPostfix_test1, test_get_postfix_13) {
	TPostfix expr("-cos(a/3.14)");
	EXPECT_EQ(expr.GetPostfix(), "a3.14/cos~");
}
///вычисление выражений
TEST(TPostfix_test2, calc) {
	TPostfix expr("a+b");
	std::vector<double> op = { 1,2 };
	EXPECT_EQ(expr.Calculate(op), 3);
}
TEST(TPostfix_test2, calc_1) {
	TPostfix expr("a-b");
	std::vector<double> op = { 1,2 };
	EXPECT_EQ(expr.Calculate(op), -1);
}
TEST(TPostfix_test2, calc_2) {
	TPostfix expr("a*b");
	std::vector<double> op = { 1,2 };
	EXPECT_EQ(expr.Calculate(op), 2);
}
TEST(TPostfix_test2, calc_3) {
	TPostfix expr("a/b");
	std::vector<double> op = { 1,2 };
	EXPECT_EQ(expr.Calculate(op), 0.5);
}
TEST(TPostfix_test2, calc_4) {
	TPostfix expr("-h");
	std::vector<double> op = { 1 };
	EXPECT_EQ(expr.Calculate(op), -1);
}
TEST(TPostfix_test2, calc_5) {
	TPostfix expr("-1");
	std::vector<double> op; //пустой вектор, т.к. необходимо совпадение количества нечисловых переменных
	EXPECT_EQ(expr.Calculate(op), -1);
}
TEST(TPostfix_test2, calc_6) {
	TPostfix expr("cos(x)");
	double n = 3.14 / 3;
	std::vector<double> op = { n };

	EXPECT_EQ(expr.Calculate(op), std::cos(n));
}
///
TEST(TPostfix_test2, calc_7) { //использование чисел в выражении (в векторе храняться только значения переменных)
	TPostfix expr("a+b+1");
	std::vector<double> op = { 1,2 };
	EXPECT_EQ(expr.Calculate(op), 4);
}
TEST(TPostfix_test2, calc_8) { //применение унарного минуса
	TPostfix expr("-(a+b)");
	double a = 1, b = 2;
	std::vector<double> op = { a,b };
	EXPECT_EQ(expr.Calculate(op), -(a + b));
}
TEST(TPostfix_test2, calc_9) {
	TPostfix expr("-(a*b)");
	double a = 2, b = 2;
	std::vector<double> op = { a,b };
	EXPECT_EQ(expr.Calculate(op), -(a * b));
}
TEST(TPostfix_test2, calc_10) {
	TPostfix expr("-(a/b)");
	double a = 2, b = 2;
	std::vector<double> op = { a,b };
	EXPECT_EQ(expr.Calculate(op), -(a / b));
}
TEST(TPostfix_test2, calc_11) {
	TPostfix expr("-(-a)");
	double a = 2;
	std::vector<double> op = { a };
	EXPECT_EQ(expr.Calculate(op), -(-a));
}
TEST(TPostfix_test2, calc_12) { //использование всех доступных операций
	TPostfix expr("(a+b*c)*(c/d-e)+(-h)/cos(x)");
	double a = 1.1, b = 2, c = 3, e = 8.9, d = 1, h = -7, x = 2;
	std::vector<double>op = { a,b,c,d,e,h,x };
	EXPECT_EQ(expr.Calculate(op), (a + b * c) * (c / d - e) + (-h) / cos(x));
}
TEST(TPostfix_test2, calc_13) {
	TPostfix expr("-3*(-4+5)");
	std::vector<double> op;
	EXPECT_EQ(expr.Calculate(op), -3 * (-4 + 5));
}
TEST(TPostfix_test2, calc_14) { //снова использование унарного минуса
	TPostfix expr("(-a+0.8)*(-h)");
	double a = 13.2, h = -78;
	std::vector<double> op = { a,h };
	EXPECT_EQ(expr.Calculate(op), (-a + 0.8) * (-h));
}
TEST(TPostfix_test2, calc_15) {
	TPostfix expr("a/(-h+1)");
	double a = 13.2, h = -1;
	std::vector<double> op = { a,h };
	EXPECT_EQ(expr.Calculate(op), a / (-h + 1));
}
TEST(TPostfix_test2, calc_16) { //использование выражения в качестве аргумента для функции cos
	TPostfix expr("a*cos(a/b)");
	double a = 13.2, b = -1;
	std::vector<double> op = { a,b };
	EXPECT_EQ(expr.Calculate(op), a * std::cos(a / b));
}
TEST(TPostfix_test2, calc_17) { //cosa - имя переменной
	TPostfix expr("a+cosa");
	double a = 1, cosa = 2;
	std::vector<double> op = { a,cosa };
	EXPECT_EQ(expr.Calculate(op), a + cosa);
}
TEST(TPostfix_test2, calc_error) { //неправильное количество операндов в переданном векторе
	TPostfix expr("a+bmk");
	double a = 1;
	std::vector<double> op = { a };
	EXPECT_THROW(expr.Calculate(op), std::invalid_argument);

	try {
		expr.Calculate(op);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. The size of the passed vector does not match the number of operands (we are talking about non-numeric operands)");
	}
}
TEST(TPostfix_test2, calc_error_1) { //деление на ноль
	TPostfix expr("a/(b+1)");
	double a = 1, b = -1;
	std::vector<double> op = { a,b };
	EXPECT_THROW(expr.Calculate(op), std::invalid_argument);
	try {
		expr.Calculate(op);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. The expression contains a division by zero");
	}
}
/// ввод с клавиатуры
TEST(TPostfix_test3, calc_input) {
	std::stringstream ss_input("10\n");   // Подставляем заранее известные значения для переменных
	std::stringstream ss_output;

	std::cin.rdbuf(ss_input.rdbuf()); //заменяем поток ввода
	std::cout.rdbuf(ss_output.rdbuf()); //заменяем поток вывода

	TPostfix exp("x+5");
	double result = exp.Calculate_keyboard_input();

	EXPECT_EQ(result, 15.0);

	std::cin.rdbuf(std::cin.rdbuf()); // Восстанавливаем стандартный cin
	std::cout.rdbuf(std::cout.rdbuf()); // Восстанавливаем стандартный cout
}

TEST(TPostfix_test3, calc_input_1) {
	std::stringstream ss_input("10\n5\n-1\n");   // Подставляем заранее известные значения для переменных
	std::stringstream ss_output;

	std::cin.rdbuf(ss_input.rdbuf()); //заменяем поток ввода
	std::cout.rdbuf(ss_output.rdbuf()); //заменяем поток вывода

	TPostfix exp("a+b+(-c)");
	double result = exp.Calculate_keyboard_input();

	EXPECT_EQ(result, 16.0); //10+5+(-1)

	std::cin.rdbuf(std::cin.rdbuf()); // Восстанавливаем стандартный cin
	std::cout.rdbuf(std::cout.rdbuf()); // Восстанавливаем стандартный cout
}