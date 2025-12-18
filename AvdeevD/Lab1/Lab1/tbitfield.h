// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#pragma once

#include <iostream>

using namespace std;
typedef unsigned int TELEM;

class TBitField
{
private:
  int  BitLen; // длина битового поля - макс. к-во битов
  TELEM *pMem; // память для представления битового поля
  int  MemLen; // к-во эл-тов Мем для представления бит.поля

  // методы реализации
  int   GetMemIndex(const int n) const; // индекс в pМем для бита n       (#О2)
  TELEM GetMemMask (const int n) const; // битовая маска для бита n       (#О3)
public:
  TBitField(int len);                //                                   (#О1)
  TBitField(const TBitField &bf);    //                                   (#П1)
  ~TBitField();                      //                                    (#С)

  // доступ к битам
  int GetLength(void) const;      // получить длину (к-во битов)           (#О)
  void SetBit(const int n);       // установить бит                       (#О4)
  void ClrBit(const int n);       // очистить бит                         (#П2)
  int  GetBit(const int n) const; // получить значение бита               (#Л1)

  // битовые операции
  int operator==(const TBitField &bf) const; // сравнение                 (#О5)
  int operator!=(const TBitField &bf) const; // сравнение
  TBitField& operator=(const TBitField &bf); // присваивание              (#П3)
  TBitField  operator|(const TBitField &bf); // операция "или"            (#О6)
  TBitField  operator&(const TBitField &bf); // операция "и"              (#Л2)
  TBitField  operator~(void);                // отрицание                  (#С)

  friend std::istream& operator>>(std::istream& istr, TBitField& bf)
  {
	  if (bf.BitLen == 0) {
		  throw invalid_argument("Field size is zero.");
	  }
	  for (size_t i = 0; i < bf.MemLen; i++) {
		  bf.pMem[i] &= 0;
	  }
	  string field;
	  istr >> field;
	  if (field.size() != bf.MemLen) {
		  throw length_error("Size of bit field is different.");
	  }
	  for (int i = 0; i < bf.BitLen; i++)
	  {
		  if (field[bf.BitLen - 1 - i] - '0' == 1) {
			  bf.SetBit(i);
		  }  
		  else if (field[bf.BitLen - 1 - i] - '0' != 0)
		  {
			  throw std::invalid_argument("Bitfield contains only 0 and 1's.");
		  }
	  }
	  return istr;
  };        //      (#О7)
  friend std::ostream& operator<<(std::ostream& ostr, const TBitField& bf)
  {
	  if (bf.BitLen == 0) {
		  ostr << "null";
		  return ostr;
	  }
	  for (size_t i = 0; i < bf.MemLen; i++) {
		  ostr << bf.GetBit(i);
	  }
	  return ostr;
  }; //      (#П4)
};

int TBitField::GetMemIndex(const int n) const {
	if (n < 0 || n + 1 > BitLen) {
		throw out_of_range("Out of range.");
	}
	return n / (sizeof(TELEM) * 8);
};
TELEM TBitField::GetMemMask(const int n) const
{
	if (n + 1 > BitLen) {
		throw out_of_range("Out of range.");
	}
	if (n < 0) {
		throw invalid_argument("Index is negative.");
	}
	return 1 << (n % (sizeof(TELEM) * 8));
};
TBitField::TBitField(int len) {
	if (len < 0) {
		throw invalid_argument("Must be >= 0");
	}
	BitLen = len;
	MemLen = (BitLen + (sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8));
	if (len > 0) {
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
	else {
		pMem = nullptr;
	}
};
TBitField::TBitField(const TBitField& bf) {
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	if (BitLen > 0) {
		pMem = new TELEM[MemLen];
		for (int i = 0; i < BitLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	else {
		pMem = nullptr;
	}
};
TBitField::~TBitField() {
	delete[] pMem;
};
int TBitField::GetLength(void) const { return BitLen; };
void TBitField::SetBit(const int n)
{
	if (pMem == nullptr) {
		throw invalid_argument("Bit field size is 0.");
	}
	if (n < 0 || n >= BitLen) {
		throw out_of_range("Out of range");
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
};       // установить бит                       (#О4)
void TBitField::ClrBit(const int n)
{
	if (pMem == nullptr) {
		throw invalid_argument("Bit field size is 0.");
	}
	if (n < 0 || n >= BitLen) {
		throw out_of_range("Out of range");
	}
	pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
};       // очистить бит                         (#П2)
int  TBitField::GetBit(const int n) const
{
	if (pMem == nullptr) {
		throw invalid_argument("Bit field size is 0.");
	}
	if (n < 0 || n >= BitLen) {
		throw out_of_range("Out of range");
	}
	if (pMem[GetMemIndex(n)] & GetMemMask(n)) {
		return 1;
	}
	else {
		return 0;
	}
}; // получить значение бита               (#Л1)

// битовые операции
int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen != bf.BitLen) {
		return 0;
	}
	if (pMem == nullptr && bf.pMem == nullptr) {
		return 1;
	}
	for (size_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}; // сравнение                 (#О5)
int TBitField::operator!=(const TBitField& bf) const
{
	if (BitLen != bf.BitLen) {
		return 1;
	}
	if (pMem == nullptr && bf.pMem == nullptr) {
		return 0;
	}
	for (size_t i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 1;
		}
	}
	return 0;
}; // сравнение
TBitField& TBitField::operator=(const TBitField& bf)
{
	if (*this == bf) {
		return *this;
	}
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (BitLen != 0) {
		pMem = new TELEM[MemLen];
		for (size_t i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	else {
		pMem = nullptr;
	}
	return *this;
}; // присваивание              (#П3)
TBitField  TBitField::operator|(const TBitField& bf)
{
	TBitField Or(0);
	if (BitLen > bf.BitLen) {
		Or = TBitField(*this);
	}
	else {
		Or = TBitField(bf);
	}
	if (pMem == nullptr) {
		return bf;
	}
	if (bf.pMem == nullptr) {
		return *this;
	}
	int MinLen;
	if (MemLen > bf.MemLen) {
		MinLen = bf.MemLen;
	}
	else {
		MinLen = MemLen;
	}
	for (size_t i = 0; i < MinLen; i++) {
		Or.pMem[i] = (pMem[i] | bf.pMem[i]);
	}
	return Or;
}; // операция "или"            (#О6)
TBitField  TBitField::operator&(const TBitField& bf)
{
	TBitField And(0);
	if (BitLen > bf.BitLen) {
		And = TBitField(BitLen);
	}
	else {
		And = TBitField(bf.BitLen);
	}
	if (pMem == nullptr) {
		return bf;
	}
	if (bf.pMem == nullptr) {
		return *this;
	}
	int MinLen;
	if (MemLen > bf.MemLen) {
		MinLen = bf.MemLen;
	}
	else {
		MinLen = MemLen;
	}
	for (size_t i = 0; i < MinLen; i++) {
		And.pMem[i] = (pMem[i] & bf.pMem[i]);
	}
	return And;
}; // операция "и"              (#Л2)
TBitField TBitField::operator~(void)
{
	if (pMem == nullptr) {
		throw runtime_error("Size is 0. Unable to invert.");
	}
	TBitField Inv(*this);
	for (size_t i = 0; i < MemLen; i++) {
		Inv.pMem[i] = ~pMem[i];
	}
	int bitsInLastElement = BitLen % (sizeof(TELEM) * 8);
	if (bitsInLastElement != 0) {
		TELEM mask = (1 << bitsInLastElement) - 1;
		Inv.pMem[MemLen - 1] &= mask;
	}
	return Inv;
};

// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2
