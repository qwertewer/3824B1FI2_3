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
	TVector(const TVector& v);                // конструктор копирования
	~TVector();
	int GetSize() const { return Size; } // размер вектора
	int GetStartIndex() const { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение
	TVector& operator=(const TVector& v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType& val);   // прибавить скаляр
	TVector  operator-(const ValType& val);   // вычесть скаляр
	TVector  operator*(const ValType& val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector& v);     // сложение
	TVector  operator-(const TVector& v);     // вычитание
	ValType  operator*(const TVector& v);     // скалярное произведение

	// ввод-вывод

	friend std::istream& operator>>(std::istream& in, TVector& v) {

		////////
		if (v.pVector == nullptr) {
			throw std::runtime_error("An error occurred when creating an object");
		}
		////////

		TVector<ValType>back(v);
		try {
			for (size_t i = 0; i < v.GetSize() - v.GetStartIndex(); ++i) {
				if (!(in >> v.pVector[i])) {
					in.clear();
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw std::invalid_argument("Incorrect input");
				}
			}
		}
		catch (...) {
			v = back;
			throw;
		}

		return in;
	};
	friend std::ostream& operator<<(std::ostream& out, const TVector& v) {

		////////
		if (v.pVector == nullptr) {
			throw std::runtime_error("An error occurred when creating an object");
		}
		////////

		ValType zero = {};

		for (size_t i = 0; i < v.StartIndex; ++i) {
			out << zero << " ";
		}

		bool m = true;
		for (size_t i = 0; i < v.Size - v.StartIndex; ++i) {
			if (!m) {
				out << " ";
			}
			out << v.pVector[i];
			m = false;
		}

		return out;
	};
};

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<ValType>>& mt);  // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание

	// ввод / вывод
	friend std::istream& operator>>(std::istream& in, TMatrix& mt) {

		/////
		if (mt.GetSize()== -1) {  //чтобы избежать вызовов конструктора копирования и оператора присваивания
			throw std::runtime_error("An error occurred when creating an object");
		}
		/////

		TMatrix<ValType>mat_copy(mt);

		for (size_t i = 0; i < mt.Size; ++i) {
			try {
				in >> mt[i];
			}
			catch (...) {
				mt = mat_copy;
				throw;
			}

		}

		return in;
	};
	friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) {

		//////
		if (mt.GetSize() == -1) {
			throw std::runtime_error("An error occurred when creating an object");
		}
		//////

		for (size_t i = 0; i < mt.Size; ++i) {
			out << mt.pVector[i] << "\n";
		}
		return out;
	};
}; 

//////////класс TVector

template<class ValType> //конструктор
TVector<ValType>::TVector(int s, int si)
{
	try {
		if (s <= 0 || s > MAX_VECTOR_SIZE) {
			throw std::invalid_argument("Error. Incorrect size");
		}

		if (si < 0 || si >= s) {
			throw std::invalid_argument("Error. Incorrect start_index");
		}

		this->Size = s;
		this->StartIndex = si;
		this->pVector = new ValType[s - si]();
	}
	catch (...) {
		this->Size = -1;
		this->StartIndex = -1;
		this->pVector = nullptr;
		throw;
	}
}

template<class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector& v)
{
	this->Size = v.Size;
	this->StartIndex = v.StartIndex;

	if (v.pVector == nullptr) { //если бросить исключение, то значения не будут переданы текущему объекту
		this->pVector = nullptr;
	}
	else {
		this->pVector = new ValType[v.Size - v.StartIndex];

		for (size_t i = 0; i < v.Size - v.StartIndex; ++i) {
			this->pVector[i] = v.pVector[i];
		}
	}
}

template<class ValType>
TVector<ValType>::~TVector() //деструктор
{
	delete[] pVector;
	this->pVector = nullptr;
}

template<class ValType>
ValType& TVector<ValType>::operator[](int pos)//доступ
{
	//////////
	if (this->pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object"); 
	}
	/////////

	if (pos < this->StartIndex || pos >= this->Size) {
		throw std::out_of_range("Incorrect index");
	}

	return this->pVector[pos - this->StartIndex];
}

