#include "../../../include/Lab1/tset.h"
#include <exception>
#include <string>
#include <cmath>

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {};
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {};
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {};
TSet::operator TBitField() {
	return BitField;
}

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

int TSet::operator== (const TSet& s) const {
	if (MaxPower != s.MaxPower) {
		return 0;
	}
	return BitField == s.BitField;
}
int TSet::operator!= (const TSet& s) const {
	return !(*this == s);
}
TSet& TSet::operator=(const TSet& s) {
	if (this == &s) {
		return *this;
	}
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}
TSet TSet::operator+ (const int Elem) {
	TSet add(*this);
	add.InsElem(Elem);
	return add;
}

TSet TSet::operator- (const int Elem) {
	TSet sub(*this);
	sub.DelElem(Elem);
	return sub;
}

TSet TSet::operator+ (const TSet& s) {
	if (MaxPower != s.MaxPower) {
		throw std::invalid_argument("The sets have different universes");
	}
	return TSet(BitField | s.BitField);
}
TSet TSet::operator* (const TSet& s) { 
	if (MaxPower != s.MaxPower) {
		throw std::invalid_argument("The sets have different universes");
	}
	return TSet(BitField & s.BitField);
}
TSet TSet::operator~ (void) {
	return TSet(~BitField);
}

std::istream& operator>>(std::istream& istr, TSet& bf) {
	bf.BitField = TBitField(bf.BitField.GetLength());
	std::string res;
	std::getline(istr, res);
	std::string num = "";
	TELEM tnum = 0;
	for (int i = 0; i < res.length(); ++i) {
		if (res[i] != ' ' && i != res.length() - 1) {
			num += res[i];
		}
		else {
			if (i == res.length() - 1 && res[i] != ' ') {
				num += res[i];
			}
			size_t len = num.length();
			for (int j = len - 1; j >= 0; --j) {
				tnum += (num[j] - '0') * pow(10, len - 1 - j);
			}
			if (num != "") {
				bf.InsElem(tnum);
			}
			tnum = 0;
			num = "";
		}
	}
	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
	ostr << "{ ";
	bool flag = 0; // флаг наличия в потоке вывода хотя бы одного элемента
	for (int i = 0; i < bf.MaxPower; ++i) {
		if (bf.IsMember(i)) {
			if (i != 0 && flag) {
				ostr << ", ";
			}
			ostr << i;
			if (!flag) {
				flag = true;
			}
		}
	}
	ostr << " }";
	return ostr;
}
