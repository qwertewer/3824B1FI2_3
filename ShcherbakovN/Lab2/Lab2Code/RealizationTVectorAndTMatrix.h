#pragma once

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
  ValType* pVector;
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize() const { return Size; }             // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод

  //Формат ввода: elem1_elem2_elem3_... где _ - некоторое число разделителей.
  friend std::istream& operator>>(std::istream& in, TVector& v) //Ввод вектора.
  {
	  for (int i = 0; i < v.Size; ++i) //Очищаем вектор от прошлых значений элементов.
	  {
		  v.pVector[i] = 0;
	  }

	  for (int i = 0; i < v.Size; ++i) //Считываем элементы из потока.
	  {
		  in >> v.pVector[i]; //Считывает элементы до разделителя(пробела). Записывает элементы в вектор.
		  if (in.fail()) //fail() - функция потока ввода, которая проверяет, завершилась ли последняя операция ввода неудачей. Возвращает true, если произошла ошибка ввода, и false, если операция прошла успешно.
		  {
			  in.clear(); //Сбрасываем поток ввода до исходнного состояния.
			  throw std::runtime_error("Uncorrected input");
		  }
	  }

	  return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const TVector& v) //Вывод вектора.
  {
	  for (int i = 0; i < v.StartIndex; ++i) //Выводим элементы, по индексу меньшие, чем v.StartIndex. То есть - несуществующие элементы.
	  {
		  out << "0 ";
	  }

	  for (int j = 0; j < v.Size; ++j) //Выводим элементы вектора v, начиная со v.StartIndex.
	  {
		  out << v.pVector[j] << " ";
	  }

	  out << '\n';

	  return out;
  }
};

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType>> &mt);  // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод

  //Формат ввода: elem1_elem2_elem3_... где _ - некоторое число разделителей.
  friend std::istream& operator>>(std::istream& in, TMatrix& mt) //Ввод матрицы.
  {
	  for (int i = 0; i < mt.Size; ++i) //Очищаем матрицу от прошлых значений элементов.
	  {
		  mt.pVector[i] = mt.pVector[i] * 0; //Умножаем строки (вектора) матрицы на 0 (скаляр), чтобы обнулить. (Перегруженный оператор умножения вектора на скаляр, перегруженный оператор присваивания вектора).
	  }

	  for (int i = 0; i < mt.Size; ++i)
	  {
		  in >> mt.pVector[i]; //Применяем перегруженный ввод вектора, чтобы ввести всю матрицу (все проверки учтены в перегрузке ввода вектора).
	  }

	  return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) //Вывод матрицы.
  {
	  for (int i = 0; i < mt.Size; ++i)
	  {
		  out << mt.pVector[i]; //Применяем перегруженный оператор вывода вектора, чтобы вывести всю матрицу.
	  }

	  return out;
  }
};

//Реализация TVector:

template <class ValType>
TVector<ValType>::TVector(int s, int si) //Конструктор по умолчанию/Конструктор с параметрами для вектора.
{
	if (s <= 0 || s > MAX_VECTOR_SIZE || si < 0 || si >= MAX_VECTOR_SIZE) //При выходе за предела допустимых значений - значения по умолчанию.
	{
		pVector = new ValType[10](); //Память для вектора по умолчанию. Может бросить исключение. Скобки () инициализируют все элементы нулями (для чисел) или вызывают конструктор по умолчанию для объектов сложных типов (Было рассказано на лекции).
		Size = 10; //Размер вектора по умолчанию.
		StartIndex = 0; //Индекс первого элемента вектора по умолчанию.
	}
	else
	{
		pVector = new ValType[s](); //Память для вектора. Может бросить исключение. Скобки () инициализируют все элементы нулями (для чисел) или вызывают конструктор по умолчанию для объектов сложных типов (Было рассказано на лекции).
		Size = s; //Размер вектора.
		StartIndex = si; //Индекс первого элемента вектора.
	}
}


template <class ValType>
TVector<ValType>::TVector(const TVector& v) //Конструктор копирования для вектора.
{
	pVector = new ValType[v.Size]; //Память для вектора. Может бросить исключение.
	Size = v.Size; //Копируем размер вектора.
	StartIndex = v.StartIndex; //Копируем индекс первого элемента вектора.

	for (int i = 0; i < v.Size; ++i)
	{
		pVector[i] = v.pVector[i];//Копируем каждый элемент вектора v в новый вектор.
	}
}


template <class ValType>
TVector<ValType>::~TVector() //Деструктор.
{
	delete[] pVector; 
	pVector = nullptr;
}