template<class ValType>
bool TVector<ValType>::operator==(const TVector& v) const //сравнение
{

	/////////
	if (this->pVector == nullptr || v.pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object (object number 1 or object number 2)");
	}
	////////

	if (this->Size != v.Size) {
		return false;
	}

	int min_start_index = (this->StartIndex <= v.StartIndex ? this->StartIndex : v.StartIndex);
	int max_start_index = (this->StartIndex >= v.StartIndex ? this->StartIndex : v.StartIndex);

	ValType zero = {};

	if (min_start_index == this->StartIndex) {
		for (size_t i = min_start_index; i < max_start_index; ++i) {
			if (this->pVector[i - min_start_index] != zero) {
				return false;
			}
		}
	}
	else {
		for (size_t i = min_start_index; i < max_start_index; ++i) {
			if (v.pVector[i - min_start_index] != zero) {
				return false;
			}
		}
	}

	for (size_t i = max_start_index; i < this->Size; ++i) {
		if (this->pVector[i - this->StartIndex] != v.pVector[i - v.StartIndex]) {
			return false;
		}
	}

	return true;
}

template<class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const //сравнение
{
	return !(*this == v);
}

template<class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) //присваивание
{
	/////////
	if (v.pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object (object number 2)");
	}
	/////////

	if (this == &v) {
		return *this;
	}
	
	TVector<ValType>vec(v);
	std::swap(this->Size, vec.Size);
	std::swap(this->StartIndex, vec.StartIndex);
	std::swap(this->pVector, vec.pVector); 

	return *this;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) //прибавить скаляр
{
	////////
	if (this->pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object");
	}
	////////

	TVector<ValType> tvec(this->Size, this->StartIndex);
	for (size_t i = 0; i < this->Size - this->StartIndex; ++i) {
		tvec.pVector[i] = this->pVector[i] + val;
	}
	return tvec;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) //вычесть скаляр
{
	////////
	if (this->pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object");
	}
	////////

	TVector<ValType> tvec(this->Size, this->StartIndex);
	for (size_t i = 0; i < this->Size - this->StartIndex; ++i) {
		tvec.pVector[i] = this->pVector[i] - val;
	}
	return tvec;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) //умножить на скаляр
{
	////////
	if (this->pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object");
	}
	////////

	TVector<ValType> tvec(this->Size, this->StartIndex);
	for (size_t i = 0; i < this->Size - this->StartIndex; ++i) {
		tvec.pVector[i] = this->pVector[i] * val;
	}
	return tvec;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) //сложение
{
	/////////
	if (this->pVector == nullptr || v.pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object (object number 1 or object number 2)");
	}
	////////

	if (this->Size != v.Size) {
		throw std::runtime_error("The vectors have different sizes");
	}

	int min_start_index = (this->StartIndex <= v.StartIndex ? this->StartIndex : v.StartIndex);

	TVector<ValType> tvec(this->Size, min_start_index);

	if (min_start_index == this->StartIndex) {
		for (size_t i = min_start_index; i < v.StartIndex; ++i) {
			tvec[i] = (*this)[i];
		}
		for (size_t i = v.StartIndex; i < this->Size; ++i) {
			tvec[i] = (*this)[i] + v.pVector[i - v.StartIndex];
		}
	}
	else {
		for (size_t i = min_start_index; i < this->StartIndex; ++i) {
			tvec[i] = v.pVector[i - v.StartIndex];
		}
		for (size_t i = this->StartIndex; i < this->Size; ++i) {
			tvec[i] = (*this)[i] + v.pVector[i - v.StartIndex];
		}
	}

	return tvec;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) //вычитание
{
	/////////
	if (this->pVector == nullptr || v.pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object (object number 1 or object number 2)");
	}
	////////

	if (this->Size != v.Size) {
		throw std::runtime_error("The vectors have different sizes");
	}

	int min_start_index = (this->StartIndex <= v.StartIndex ? this->StartIndex : v.StartIndex);

	TVector<ValType> tvec(this->Size, min_start_index);

	if (min_start_index == this->StartIndex) {
		for (size_t i = min_start_index; i < v.StartIndex; ++i) { //до максимального стартового индекса просто копирую
			tvec[i] = (*this)[i];
		}
		for (size_t i = v.StartIndex; i < this->Size; ++i) { //с наибольшего стартового индекса делаю вычитание
			tvec[i] = (*this)[i] - v.pVector[i - v.StartIndex];
		}
	}
	else {

		for (size_t i = this->StartIndex; i < this->Size; ++i) { //копирую значения от максимального стартового индекса
			tvec[i] = (*this)[i];
		}

		int size = this->Size - min_start_index;
		for (size_t i = 0; i < size; ++i) {  //проходим по всему доступному массиву и делаем вычитание
			tvec.pVector[i] = tvec.pVector[i] - v.pVector[i];
		}
	}

	return tvec;
}

