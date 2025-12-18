// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#pragma once

#include "tbitfield.h"

class TSet
{
private:
    int MaxPower;       // максимальная мощность множества
    TBitField BitField; // битовое поле для хранения характеристического вектора
public:
    TSet(int mp);
    TSet(const TSet& s);       // конструктор копирования
    TSet(const TBitField& bf); // конструктор преобразования типа
    operator TBitField();      // преобразование типа к битовому полю
    // доступ к битам
    int GetMaxPower(void) const;     // максимальная мощность множества
    void InsElem(const int Elem);       // включить элемент в множество
    void DelElem(const int Elem);       // удалить элемент из множества
    int IsMember(const int Elem) const; // проверить наличие элемента в множестве
    // теоретико-множественные операции
    int operator== (const TSet& s) const; // сравнение
    int operator!= (const TSet& s) const; // сравнение
    TSet& operator=(const TSet& s);  // присваивание
    TSet operator+ (const int Elem); // объединение с элементом
    // элемент должен быть из того же универса
    TSet operator- (const int Elem); // разность с элементом
    // элемент должен быть из того же универса
    TSet operator+ (const TSet& s);  // объединение
    TSet operator* (const TSet& s);  // пересечение
    TSet operator~ (void);           // дополнение

    friend std::istream& operator>>(std::istream& istr, TSet& s)
    {
        int size = s.GetMaxPower();
        for (int i = 0; i < size; i++)
        {
            int elem;
            istr >> elem;
            if (elem >= 0 && elem < size)
                s.InsElem(elem);
        }
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TSet& s)
    {
        ostr << "{ ";
        bool first = true;
        for (int i = 0; i < s.GetMaxPower(); i++)
        {
            if (s.IsMember(i))
            {
                if (!first)
                    ostr << ", ";
                ostr << i;
                first = false;
            }
        }
        ostr << " }";
        return ostr;
    }
};

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {};
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {};
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {};
TSet::operator TBitField() {
    return BitField;
}
int TSet::GetMaxPower() const {
    return MaxPower;
}
void TSet::InsElem(const int Elem) {
    if (MaxPower == 0) {
        throw std::out_of_range("Power is 0.");
    }
    BitField.SetBit(Elem);
}
void TSet::DelElem(const int Elem) {
    if (MaxPower == 0) {
        throw std::out_of_range("Power is 0.");
    }
    BitField.ClrBit(Elem);
}
int TSet::IsMember(const int Elem) const {
    if (MaxPower == 0) {
        throw std::out_of_range("Power is 0.");
    }
    return BitField.GetBit(Elem);
}
int TSet::operator==(const TSet& s) const {
    if (s.MaxPower != MaxPower) {
        return 0;
    }
    return s.BitField == BitField;
}
int TSet::operator!=(const TSet& s) const {
    if (s.MaxPower != MaxPower) {
        return 1;
    }
    return s.BitField != BitField;
}
TSet& TSet::operator=(const TSet& s) {
    if (&s == this) {
        return *this;
    }
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}
TSet TSet::operator+(const int Elem) {
    if (MaxPower == 0) {
        throw std::out_of_range("Power is 0.");
    }
    TSet newset(*this);
    newset.InsElem(Elem);
    return newset;
}
TSet TSet::operator-(const int Elem) {
    if (MaxPower == 0) {
        throw std::out_of_range("Power is 0.");
    }
    TSet newset(*this);
    newset.DelElem(Elem);
    return newset;
}
TSet TSet::operator+(const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Different universes.");
    }
    TSet newset(BitField | s.BitField);
    return newset;
}
TSet TSet::operator*(const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Different universes.");
    }
    TSet newset(BitField & s.BitField);
    return newset;
}
TSet TSet::operator~() {
    TSet newset(*this);
    newset.BitField = ~(BitField);
    return newset;
}
 