template <class ValType>
ValType& TVector<ValType>::operator[](int pos) //Доступ к элементам вектора.
{
	if (pos < StartIndex || pos >(Size + StartIndex) - 1) //Проверяем корректность индекса pos. Пример: TVector v(5,3), тогда доступные индексы: 3, 4, 5, 6, 7. Причём память pVector хранится по индексам от 0 до 4.
	{
		throw std::out_of_range("Unavailable index for accessing elements"); //Бросаем исключение.
	}
	return pVector[pos - StartIndex];
}


template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const //Сравнение векторов.
{
	if (Size != v.Size || StartIndex != v.StartIndex) //Проверяем совпадение размеров вектора и индексов первых элементов векторов.
	{
		return false;
	}

	for (int i = 0; i < Size; ++i) //Проверяем элементы двух векторов на неравенство. 
	{
		if (pVector[i] != v.pVector[i])
		{
			return false;
		}
	}

	return true;
}


template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const //Сравнение векторов.
{
	return !((*this) == v); //Применяем перегруженный оператор сравнения (==) для векторов, но инвертируем результат (!).
}


template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) //Присваивание вектора.
{
	if (this != &v) //Если вектора равны, то возвращаем текущий вектор (Самоприсваивание). Если вектора не равны, то выполняем copy-and-swap. (Сравнение по адресам в памяти: this == &v).
	{
		TVector<ValType> v_temp(v); //Вызываем конструктор копирования класса TVector для создания копии вектора v.

		std::swap(Size, v_temp.Size); //Меняем поле Size местами с полем v_temp.Size.
		std::swap(StartIndex, v_temp.StartIndex); //Меняем поле StartIndex местами с полем v_temp.StartIndex.
		std::swap(pVector, v_temp.pVector); //Меняем местами указатели.
	}

	return *this; //Возвращаем ссылку на объект.
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) //Прибавление скаляра к вектору.
{
	TVector<ValType> VecRes(*this); //Создаём копию текущего вектора (Констурктор копирования).

	for (int i = 0; i < Size; ++i) 
	{
		VecRes.pVector[i] += val; //Прибавляем скаляр к каждому элементу вектора.
	}

	return VecRes;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) //Вычитание скаляра из вектора.
{
	TVector<ValType> VecRes(*this); //Создаём копию текущего вектора (Констурктор копирования).

	for (int i = 0; i < Size; ++i)
	{
		VecRes.pVector[i] -= val; //Вычитаем скаляр из каждого элемента вектора.
	}

	return VecRes;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) //Умножение вектора на скаляр.
{
	TVector<ValType> VecRes(*this); //Создаём копию текущего вектора (Констурктор копирования).

	for (int i = 0; i < Size; ++i)
	{
		VecRes.pVector[i] *= val; //Умножаем каждый элемент вектора на скаляр.
	}

	return VecRes;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) //Сложение векторов.
{
	if (Size != v.Size || StartIndex != v.StartIndex) //Проверяем совпадение размеров вектора и индексов первых элементов векторов.
	{
		throw std::invalid_argument("The sizes and/or indexes of the first elements are different"); //Бросаем исключение.
	}

	TVector<ValType> VecRes(Size, StartIndex); //Создаём новый вектор, результат сложения двух векторов.

	for (int i = 0; i < Size; ++i)
	{
		VecRes.pVector[i] = pVector[i] + v.pVector[i]; //Скалдываем элементы двух векторов.
	}

	return VecRes;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) //Вычитание векторов.
{
	if (Size != v.Size || StartIndex != v.StartIndex) //Проверяем совпадение размеров вектора и индексов первых элементов векторов.
	{
		throw std::invalid_argument("The sizes and/or indexes of the first elements are different"); //Бросаем исключение.
	}

	TVector<ValType> VecRes(Size, StartIndex); //Создаём новый вектор, результат вычитания двух векторов.

	for (int i = 0; i < Size; ++i)
	{
		VecRes.pVector[i] = pVector[i] - v.pVector[i]; //Вычитаем элементы двух векторов.
	}

	return VecRes;
}


template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) //Скалярное произведение векторов.
{
	if (Size != v.Size || StartIndex != v.StartIndex) //Проверяем совпадение размеров вектора и индексов первых элементов векторов.
	{
		throw std::invalid_argument("The sizes and/or indexes of the first elements are different"); //Бросаем исключение.
	}

	ValType Res = 0; //Создаём переменную - результат скалярного произведения векторов. Инициализируем нулём (для сложных типов вызовется конструктор по умолчанию).

	for (int i = 0; i < Size; ++i) //Применяем формулу скалярного произведения векторов.
	{
		Res += pVector[i] * v.pVector[i]; 
	}

	return Res;
}

