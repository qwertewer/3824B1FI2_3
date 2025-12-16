#include <../../../../../include/Lab1/tbitfield.h>
#include <../../../../../include/Lab1/tset.h>

#include <string>

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {} //Список инициализации. Не проверяем mp, так как проверка есть в конструкторе TBitField.

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {} //Список инициализации. BitField(s.BitField) - применяем конструктор копирования TBitField.

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {} //Список инициализации. BitField(bf) - применяем конструктор копирования TBitField.

TSet::operator TBitField() //TSet преобразовать в TBitField.
{
	return BitField;
}

int TSet::GetMaxPower(void) const //Максимальная мощность множества (мощность универса).
{
	return MaxPower;
}

void TSet::InsElem(const int Elem) //Включить элемент в множество.
{
	BitField.SetBit(Elem); //Не проверяем Elem на допустимость, так как проверка есть в SetBit(). (MaxPower = BitField.BitLen).
}

void TSet::DelElem(const int Elem) //Удалить элемент из множества.
{
	BitField.ClrBit(Elem); //Не проверяем Elem на допустимость, так как проверка есть в ClrBit(). (MaxPower = BitField.BitLen).
}

int TSet::IsMember(const int Elem) const //Проверить наличие элемента в множестве.
{
	return (BitField.GetBit(Elem)) ? 1 : 0; //Тернарный оператор. Не проверяем Elem на допустимость, так как проверка есть в GetBit(). (MaxPower = BitField.BitLen). Есть элемент в множестве => 1. Нет элемента в множестве => 0.
}

int TSet::operator== (const TSet& s) const //Cравнение множеств.
{
	return (BitField == s.BitField) ? 1 : 0; //Тернарный оператор. Сравниваем битовые поля (характеристические векторы) множеств (Здесь применится перегруженный оператор == для битовых полей, где (MaxPower != s.MaxPower) уже учитывается, так как MaxPower = BitLen, s.MaxPower = s.BitLen). Равны => 1. Не равны => 0.
}

int TSet::operator!= (const TSet& s) const //Сравнение множеств.
{
	return (*this == s) ? 0 : 1; //Тернарный оператор. Сравниваем множества: (*this == s) - применится перегруженный оператор == для множеств, где уже учитывается (MaxPower != s.MaxPower). Равны => 0. Не равны => 1.
}

TSet& TSet::operator=(const TSet& s) //Присваивание множества другому множеству.
{
	MaxPower = s.MaxPower;
	BitField = s.BitField; //Перегруженный оператор = для битовых полей.

	return *this; //Возвращаем ссылку на объект.
}

TSet TSet::operator+ (const int Elem) //Объединение множества с элементом. Элемент должен быть из того же универса, что и элементы множества.
{
	TSet res(*this); //Создаём копию исходного множества (конструктор копирования). Это итоговое множество.
	res.InsElem(Elem); //Проверка на совпадение универсов здесь также есть (в InsElem()). Если элемент уже был в множестве - тоже учитывается.
	return res;
}

TSet TSet::operator- (const int Elem) //Разность множества с элементом. Элемент должен быть из того же универса, что и элементы множества.
{
	TSet res(*this); //Создаём копию исходного множества (конструктор копирования). Это итоговое множество.
	res.DelElem(Elem); //Проверка на совпадение универсов здесь также есть (в DelElem()). Если элемента не было в множестве - тоже учитывается.
	return res;
}

TSet TSet::operator+ (const TSet& s) //Объединение множеств.
{
	if (MaxPower != s.MaxPower) //Операция объединения множеств не определена для множеств разных универсов.
	{
		throw std::invalid_argument("The universes of the sets do not coincide");
	}
	TSet res(MaxPower); //Создаём итоговое множество. Результат объединения множеств.
	res.BitField = BitField | s.BitField; //Используем перегруженный оператор побитового ИЛИ для битовых полей.
	res.DelElem(0); //Не затрагиваем нулевой элемент множества.
	return res;
}

TSet TSet::operator* (const TSet& s) //Пересечение множеств.
{
	if (MaxPower != s.MaxPower) //Операция пересечения множеств не определена для множеств разных универсов.
	{
		throw std::invalid_argument("The universes of the sets do not coincide");
	}
	TSet res(MaxPower); //Создаём итоговое множество. Результат пересечения множеств.
	res.BitField = BitField & s.BitField; //Используем перегруженный оператор побитового И для битовых полей.
	res.DelElem(0); //Не затрагиваем нулевой элемент множества.
	return res;
}

TSet TSet::operator~ (void) //Дополнение множеств.
{
	TSet res(MaxPower); //Создаём итоговое множество. Результат дополнения множества.
	res.BitField = ~(BitField); //Используем перегруженный оператор побитового НЕ для битовых полей.
	res.DelElem(0); //Не затрагиваем нулевой элемент множества.
	return res;
}

std::istream& operator>>(std::istream& istr, TSet& bf) //Формат ввода:{ * * * * * * * }, где * - любой допустимый индекс элемента множества. {} => пустое множество.
{
	for (int i = 0; i < bf.MaxPower; ++i) //Опустошаем множество для записи нового.
	{
		bf.DelElem(i);
	}

	std::string str; //Создаём буфер для ввода из консоли (строку).
	std::getline(istr, str); //Ввод из консоли.
	int str_len = str.length(), str_ind = -1; 
	std::string str_elem; //Буфер для отдельных индексов элементов множества.

	if (str.empty() || str.front() != '{' || str.back() != '}') //{ - должна быть первым введённым символом. } - должна быть последним введённым символом. Буфер не доолжен быть пустым.
	{
		throw std::invalid_argument("Incorrect input");
	}
	
	for (int i = 1; i < str_len-1; ++i) //Проходим все символы буфера, кроме первого и последнего.
	{
		switch (str[i])
		{
			case '{':
				throw std::invalid_argument("The opening curly brace should be the only one"); //Проверка на то, что { встречается ещё раз. Например { 1 { 2 }. 
			case ' ':
				break;
			case '0':  case '1': case '2':  case '3': case '4':  case '5': case '6':  case '7': case '8':  case '9':
				str_elem.push_back(str[i]); //push_back() - добавляет символ в конец буфера.
				for (i = i + 1; str[i] != ' ' && str[i] != '}'; ++i) //Смотрим следующие символы до пробела (или до }), чтобы составить индекс.
				{
					if (!(str[i] >= 48 && str[i] <= 57)) //Проверяем последующие символа на цифры.
					{
						throw std::invalid_argument("It is not a number that has been sent for input");
					}
					str_elem.push_back(str[i]);
				}
				str_ind = std::stoi(str_elem); //Получаем индекс элемента множества.
				bf.InsElem(str_ind); //Записываем индекс элемента в множество.
				str_elem.clear(); //Очищаем буфер для индексов элементов множества.
				if (str[i] == '}')
				{
					i = i - 1;
				}
				break;
			case '}':
				throw std::invalid_argument("The closing curly brace should be the only one"); //Проверка на то, что } встречается ещё раз. Например { 1 } 2 }.
			default:
				throw std::invalid_argument("Invalid character passed"); //Передали некорректный символ.
		}
	}
	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& bf)
{
	ostr << "{";
	int extra = 0; //Дополнительная переменная для красивого вывода.
	for (int i = 0; i < bf.MaxPower; ++i)
	{
		if (bf.BitField.GetBit(i))
		{
			if (extra == 0) //Вывод пробела после первой {.
			{
				ostr << " ";
				extra = 1;
			}
			ostr << i << " ";
		}
	}
	ostr << "}";
	return ostr;
}