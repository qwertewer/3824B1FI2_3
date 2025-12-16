#include "tset.h"       
#include "tbitField.h"  
using namespace std;
#include <string>
TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}//Можем не проверять mp, поскольку подобная проверка есть в TBitField

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
	return BitField;
}

//Исключения следующих функций уже прописаны в соответствующих функциях TBitField
int TSet::GetMaxPower(void) const {
	return MaxPower;
}
void TSet::InsElem(const int Elem) {
	BitField.SetBit(Elem);
}
void TSet::DelElem(const int Elem) {
	BitField.ClrBit(Elem);
}
int TSet::IsMember(const int Elem) const {
	return BitField.GetBit(Elem);
}
//Операторы
int TSet::operator== (const TSet& s) const {
	return BitField == s.BitField;
}
int TSet::operator!= (const TSet& s) const {
	return (BitField == s.BitField) ? 0 : 1;
}
TSet& TSet::operator=(const TSet& s) {
	if (this != &s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}
TSet TSet::operator+ (const int Elem) {
	TSet result(*this);
	result.InsElem(Elem);
	return result;
}
TSet TSet::operator- (const int Elem) {
	TSet result(*this);
	result.DelElem(Elem);
	return result;
}
TSet TSet::operator+ (const TSet& s) {
	if (MaxPower != s.MaxPower) {//Не можем объединить элементы из разных универсов
		throw invalid_argument("Sets must be of the same power");
	}
	TSet result(MaxPower);
	result.BitField = BitField | s.BitField;
	return result;
}
TSet TSet::operator* (const TSet& s) {
	if (MaxPower != s.MaxPower) {//Не можем пересечь элементы из разных универсов
		throw invalid_argument("Sets must be of the same power");
	}
	TSet result(MaxPower);
	result.BitField = BitField & s.BitField;
	return result;
}
TSet TSet::operator~ (void) {//Дополнение к множеству
	TSet result(MaxPower);
	result.BitField = ~BitField;
	return result;
}

//Операторы ввода и вывода, вводим так же как битовую строку
istream& operator>>(istream& istr, TSet& s) {
	istr >> s.BitField;
	return istr;
}
ostream& operator<<(ostream& ostr, const TSet& s) {
	ostr << s.BitField;
	return ostr;
}