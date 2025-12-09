#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <string> //Работа по строками.

template <class T>
class TStack
{
	std::vector<T> mem; //Память для стека. 
public:
	TStack(); //Конструктор.
	~TStack(); //Деструктор.
	bool isEmpty() const; //Проверить на пустоту стека.
	size_t size() const; //Размер стека - число элементов в нём на данный момент;
	void push(const T& val); //Положить элемент в стека.
	void pop(); //Удалить "верхний" элемент из стека.
	T top() const; //Вернуть "верхний" элемент стека.
};


class Postfix
{
	std::string infix; //Хранит инфиксную форму.
	std::string postfix; //Хранит постфиксную форму.

	std::vector<std::string> lexems_infix; //Хранит последовательность всех лексем, которые были в инфиксной форме.
	std::vector<std::string> lexems_postfix; //Хранит последовательность всех лексем, которые были в постфиксной форме.

	std::vector<std::string> operands; //Хранит имена всех переменных.
	std::vector<double> values; //Хранит значения всех переменных.

	std::vector<std::string> name_op_priority; //Имя операции.
	std::vector<int> op_priority; //Приоритет операции.

	void Parse(); //Разбор инфиксной формы на лексемы.
	void ToPostfix(); //Преобразование в постфиксную форму.
public:
	Postfix(std::string infx); //Конструктор.
	~Postfix(); //Дестурктор.

	std::string GetInfix() const; //Получить инфиксную форму.
	std::string GetPostfix() const; //Получить постфиксную форму.

	std::vector<std::string> GetOperands() const; //Возвращает список, набор переменных.

	double Calculate(const std::vector<double> values); //Вычисляет выражение по постфиксной форме.

	double Calculate(); //Вычисляет выражение по постфиксной форме. Ввод опернадов (переменных) с консоли.
};

//Реализация класса TStack:

template <class T>
TStack<T>::TStack() {} //Конструктор.

template <class T>
TStack<T>::~TStack() {} //Деструктор.

template <class T>
bool TStack<T>::isEmpty() const //Проверить на пустоту стека.
{
	return mem.empty(); //Проверяет, пуст ли вектор (стек). true - если пуст; false - иначе.
}

template <class T>
size_t TStack<T>::size() const
{
	return mem.size(); //Возвращает количество элементов в векторе (в стеке).
}

template <class T>
void TStack<T>::push(const T& val)
{
	mem.push_back(val); //Добавляет элемент в конец вектора (на вершину стека).
}

template <class T>
void TStack<T>::pop()
{
	if (isEmpty())
	{
		throw std::out_of_range("Stack is empty"); //Исключение.
	}
	mem.pop_back(); //Удаляет элемент в конце вектора (с вершины стека).
}

template <class T>
T TStack<T>::top() const
{
	if (isEmpty())
	{
		throw std::out_of_range("Stack is empty"); //Исключение.
	}
	return mem.back(); //Возвращает ссылку на последний элемент вектора (на элемент на вершине стека).
}

//Реализация класса Postfix:

