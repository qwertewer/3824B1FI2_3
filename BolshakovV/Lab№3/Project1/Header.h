#pragma once
#include <iostream>
#include <vector>
#include <string> //для преобразования в строку
#include <cmath>

template <typename T>
class TStack {

private:
	std::vector<T> pStack;

public:

	TStack() = default; //конструктор по умолчанию

	bool empty() const {
		return pStack.empty();
	}

	size_t size() const {
		return pStack.size();
	}

	void push(const T& val) { //положить элемент на вершину
		pStack.push_back(val);
	}

	void pop() { //удалить элемент с вершины
		if (this->empty()) {
			throw std::runtime_error("Stack is empty");
		}

		pStack.pop_back();
	}

	T top() const { //получить элемент с вершины (не удаляя его из стека)
		if (this->empty()) {
			throw std::runtime_error("Stack is empty");
		}
		return pStack.back();
	}

	void swap(TStack<T>& other) { //не используется в классе TPostfix
		pStack.swap(other.pStack);
	}
};

class TPostfix {
private:
	std::string infix; //инфиксная форма
	std::string postfix;//постфиксная форма

	std::vector<std::string>lexems_infix; //лексемы инфиксной записи
	std::vector<std::string>lexems_postfix;//лексемы постфиксной записи
	std::vector<std::string> operands; //операнды
	std::vector<double> value_operands; //значения операндов

	std::vector<std::string> operations; //операции 
	std::vector<int>priority; //значения операций 

	void InfCorrect(const std::string& inf); //проверка корректности выражения
	void Parse(const std::string& inf); //метод для разделения на лексемы  
	void Forming_operands(const std::vector<std::string>& lexem_inf); //формирование уникальных операндов
	void Values(const std::vector<std::string>& operand); //метод для установки значений операндов
	
	int find_pos(const std::string& symbol, const std::vector<std::string>& vec); //вспомогательный метод для поиска позиции операции в векторе operations (используется в методах ToPostfix, Calculate)
		
	void ToPostfix();  //метод для преобразования в постфиксную форму 

public:

	TPostfix(const std::string& inf) :infix(""), postfix("") {

		operations = { "+","-","*","/","~","cos" }; // использование функции cos допустимо только с использованием скобок (иначе воспринимается как имя переменной)
		priority = { 1,1,3,3,2,4 }; //~ - унарный минус (приоритет 2 - для корректного преобразования в постфиксную форму).

		InfCorrect(inf);

		infix = inf;

		Parse(infix); //разбиваеим выражение на лексемы 

		ToPostfix(); //получаем постфиксную форму
	}

	std::string GetInfix() const { //получение инфиксной формы
		return infix;
	}

	std::string GetPostfix() const { //получение постфиксной формы
		return postfix;
	}

	double Calculate(const std::vector<double>& values); //вычисление значения выражения без использования консоли 

	double Calculate_keyboard_input(); //ввод неизвестных переменных с консоли
};

