
#include "../../../include/Lab1/tset.h"
#include <stdexcept>

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {
    if (mp < 0) throw std::invalid_argument("Negative MaxPower");
}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
    return BitField;
}

int TSet::GetMaxPower(void) const {
    return MaxPower;
}

void TSet::InsElem(int Elem) {
    BitField.SetBit(Elem);
}

void TSet::DelElem(int Elem) {
    BitField.ClrBit(Elem);
}

int TSet::IsMember(int Elem) const {
    return BitField.GetBit(Elem);
}

int TSet::operator==(const TSet& s) const {
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const {
    return BitField != s.BitField;
}

TSet& TSet::operator=(const TSet& s) {
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

TSet TSet::operator+(int Elem) {
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(int Elem) {
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator+(const TSet& s) {
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument("Sets must have the same MaxPower for union");
    return TSet(BitField | s.BitField);
}

TSet TSet::operator*(const TSet& s) {
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument("Sets must have the same MaxPower for intersection");
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~() {
    return TSet(~BitField);
}

std::istream& operator>>(std::istream& istr, TSet& bf) {
    return istr >> bf.BitField;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
    return ostr << bf.BitField;
}