void Postfix::Parse() //Разбор инфиксной формы на лексемы.
{
	size_t size_infx = infix.size(); //Размер инфиксной формы.
	std::string buffer; //Буфер для конкретной лексемы.
	std::string prev = ""; //Предыдущая лексема.
	size_t num_brackets = 0; //Указывает на правильность количества скобок '(' и ')' в инфиксной форме. Если попалась '(', то num_brackets++, если ')' - num_brackets--. Если к концу парсинга num_brackets == 0, то инфиксная форма верна.

	for (size_t i = 0; i < size_infx; )
	{
		char c = infix[i]; //Текущий символ.

		if (c == ' ') //Пропуск пробела.
		{
			i++;
			continue;
		}

		if (c >= '0' && c <= '9') //Поиск вещественного числа.
		{
			buffer.clear(); //Очищаем буфер.
			int points = 0; //Количество точек, которые идут после найденной цифры/числа.

			if (prev == "exp" || prev == ")" || ((prev[0] >= 'a' && prev[0] <= 'z') || (prev[0] >= 'A' && prev[0] <= 'Z')))
			{
				throw std::invalid_argument("Incorrect infix form: incorrect number input, symbol number - " + std::to_string(i + 1)); //Некорректные случаи: exp8 , exp 8 , )9 , a7 .
			}

			while ((i < size_infx) && ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')) //Если после числа идёт ещё число или точка, то парсим их.
			{
				if (infix[i] == '.')
				{
					points++;
					if (points > 1)
					{
						throw std::invalid_argument("Incorrect infix form: invalid number, symbol number - " + std::to_string(i + 1)); //В числе не может быть две и более точек. Пример некорректного случая: 5.2.3
					}
				}

				buffer.push_back(infix[i]);
				i++;
			}

			lexems_infix.push_back(buffer); //Добавляем лексему - число.
			prev = buffer; //Сохраняем лексему.
			continue;
		}

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) //Поиск буквы или функции exp.
		{
			buffer.clear(); //Очищаем буфер.

			if (prev == "exp" || prev == ")" || (prev[0] >= '0' && prev[0] <= '9'))
			{
				throw std::invalid_argument("Incorrect infix form: incorrect input of the operand (or the exp() function), symbol number - " + std::to_string(i + 1)); //Некорректные случаи: expa , exp a , )a , 4.3a .
			}

			if (i != 0)
			{
				if (infix[i - 1] == ' ' && ((prev[0] >= 'a' && prev[0] <= 'z') || (prev[0] >= 'A' && prev[0] <= 'Z')))
				{
					throw std::invalid_argument("Incorrect infix form: a gap was found between the operands, symbol number - " + std::to_string(i + 1)); //Некорректный случай: a exp(), a b. То есть пробел между операндами. Считаем ошибкой.
				}
			}

			while ((i < size_infx) && ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))) //Ищем многобуквенные переменные или функции. Кроме exp.
			{
				buffer.push_back(infix[i]);
				i++;

				if (buffer == "exp") //Поиск exp.
				{
					lexems_infix.push_back(buffer); //Добавляем лексему - функцию exp.
					prev = buffer; //Сохраняем лексему.

					break;
				}
			}

			if (buffer == "exp")
			{
				continue;
			}

			lexems_infix.push_back(buffer); //Добавляем лексему - переменную или многобуквенную переменную.
			prev = buffer; //Сохраняем лексему.

			size_t size_operands = operands.size(); //Количество операндов.
			bool replay_op = false;
			for (size_t j = 0; j < size_operands; ++j)
			{
				if (operands[j] == buffer) //Проверяем, есть ли данный операнд buffer в списке операндов.
				{
					replay_op = true;
					break;
				}
			}
			if (!replay_op)
			{
				operands.push_back(buffer); //Если данного операнда buffer нет в списке операндов, то добавляем его в список.
			}

			continue;
		}

		if (c == '(') //Поиск открывающей скобки.
		{
			buffer.clear(); //Очищаем буфер.
			buffer.push_back(c);

			if (!lexems_infix.empty() && ((prev[0] >= '0' && prev[0] <= '9') || (((prev[0] >= 'a' && prev[0] <= 'z') || (prev[0] >= 'A' && prev[0] <= 'Z')) && prev != "exp" && prev != "~") || prev == ")")) //Если предыдущая лексема: не операция (число или операнд), кроме унарного минуса и exp, или закрывающая скобка, то ошибка.
			{
				throw std::invalid_argument("Incorrect infix form: incorrect entry of the opening bracket, symbol number - " + std::to_string(i + 1)); //Не может быть, например: (a+b)a( , (a+b)7( , (a*b)(
			}

			lexems_infix.push_back(buffer); //Добавляем лексему - открывающая скобка.
			prev = buffer;

			num_brackets++;

			i++;
			continue;
		}

		if (c == ')') //Поиск закрывающей скобки.
		{
			buffer.clear(); //Очищаем буфер.
			buffer.push_back(c);

			if (lexems_infix.empty() || prev == "(" || prev == "+" || prev == "-" || prev == "*" || prev == "/" || prev == "~" || prev == "exp") //1)Некорректный случай: () . 2)Некорректные случаи: (a+) , (a-) , (a*) , (a/) , (a+exp)
			{
				throw std::invalid_argument("Incorrect infix form: incorrect entry of the closing bracket, symbol number - " + std::to_string(i + 1));
			}

			lexems_infix.push_back(buffer); //Добавляем лексему - закрывающая скобка.
			prev = buffer;

			num_brackets--;
			if (num_brackets < 0)
			{
				throw std::invalid_argument("Incorrect infix form: incorrect number of opening and closing brackets"); //Некорректный случай: (a+b)+9)
			}

			i++;
			continue;
		}

		if (c == '+' || c == '-' || c == '*' || c == '/') //Поиск операций (+, -, *, /).
		{
			buffer.clear(); //Очищаем буфер.
			buffer.push_back(c);

			if (lexems_infix.empty() || prev == "+" || prev == "-" || prev == "*" || prev == "/" || prev == "exp" || prev == "(" || prev == "~") //Некорретные случаи: ++ , -+ , *+ , /+ , exp+ , (+ , ~+ .
			{
				if (!lexems_infix.empty() && c == '-')
				{
					if (lexems_infix.back() == "(")
					{
						lexems_infix.push_back("~"); //~ - обозначение унарного минуса. Добавляем лексему - унарный минус.
						prev = "~";

						i++;
						continue;
					}
					else
					{
						throw std::invalid_argument("Incorrect infix form: incorrect unary minus sign input, symbol number - " + std::to_string(i + 1));
					}
				}
				else if (lexems_infix.empty() && c == '-')
				{
					lexems_infix.push_back("~"); //~ - обозначение унарного минуса. Добавляем лексему - унарный минус.
					prev = "~";

					i++;
					continue;
				}
				else
				{
					throw std::invalid_argument("Incorrect infix form: incorrect operation input, symbol number - " + std::to_string(i + 1));
				}
			}
	
			lexems_infix.push_back(buffer); //Добавляем лексему - операция.
			prev = buffer;

			i++;
			continue;
		}

		throw std::invalid_argument("Incorrect infix form: unknown symbol detected, symbol number - " + std::to_string(i + 1)); //В инфиксной форме присутствует недопустимый (неизвестный) символ. Код дойдёт до этой строки, если предыдущие условия не выполнятся.
	}

	if (num_brackets != 0 || prev == "exp" || prev == "+" || prev == "-" || prev == "*" || prev == "/" || prev == "(")
	{
		throw std::invalid_argument("Incorrect infix form: the infix form cannot end with exp, +, -, *, /, (; symbol number - " + std::to_string(size_infx) + ". Or: incorrect number of opening and closing brackets"); //Не допускается разного количества '(' и ')' в инфиксной форме. Также не допускается, чтобы операция была последней лексемой в инфиксной форме.
	}
}