void TPostfix::InfCorrect(const std::string& inf)
{
	TStack<char> open_bracket; //стек для хранения открывающихся круглых скобок
	TStack<int> pos_open_bracket;

	std::string number;

	for (size_t pos = 0; pos < inf.size(); ++pos) {
		char ch = inf[pos];
		if (!((ch >= '(' && ch <= '+') || (ch >= '-' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))) {

			throw std::invalid_argument("This character cannot be used in the expression. Error position: " + std::to_string(pos));
		}
		else if (ch == '(') {
			if (pos > 0 && inf[pos - 1] != '(') {
				if (!(inf[pos - 1] == '+' || inf[pos - 1] == '-' || inf[pos - 1] == '*' || inf[pos - 1] == '/') && inf.substr(pos - 3, 3) != "cos") { //a( или 2(
					throw std::invalid_argument("Only operations (+,-,*,/) and symbol ( can be placed before the parenthesis. Error position: " + std::to_string(pos - 1));
				}
				else if (pos + 1 != inf.size() && inf[pos + 1] == ')') {
					throw std::invalid_argument("An invalid expression of the form: (). Error position: " + std::to_string(pos + 1));
				}
			}
			open_bracket.push(ch);
			pos_open_bracket.push(pos);
		}
		else if (ch == ')') {

			if (open_bracket.empty()) {
				throw std::invalid_argument("Extra closing parenthesis. Error position: " + std::to_string(pos));
			}
			else if (pos + 1 != inf.size() && inf[pos + 1] != ')') {
				if (!(inf[pos + 1] == '+' || inf[pos + 1] == '-' || inf[pos + 1] == '*' || inf[pos + 1] == '/')) {
					throw std::invalid_argument("Only operations (+,-,*,/) and symbol ) can be placed after the parenthesis. Error position: " + std::to_string(pos + 1)); //(...)1 или (...)a
				}
			}
			open_bracket.pop(); //удаляем корректно открывающуюся скобку  
			pos_open_bracket.pop();//удаляем её позицию  

		}
		else if (ch == '.') {
			if (pos == 0) {
				throw std::invalid_argument("The use of the < . > symbol is incorrect. Error position: " + std::to_string(pos));
			}
			else if (pos + 1 == inf.size()) {
				throw std::invalid_argument("The use of the < . > symbol is incorrect. Error position: " + std::to_string(pos));
			}
			else if (inf[pos - 1] < '0' || inf[pos - 1]>'9') {
				throw std::invalid_argument("There can only be a digit before the < . >. Error position: " + std::to_string(pos - 1));
			}
			else if (inf[pos + 1] < '0' || inf[pos + 1]>'9') {
				throw std::invalid_argument("There can only be a digit after the < . >. Error position: " + std::to_string(pos + 1));
			}

			//проверяем количество точек в числе
			int i = pos + 1;
			int count_dot = 0;
			while (i < inf.size() && (inf[i] >= '0' && inf[i] <= '9' || inf[i] == '.')) {
				if (inf[i] == '.') {
					count_dot += 1;
					break;
				}
				++i;
			}
			if (count_dot == 1) {
				throw std::invalid_argument("The number cannot contain more than one dot. Error position: " + std::to_string(i));
			}

		}
		else if (ch >= '0' && ch <= '9') {

			if (pos > 0 && (inf[pos - 1] >= 'a' && inf[pos - 1] <= 'z' || inf[pos - 1] >= 'A' && inf[pos - 1] <= 'Z')) {
				throw std::invalid_argument("The digit may be preceded by other digits, a dot, symbol (, or operation symbols (+,-,*,/). Error position: " + std::to_string(pos - 1));
			}
			else if (pos > 0 && pos + 1 != inf.size() && (inf[pos + 1] >= 'a' && inf[pos + 1] <= 'z' || inf[pos + 1] >= 'A' && inf[pos + 1] <= 'Z') /*|| inf[pos+1]=='('*/) {
				throw std::invalid_argument("The digit may be followed by other digits, a dot, symbol ), or operation symbols (+,-,*,/). Error position: " + std::to_string(pos + 1));
			}
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {

			if (pos + 1 == inf.size()) {
				std::string symb;
				symb.push_back(ch);
				throw std::invalid_argument("You cannot use operations (" + symb + ") at the end of an expression. Error position: " + std::to_string(pos));
			}
			else if (pos + 1 != inf.size() && inf[pos + 1] == ')') {
				throw std::invalid_argument("The operation is not applied to the operand. Error position: " + std::to_string(pos)); // (...+)
			}
			else if (pos > 0 && (inf[pos - 1] == '+' || inf[pos - 1] == '-' || inf[pos - 1] == '*' || inf[pos - 1] == '/')) { //a*-b - запрет
				std::string symb;
				symb.push_back(ch);
				throw std::invalid_argument("There is another operation before this operation (" + symb + "). Error position: " + std::to_string(pos));
			}

			if (ch != '-') {
				if (pos > 0 && inf[pos - 1] == '(') {
					throw std::invalid_argument("Operation after the opening parenthesis. Error position: " + std::to_string(pos)); //(+....)
				}
				else if (pos == 0) {
					std::string symb;
					symb.push_back(ch);
					throw std::invalid_argument("You cannot use operations (" + symb + ") at the beginning of an expression. Error position: " + std::to_string(pos));
				}
			}
		}

	}

	if (!open_bracket.empty()) {
		//Позиция открывающейся скобки, для которой отсутствует закрывающаяся
		throw std::invalid_argument("The closing parenthesis is missing. The position of the opening bracket for which there is no closing bracket: " + std::to_string(pos_open_bracket.top()));
	}
}

void TPostfix::Parse(const std::string& inf) {
	std::string token;
	for (size_t i = 0; i < inf.size(); ++i) {
		char ch = inf[i];

		if (ch >= '0' && ch <= '9' || ch == '.') {
			token += ch;
			while (i + 1 < inf.size() && (inf[i + 1] >= '0' && inf[i + 1] <= '9') || inf[i + 1] == '.') {
				token += inf[i + 1];
				++i;
			}

			lexems_infix.push_back(token);
			token.clear();
		}
		else if (ch == 'c' && i + 1 < inf.size() && inf.substr(i, 3) == "cos(") { // Спец-обработка функции cos 

			token += "cos";
			lexems_infix.push_back(token);
			token.clear();
			i += 2; // Проигнорировали cos

		}
		else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
			token += ch;
			while (i + 1 < inf.size() && (inf[i + 1] >= 'A' && inf[i + 1] <= 'Z') || (inf[i + 1] >= 'a' && inf[i + 1] <= 'z')) {
				token += inf[i + 1];
				++i;
			}
			lexems_infix.push_back(token);
			token.clear();
		}
		else if (ch == '-' && (i == 0 || inf[i - 1] == '(')) {
			token += '~';
			lexems_infix.push_back(token);
			token.clear();
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
			lexems_infix.push_back(std::string(1, ch)); // Просто добавляем знак оператора или скобку 
		}
	}

	Forming_operands(lexems_infix); //формируем вектор уникальных операндов
	Values(operands); //формируем значения операндов 
}