//Реализация TMatrix:

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>( (s <= 0 || s > MAX_MATRIX_SIZE) ? 10 : s, 0) //TVector<TVector<ValType>>((s <= 0 || s > MAX_MATRIX_SIZE) ? 10 : s, 0) - создаём вектор размера s (выполняется конструктор вектора по умолчанию), состоящий из векторов TVector<ValType>, ПРИ УСЛОВИИ, что s не выходит за пределы допустимых значений. Если s выходит за пределы допустимых значений, то s = 10 и TVector<TVector<ValType>>(10, 0).
{
	if (s <= 0 || s > MAX_MATRIX_SIZE) //Размер матрицы по усполчанию при выходе за пределы допустимых значений.
	{
		s = 10;
	}

	for (int i = 0; i < s; ++i)
	{
		this->pVector[i] = TVector<ValType>(s - i, i); //Создаём векторы внутри вектора TVector<TVector<ValType>>(s) того же размера s, но с разными индексами стартового элемента, по логике верхнетреугольной матрицы.
	}
}


//Констурктор копирования.
template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt): TVector<TVector<ValType>>(mt.Size, 0) //TVector<TVector<ValType>>(mt.Size, 0) - копируем размер матрицы (выполняется конструктор вектора с параметрами);
{
	for (int i = 0; i < mt.Size; ++i)
	{
		this->pVector[i] = mt.pVector[i]; //Копируем строки (вектора) матрицы mt в новую матрицу.
	}
}


//Конструктор преобразование типа. Используем GetSize() и GetStartIndex(), так как у нас нет прямого досутпа к полям TVector.
template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt): TVector<TVector<ValType>>(mt.GetSize(), 0) //Копируем размер вектора векторов (выполняется конструктор вектора с параметрами).
{
	TVector<TVector<ValType>> mt_temp(mt); //Создаём временный не константный объект класса TVector. Вызываем конструктор копирования векторов класса TVector.

	int mtSize = mt_temp.GetSize(); //Сохраняем размер вектора mt.

	if (mt_temp.GetStartIndex() != 0)
	{
		throw std::invalid_argument("The index of the first element of the vector of vectors must be zero"); //Бросаем исключение.
	}

	for (int i = 0; i < mtSize; ++i)
	{
		if (mt_temp[i].GetSize() != mtSize - i || mt_temp[i].GetStartIndex() != i) //Проверяем вектор векторов mt на то, что он в виде верхнетреугольной матрицы (То есть (i=0..Size) i-ый вектор имеет Size - i размер и i-ый стартовый индекс).
		{
			throw std::invalid_argument("The vector of vectors should be in the form of an upper triangular matrix"); //Бросаем исключение.
		}
	}

	for (int i = 0; i < mtSize; ++i)
	{
		this->pVector[i] = mt_temp[i]; //Копируем вектора у вектора mt в новую матрицу.
	}
}


template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const //Сравнение матриц
{
	return TVector<TVector<ValType>>::operator==(mt); //Вызываем перегруженный оператор сравнения == вектора с вектором класса TVector, так как матрица представляет собой вектор векторов, то есть к ней применимы операции векторов.
}


template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const //Сравнение матриц.
{
	return TVector<TVector<ValType>>::operator!=(mt); //Вызываем перегруженный оператор сравнения != вектора с вектором класса TVector, так как матрица представляет собой вектор векторов, то есть к ней применимы операции векторов.
}


template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator= (const TMatrix& mt) //Присваивание матрицы.
{
	if (this != &mt) //Если матрицы равны, то возвращаем текущую матрицу (Самоприсваивание). Если матрицы не равны, то выполняем copy-and-swap. (Сравнение по адресам в памяти: this == &mt).
	{
		TMatrix<ValType> mt_temp(mt); //Вызываем конструктор копирования класса TMatrix для создания копии матрицы mt.

		std::swap(Size, mt_temp.Size); //Меняем поле Size местами с полем mt_temp.Size.
		std::swap(StartIndex, mt_temp.StartIndex); //Меняем поле StartIndex местами с полем mt_temp.StartIndex.
		std::swap(pVector, mt_temp.pVector); //Меняем местами указатели.
	}

	return *this; //Возвращаем ссылку на объект.
}


template <class ValType>
TMatrix<ValType>  TMatrix<ValType>::operator+ (const TMatrix& mt) //Сложение матриц.
{
	return TVector<TVector<ValType>>::operator+(mt); //Вызываем перегруженный оператор сложения + векторов класса TVector, так как матрица представляет собой вектор векторов, то есть к ней применимы операции векторов.
}


template <class ValType>
TMatrix<ValType>  TMatrix<ValType>::operator- (const TMatrix& mt) //Вычитание матриц.
{
	return TVector<TVector<ValType>>::operator-(mt); //Вызываем перегруженный оператор вычитания - векторов класса TVector, так как матрица представляет собой вектор векторов, то есть к ней применимы операции векторов.
}