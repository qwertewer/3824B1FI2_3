#include "tset.h" 
#include "tbitfield.h"
#include <string> //для метода getline();
#include <sstream>

//конструктор
TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {
	if (mp < 0) {
		throw std::invalid_argument("Error! The length is less than zero");
	}
}


//конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}


//конструктор преобразования типа 
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}


//конструктор преобразования типа к битовому полю
TSet::operator TBitField()
{
	return this->BitField;
}


//доступ к битам

int TSet::GetMaxPower(void) const
{
	return this->MaxPower;
}

void TSet::InsElem(const int Elem) //Elem - индекс элемента в унивёрсе U={u0,u1,u2....}
{
	if (MaxPower == 0) {
		throw std::runtime_error("The power of the set is 0");
	}

	if (Elem >= 0 && Elem < this->MaxPower) {
		BitField.SetBit(Elem);
	}
	else {
		throw std::out_of_range("Elem < 0 or elem >= power of set");
	}
}

void TSet::DelElem(const int Elem)
{
	if (MaxPower == 0) {
		throw std::runtime_error("The power of the set is 0");
	}

	if (Elem >= 0 && Elem < this->MaxPower) {
		BitField.ClrBit(Elem);
	}
	else {
		throw std::out_of_range("Elem < 0 or elem >= power of set");
	}
}
int TSet::IsMember(const int Elem) const
{
	if (MaxPower == 0) {
		throw std::runtime_error("The power of the set is 0");
	}

	if (Elem >= 0 && Elem < this->MaxPower) {
		return BitField.GetBit(Elem);
	}
	else {
		throw std::out_of_range("Elem < 0 or elem >= power of set");
	}
}

//теоретико множественные операции
int TSet::operator==(const TSet& s) const
{
	return ((this->MaxPower == s.MaxPower) && (this->BitField == s.BitField));
}

int TSet::operator!=(const TSet& s) const
{
	return !((this->MaxPower == s.MaxPower) && (this->BitField == s.BitField));
}

TSet& TSet::operator=(const TSet& s)
{
	if (this == &s) return *this;

	this->MaxPower = s.MaxPower;

	this->BitField = s.BitField;

	return *this;
}

TSet TSet::operator+(const int Elem)
{
	if (MaxPower == 0) {
		throw std::runtime_error("The maximum power of the set is 0. There are no elements that can be added");
	}

	if (Elem < 0 || Elem >= MaxPower) {
		throw std::out_of_range("Elem < 0 or elem >= power of set");
	}

	TSet new_set(*this);

	new_set.InsElem(Elem);
	return new_set;
}

TSet TSet::operator-(const int Elem)
{
	if (MaxPower == 0) {
		throw std::runtime_error("The maximum power of the set is 0. There are no elements that can be added");
	}

	if (Elem < 0 || Elem >= MaxPower) {
		throw std::out_of_range("Elem < 0 or elem >= power of set");
	}

	TSet new_set(*this);

	new_set.DelElem(Elem);
	return new_set;
}

TSet TSet::operator+(const TSet& s)
{
	if (&this->BitField == &s.BitField) {
		return *this;
	}

	if (this->MaxPower != s.MaxPower) {
		throw std::runtime_error("The maximum powers do not match");
	}

	TSet new_set(this->MaxPower);
	new_set.BitField = this->BitField | s.BitField;
	return new_set;
}

TSet TSet::operator*(const TSet& s)
{
	if (&this->BitField == &s.BitField) {
		return *this;
	}

	if (this->MaxPower != s.MaxPower) {
		throw std::runtime_error("The maximum powers do not match");
	}

	TSet new_set(this->MaxPower);
	new_set.BitField = this->BitField & s.BitField;
	return new_set;
}



TSet TSet::operator~(void)
{
	TSet new_set = *this;
	new_set.BitField = ~(new_set.BitField);
	return new_set;
}


//ввод, вывод
std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
	if (bf.GetMaxPower() == 0) {
		throw std::runtime_error("The maximum power of the set is 0. There are no elements that can be added");
	}

	ostr << bf.BitField << ": ";
	bool m = true;
	ostr << "{";
	for (size_t i = 0; i < bf.GetMaxPower(); ++i) {
		if (bf.IsMember(i)) {
			if (!m) {
				ostr << ",";
			}
			ostr << i;
			m = false;
		}
	}
	ostr << "}";
	return ostr;
}

std::istream& operator>>(std::istream& istr, TSet& bf) {

	if (bf.MaxPower == 0) {
		throw std::runtime_error("The maximum power of the set is 0. There are no elements that can be added");
	}

	std::string str;
	std::getline(istr, str); //считали из istr в str

	std::stringstream ss(str);  //поместили str в stringstream
	std::string elem_string;
	while (std::getline(ss, elem_string, ',')) { //проходим по ss до ',', записываем результат в elem_string

		int len = elem_string.size();
		if (len != 0) {
			for (char c : elem_string) {
				if (c < '0' || c > '9') {
					throw std::invalid_argument("Incorrect index. Incorrect symbol");
				}
			}

			if (len > 1 && elem_string[0] == '0') {
				throw std::invalid_argument("Incorrect index");
			}

			int elem = std::stoi(elem_string); //преобразовали строку в целое число

			if (elem < 0 || elem >= bf.MaxPower) {
				throw std::out_of_range("Incorrect index. The boundaries of the universal set");
			}

			bf.InsElem(elem);
		}
		else {
			throw std::runtime_error("Error. Empty values between commas are not allowed");
		}
	}

	return istr;
}