void Postfix::ToPostfix() //Преобразование в постфиксную форму.
{
	Parse();

	TStack<std::string> stack_data; //Стек для перобразования в постфиксную форму.
	std::string stack_elem = "", lexem_i = ""; //Элемент стека; i-ая лексема.
	size_t size_of_lexems = lexems_infix.size(); //Количество лексем.
	size_t size_of_operands = operands.size(); //Количество операндов.

	for (size_t i = 0; i < size_of_lexems; )
	{
		lexem_i = lexems_infix[i]; //Берём i-ую лексему.

		bool operand_seek = false; //Константа для отлова операндов.
		for (size_t j = 0; j < size_of_operands && !operand_seek; ++j) //Поиск операндов.
		{
			if (lexem_i == operands[j])
			{
				postfix += lexem_i; //Если лексема - операнд, то помещаем её в постфиксную форму.
				lexems_postfix.push_back(lexem_i); //Добавляем лексему в последовательность лексем для постфиксной формы.
				operand_seek = true;
			}
		}
		if (operand_seek) //Если нашли операнд, то переходим к другой лексеме.
		{
			i++;
			continue;
		}

		if (lexem_i[0] >= '0' && lexem_i[0] <= '9') //Если лексема - число, то помещаем её в постфиксную форму.
		{
			postfix += lexem_i;
			lexems_postfix.push_back(lexem_i); //Добавляем лексему в последовательность лексем для постфиксной формы.

			i++;
			continue;
		}

		if (lexem_i == "(") //Если лексема - открывающая скобка, то помещаем её в стек.
		{
			stack_data.push(lexem_i);

			i++;
			continue;
		}

		if (lexem_i == ")") //Если лексема - закрывающая скобка.
		{
			stack_elem = stack_data.top(); //Берём верхний элемент стека.
			stack_data.pop(); //Удаляем верхний элемент стека.

			while (stack_elem != "(") //Пока верхний элемент стека - не открывающая скобка, помещаем его в постфиксную форму. Как только stack_elem == "(", то цикл заканчивается, а открывающая скобка из стека ужеудалена.
			{
				postfix += stack_elem;
				lexems_postfix.push_back(stack_elem); //Добавляем элемент стека в последовательность лексем для постфиксной формы.

				stack_elem = stack_data.top(); //Берём верхний элемент стека.
				stack_data.pop(); //Удаляем верхний элемент стека.
			}

			i++;
			continue;
		}

		if (lexem_i == "+" || lexem_i == "-" || lexem_i == "*" || lexem_i == "/" || lexem_i == "exp" || lexem_i == "~") //Если лексема - операция.
		{
			size_t size_op_priority = name_op_priority.size(); //Количество операций.
			size_t j = 0; //Индекс i-ой лексемы - индекс операции.
			for ( ; j < size_op_priority; ++j) //Поиск индекса j.
			{
				if (lexem_i == name_op_priority[j])
				{
					break;
				}
			}
			while (!stack_data.isEmpty())
			{
				stack_elem = stack_data.top(); //Берём верхний элемент стека.

				size_t k = 0; //Индекс верхнего элемента стека - индекс операции.
				for (; k < size_op_priority && stack_elem != "("; ++k) //Поиск индекса k.
				{
					if (stack_elem == name_op_priority[k])
					{
						break; //Выходим из цикла for.
					}
				}

				if (op_priority[j] <= op_priority[k] && stack_elem != "(") //Если приоритет нашей лексемы-операции меньше или равен приоритета операции на вершине стека (при условии, что на вершине стека не открывающая скобка) 
				{
					stack_data.pop(); //Удаляем верхний элемент стека.
					postfix += stack_elem; //Помещаем элемент вершины стека в постфиксную форму.
					lexems_postfix.push_back(stack_elem); //Добавляем элемент стека в последовательность лексем для постфиксной формы.
				}
				else //Иначе.
				{
					break; //Выходим из цикла while.
				}
			}
			stack_data.push(lexem_i); //Помещаем лексему - операцию в стек.

			i++;
			continue;
		}
	}
	while (!stack_data.isEmpty()) //После исчерпания лексем, все элементы из стека переносим в постфиксную форму.
	{
		stack_elem = stack_data.top(); //Берём верхний элемент стека.
		postfix += stack_elem; //Помещаем элемент вершины стека в постфиксную форму.
		lexems_postfix.push_back(stack_elem); //Добавляем элемент стека в последовательность лексем для постфиксной формы.
		stack_data.pop(); //Удаляем верхний элемент стека.
	}
}

