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
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
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

  friend std::istream& operator>>(std::istream& in, TVector& v) {
	  if (v.GetSize() == 0) {
		  throw out_of_range("Vector have size of null.");
	  }
	  else {
		  for (size_t i = v.GetStartIndex(); i < v.GetSize(); i++) {
			  in >> v[i];
		  }
	  }
	  return in;
  };
  friend std::ostream& operator<<(std::ostream& out, const TVector& v) {
	  if (v.Size > 0) {
		  for (size_t i = 0; i < v.Size; i++) {
			  if (i < v.StartIndex) {
				  out << ValType() << " ";
			  }
			  else {
				  out << v.pVector[i] << " ";
			  }
		  }
		  out << endl;
	  }
	  else {
		  out << "null" << endl;
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
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType>> &mt);  // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend std::istream& operator>>(std::istream& in, TMatrix& mt) {
	  for (size_t i = 0; i < mt.GetSize(); i++) {
		  for (size_t j = mt[i].GetStartIndex(); j < mt[i].GetSize(); j++) {
			  in >> mt[i][j];
		  }
	  }
	  return in;
  };
  friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) {
	  for (size_t i = 0; i < mt.Size; i++) {
		  out << mt.pVector[i];
	  }
	  return out;
  };
};