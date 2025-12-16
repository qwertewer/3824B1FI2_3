#include "../../../include/Lab1/tbitfield.h"
#include <stdexcept>

static int BitsPerElem = sizeof(TELEM) * 8;

int TBitField::GetMemIndex(int n) const {
    return n / BitsPerElem;
}

TELEM TBitField::GetMemMask(int n) const {
    return TELEM(1) << (n % BitsPerElem);
}

TBitField::TBitField(int len) {
    if (len < 0) throw std::invalid_argument("incorrect length");
    BitLen = len;
    MemLen = (len + BitsPerElem - 1) / BitsPerElem; //округление вверх
    pMem = new TELEM[MemLen]();
    for (int i = 0; i < MemLen; ++i)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    std::copy(bf.pMem, bf.pMem + MemLen, pMem);
}

TBitField::~TBitField() {
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetLength(void) const {
    return BitLen;
}

void TBitField::SetBit(const int n) {
    if (n < 0 || n >= BitLen) throw std::out_of_range("SetBit");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
    if (n < 0 || n >= BitLen) throw std::out_of_range("ClrBit");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}
int  TBitField::GetBit(const int n) const {
    if (n < 0 || n >= BitLen) throw std::out_of_range("GetBit");
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}
int TBitField::operator==(const TBitField& bf) const {
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; ++i)
        if (pMem[i] != bf.pMem[i]) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const {
    if (BitLen != bf.BitLen) return 1;
    for (int i = 0; i < MemLen; ++i)
        if (pMem[i] != bf.pMem[i]) return 1;
    return 0;
}

TBitField& TBitField::operator=(const TBitField& bf) {
    if (this == &bf) return *this;
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    std::copy(bf.pMem, bf.pMem + MemLen, pMem);
    return *this;
}

TBitField  TBitField::operator|(const TBitField& bf) {
    int maxLen = std::max(BitLen, bf.BitLen);
    TBitField result(maxLen);
    for (int i = 0; i < result.MemLen; ++i) {
        TELEM lValue;
        if (i < MemLen) {
            lValue = pMem[i];
        }
        else {
            lValue = 0;         // вышел за границу берём 0
        }

        TELEM rValue;
        if (i < bf.MemLen) {
            rValue = bf.pMem[i];
        }
        else {
            rValue = 0;
        }

        result.pMem[i] = lValue | rValue;
    }
    return result;
}

TBitField  TBitField::operator&(const TBitField& bf) {
    int maxLen = std::max(BitLen, bf.BitLen);
    TBitField result(maxLen);
    for (int i = 0; i < result.MemLen; ++i) {
        TELEM lValue;
        if (i < MemLen) {
            lValue = pMem[i];
        }
        else {
            lValue = 0;
        }

        TELEM rValue;
        if (i < bf.MemLen) {
            rValue = bf.pMem[i];
        }
        else {
            rValue = 0;
        }

        result.pMem[i] = lValue & rValue;
    }
    return result;
}

TBitField TBitField::operator~() {
    TBitField result(*this);
    for (int i = 0; i < MemLen; ++i)
        result.pMem[i] = ~result.pMem[i];

    int extra = MemLen * BitsPerElem - BitLen; // в последнем элементе BitLen % BitsPerElem
    if (extra) {                               // может оказаться < BitsPerElem, в конце образовываются лишние единицы
        TELEM mask = (~TELEM(0)) >> extra;
        result.pMem[MemLen - 1] &= mask;
    }
    return result;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {
    std::string s;
    istr >> s;
    for (int i = 0; i < bf.BitLen && i < int(s.size()); ++i)
        if (s[i] == '1') bf.SetBit(i);
        else bf.ClrBit(i);
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
    for (int i = 0; i < bf.BitLen; ++i)
        if (bf.GetBit(i)) {
            ostr << '1';
        }
        else {
            ostr << '0';
        }
    return ostr;
}