Postfix::Postfix(std::string infx): infix(infx), postfix("") //Конструктор. (Приоритеты по возрастанию).
{
	name_op_priority = {"+", "-", "*", "/", "~", "exp"}; //~ - унарный минус.
	op_priority = { 1, 1, 2, 2, 3, 4 };

	ToPostfix(); //Переводим в постфиксную форму.
}

Postfix::~Postfix() {} //Дестурктор.

std::string Postfix::GetInfix() const //Получить инфиксную форму.
{
	return infix;
}

std::string Postfix::GetPostfix() const //Получить постфиксную форму.
{
	return postfix;
}

std::vector<std::string> Postfix::GetOperands() const //Возвращает список, набор переменных.
{
	std::vector<std::string> vector_op;

	size_t size_vec_op = operands.size();
	for (size_t i = 0; i < size_vec_op; ++i)
	{
		vector_op.push_back(operands[i]);
	}

	return vector_op;
}

double Postfix::Calculate(const std::vector<double> values_) //Вычисляет выражение по постфиксной форме.
{
	size_t size_val = values_.size(); //Размер полученного вектора значений переменных (операндов).
	if (size_val == operands.size()) //Проверка совпадения размеров (количества значений операндов и количества операндов).
	{
		for (size_t i = 0; i < size_val; ++i)
		{
			values.push_back(values_[i]); //Запоминаем полученные значения переменных (операндов).
		}
	}
	else
	{
		throw std::invalid_argument("Incorrect size of the vector of variable values (operands). Mismatch between the number of operand values and the number of operands"); //Если размеры отличаются.
	}

	TStack<double> stack_data; //Стек для вычисления выражения по постфискной форме.
	double leftOperand = 0.0, rightOperand = 0.0;
	std::string lexem_i = ""; //i-ая лексема.
	size_t size_of_lexems = lexems_postfix.size(); //Количество лексем.
	size_t size_of_operands = operands.size(); //Количество операндов.

	for (size_t i = 0; i < size_of_lexems; )
	{
		lexem_i = lexems_postfix[i]; //Берём i-ую лексему.

		bool operand_seek = false; //Константа для отлова операндов.
		for (size_t j = 0; j < size_of_operands && !operand_seek; ++j) //Поиск операндов.
		{
			if (lexem_i == operands[j])
			{
				stack_data.push(values[j]); //Если лексема - операнд, то помещаем её значение в стек.
				operand_seek = true;
			}
		}
		if (operand_seek) //Если нашли операнд, то переходим к другой лексеме.
		{
			i++;
			continue;
		}

		if (lexem_i[0] >= '0' && lexem_i[0] <= '9') //Если лексема - число, то помещаем её в стек.
		{
			stack_data.push(std::stod(lexem_i)); //Преобразуем лексему в число (std::stod(lexem_i) - вернёт double) и помещаем в стек.

			i++;
			continue;
		}

		if (lexem_i == "+" || lexem_i == "-" || lexem_i == "*" || lexem_i == "/") //Если лексема - бинарная операция.
		{
			rightOperand = stack_data.top(); //Извлекаем верхний элемент из стека, который является правым операндом.
			stack_data.pop(); //Удаляем правый операнд из стека.
			leftOperand = stack_data.top(); // Извлекаем следующий элемент из стека, который является левым операндом.
			stack_data.pop(); //Удаляем левый операнд из стека.

			if (lexem_i == "+")
			{
				stack_data.push(leftOperand + rightOperand);
			}
			else if (lexem_i == "-")
			{
				stack_data.push(leftOperand - rightOperand);
			}
			else if (lexem_i == "*")
			{
				stack_data.push(leftOperand * rightOperand);
			}
			else
			{
				stack_data.push(leftOperand / rightOperand);
			}

			i++;
			continue;
		}

		if (lexem_i == "exp" || lexem_i == "~") //Если лексема - унарная операция.
		{
			rightOperand = stack_data.top(); //Извлекаем верхний элемент из стека - операнд.
			stack_data.pop(); //Удаляем операнд из стека.

			if (lexem_i == "exp")
			{
				stack_data.push(std::exp(rightOperand));
			}
			else
			{
				stack_data.push(-rightOperand);
			}

			i++;
			continue;
		}
	}

	return stack_data.top(); //После исчерпания лексем из постфиксной формы на вершине стека остался результат вычисления выражения.
}

double Postfix::Calculate() //Вычисляет выражение по постфиксной форме. Ввод опернадов (переменных) с консоли.
{
	double val_i = 0.0; //Значение i-го операнда.
	size_t size_of_operands = operands.size(); //Количество операндов.

	for (size_t i = 0; i < size_of_operands; ) //Вводим значения операндов.
	{
		std::cout << "Enter value of " << operands[i] << ": ";
		std::cin >> val_i;
		if (std::cin.fail()) //fail() - функция потока ввода, которая проверяет, завершилась ли последняя операция ввода неудачей. Возвращает true, если произошла ошибка ввода, и false, если операция прошла успешно.
		{
			std::cin.clear(); //Сбрасываем поток ввода до исходного состояния.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Пропускаем плохой ввод. Параметры: количество отбрасываемых символов - std::numeric_limits<std::streamsize>::max(); символ-признак, после которого отбрасывание прекращается - '\n'.
			std::cout << "Invalid input!\n";
			continue;
		}
		values.push_back(val_i);
		i++;
	}

	return Calculate(values);
}