void TPostfix::Forming_operands(const std::vector<std::string>& lexem_inf)
{
	for (std::string x : lexem_inf) {
		bool uniq_elem = true;

		if (x != "cos" && (x[0] >= 'a' && x[0] <= 'z' || x[0] >= 'A' && x[0] <= 'Z' || x[0] >= '0' && x[0] <= '9')) {
			for (std::string y : operands) {
				if (x == y) {
					uniq_elem = false;
					break;
				}
			}
			if (uniq_elem == true) {
				operands.push_back(x);
			}
		}
	}
}

void TPostfix::Values(const std::vector<std::string>& operand)
{
	for (std::string op : operand) {
		if (op[0] >= '0' && op[0] <= '9') {

			bool flag_point_found = false;
			double number = 0.0;
			double divider = 10.0; //делитель

			for (char ch : op) {
				if (ch == '.') {
					flag_point_found = true;
				}
				else {
					int digit = ch - '0';
					if (!flag_point_found) {
						number = number * 10.0 + digit;
					}
					else {
						number += digit / divider;
						divider *= 10.0;
					}
				}
			}

			value_operands.push_back(number);
		}
		else {
			value_operands.push_back(0.0);
		}
	}
}

int TPostfix::find_pos(const std::string& symbol, const std::vector<std::string>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i) {
		if (vec[i] == symbol) {
			return i;
		}
	}
	return -1;
}

void TPostfix::ToPostfix()
{
	TStack<std::string> st;
	for (const auto& token : lexems_infix) {
		std::string Token = token;
		if (token == "(") {
			st.push(token);
		}
		else if (token == ")") {
			while (!st.empty() && st.top() != "(") {
				postfix += st.top();
				lexems_postfix.push_back(st.top()); // формируем вектор лексем постфиксной формы
				st.pop();
			}
			st.pop(); //убираем (
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "~" || token == "cos") {

			int priority_token = priority[find_pos(token, operations)];


			while (!st.empty()) {
				int pos = find_pos(st.top(), operations);
				int priority_stack;
				if (pos == -1) {
					priority_stack = 0;
				}
				else {
					priority_stack = priority[pos];
				}

				if (priority_stack >= priority_token) {
					postfix += st.top();
					lexems_postfix.push_back(st.top());
					st.pop();
				}
				else {
					break;
				}
			}
			st.push(token);

		}
		else {
			postfix += token;
			lexems_postfix.push_back(token);
		}
	}
	while (!st.empty()) {
		postfix += st.top();
		lexems_postfix.push_back(st.top());
		st.pop();
	}
}

double TPostfix::Calculate(const std::vector<double>& values)
{
	int size = 0; //количество неизвестных переменных в выражении
	for (std::string x : operands) {
		if (x[0] >= '0' && x[0] <= '9') {

		}
		else {
			size += 1;
		}
	}

	if (values.size() != size) {
		throw std::invalid_argument("Error. The size of the passed vector does not match the number of operands (we are talking about non-numeric operands)");
	}

	int j = 0;
	for (size_t i = 0; i < value_operands.size(); ++i) {
		if (value_operands[i] == 0) {
			value_operands[i] = values[j];
			++j;
		}
	}

	TStack<double>st;
	double left_operand, right_operand;
	for (std::string lexem : lexems_postfix) {
		if (lexem == "+" || lexem == "-" || lexem == "*" || lexem == "/") {
			right_operand = st.top();
			st.pop();
			left_operand = st.top();
			st.pop();

			if (lexem == "+") {
				st.push(left_operand + right_operand);
			}
			else if (lexem == "-") {
				st.push(left_operand - right_operand);
			}
			else if (lexem == "*") {
				st.push(left_operand * right_operand);
			}
			else if (lexem == "/") {
				if (right_operand == 0) {
					throw std::invalid_argument("Error. The expression contains a division by zero");
				}
				st.push(left_operand / right_operand);
			}
		}
		else if (lexem == "~" || lexem == "cos") {
			right_operand = st.top();
			st.pop();
			if (lexem == "~") {
				st.push(0 - right_operand);
			}
			else {
				st.push(std::cos(right_operand));
			}
		}
		else {
			int pos = find_pos(lexem, operands);
			st.push(value_operands[pos]);
		}

	}
	return st.top();
}

double TPostfix::Calculate_keyboard_input()
{
	std::vector<std::string>op;
	for (std::string x : operands) {
		if (x[0] >= '0' && x[0] <= '9') {

		}
		else {
			op.push_back(x);
		}
	}

	std::vector<double> val;
	double value = 0;

	for (size_t i = 0; i < op.size(); ) {
		std::cout << "Please enter the value of this variable: " << op[i] << "\n";
		if (!(std::cin >> value)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "Error. Incorrect input. PLease try again\n"; 
			continue; 
		}
		val.push_back(value); 
		++i; 
	}

	return this->Calculate(val);
}