template<class ValType>
ValType TVector<ValType>::operator*(const TVector& v) //скалярное произведение
{
	/////////
	if (this->pVector == nullptr || v.pVector == nullptr) {
		throw std::runtime_error("An error occurred when creating an object (object number 1 or object number 2)");
	}
	////////

	if (this->Size != v.Size) {
		throw std::runtime_error("The vectors have different sizes"); 
	}

	ValType value = {};

	int max_start_index = (this->StartIndex >= v.StartIndex ? this->StartIndex : v.StartIndex);

	for (size_t i = max_start_index; i < this->Size; ++i) {
		value += (*this)[i] * v.pVector[i - v.StartIndex];
	}

	return value;
}

//класс TMatrix
template<class ValType>
TMatrix<ValType>::TMatrix(int s) :TVector<TVector<ValType>>(s, 0) {

	try {
		if (s > MAX_MATRIX_SIZE) {
			throw std::invalid_argument("Invalid matrix size");
		}

		for (size_t i = 0; i < s; ++i) {
			(*this)[i] = TVector<ValType>(s, i); 
		}
	}
	catch (...) {
		throw; //значения по умолчанию устанавливаются в конструкторе класса TVector
	}

}
template<class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) :TVector<TVector<ValType>>(mt) {}// копирование  

template<class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) {// преобразование типа 

	try {
		///////
		if (mt.GetSize() == -1) {
			throw std::runtime_error("An error occurred when creating an object (object number 2)");
		}
		///////

		TVector<TVector<ValType>>& non_const_mt = const_cast<TVector<TVector<ValType>>&>(mt);

		if (mt.GetSize() > MAX_MATRIX_SIZE) {
			throw std::invalid_argument("Invalid matrix size");
		}

		if (mt.GetStartIndex() != 0) {
			throw std::invalid_argument("Error. The starting index of the vector of vectors should be 0");
		}

		for (int i = 0; i < mt.GetSize(); ++i) {
			if (non_const_mt[i].GetStartIndex() != i) { 
				throw std::runtime_error("Matching of the starting indexes");
			}
		}

		TVector<TVector<ValType>>::operator=(mt);
	}
	catch (...) {
		this->Size = -1;
		this->StartIndex = -1;
		this->pVector = nullptr; 
		throw;
	}

}
template<class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt); 
}

template<class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const //сравнение
{
	return TVector<TVector<ValType>>::operator!=(mt);
}

template<class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt)//присваивание
{
	TVector<TVector<ValType>>::operator=(mt);

	return *this;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt)//сложение
{
	///////
	if (this->pVector == nullptr || mt.GetSize() == -1) { //исключение выбрасывается в операторе базового класса, но если один объект создан корректно, то выйдет сообщение о разных размерах 
		throw std::runtime_error("An error occurred when creating an object (object number 1 or object number 2)");
	}
	///////

	if (this->Size != mt.Size) {
		throw std::runtime_error("Different sizes of matrices");
	}

	return TVector<TVector<ValType>>::operator+(mt);
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt)//вычитание
{
	///////
	if (this->pVector == nullptr || mt.GetSize() == -1) {
		throw std::runtime_error("An error occurred when creating an object (object number 1 or object number 2)");
	}
	///////

	if (this->Size != mt.Size) {
		throw std::runtime_error("Different sizes of matrices");
	}

	return TVector<TVector<ValType>>::operator-(mt);
}

