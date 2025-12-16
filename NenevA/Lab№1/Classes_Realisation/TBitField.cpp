#include "tbitField.h"
#include <algorithm>
#include <exception>
#include <cstring>
using namespace std;
TBitField::TBitField(int len) {
	if (len <= 0) {
		throw invalid_argument("Length must be positive");
	}
	BitLen = len;
	MemLen = (BitLen + 31) / 32;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) {
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() {
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const {
	if (n >= BitLen) {
		throw out_of_range("The bit number must be within the bit field");
	}
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const {
	if (n >= BitLen) {
		throw out_of_range("The bit number must be within the bit field");
	}
	return 1 << (n % (sizeof(TELEM) * 8));
}

int TBitField::GetLength(void) const {
	return BitLen;
}

void TBitField::SetBit(const int n) {
	if (n < 0 || n >= BitLen) {
		throw out_of_range("Bit index out of range");
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
	if (n < 0 || n >= BitLen) {
		throw out_of_range("Bit index out of range");
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {
	if (n < 0 || n >= BitLen) {
		throw out_of_range("Bit index out of range");
	}
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const {
	if (BitLen != bf.BitLen) {
		return 0;
	}
	for (int i = 0; i < MemLen; ++i) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const {
	if (*this == bf) {
		return 0;
	}
	else {
		return 1;
	}
}

TBitField& TBitField::operator=(const TBitField& bf) {
	if (this != &bf) {
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

TBitField TBitField::operator|(const TBitField& other){
	size_t maxLen = std::max(BitLen, other.BitLen);
	TBitField result(maxLen);
	for (size_t i = 0; i < maxLen; ++i)	{
		int bit1 = (i < BitLen) ? GetBit(i) : 0;
		int bit2 = (i < other.BitLen) ? other.GetBit(i) : 0;
		if (bit1 || bit2) {
			result.SetBit(i);
		}
		else {
			result.ClrBit(i);
		}
	}
	return result;
}

TBitField TBitField::operator&(const TBitField& other){
	size_t maxLen = std::max(BitLen, other.BitLen);
	TBitField result(maxLen);
	for (size_t i = 0; i < maxLen; ++i){
		int bit1 = (i < BitLen) ? GetBit(i) : 0;
		int bit2 = (i < other.BitLen) ? other.GetBit(i) : 0;
		if (bit1 && bit2) {
			result.SetBit(i);
		}
		else {
			result.ClrBit(i);
		}
	}
	return result;
}

TBitField TBitField::operator~(void) {
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; ++i) {
		result.pMem[i] = ~pMem[i];
	}
	// Очищает лишние биты
	int lastBitIndex = BitLen % 32;
	if (lastBitIndex != 0) {
		result.pMem[MemLen - 1] &= (1 << lastBitIndex) - 1;
	}
	return result;
}

std::istream& operator>>(std::istream& is, TBitField& bf){
	std::string str;

	is >> str;
	if (str.length() != bf.BitLen) {
		throw invalid_argument("Input string length does not match BitField length");
	}
	for (size_t i = 0; i < bf.BitLen; ++i){
		if (str[bf.BitLen - i - 1] == '1'){
			bf.SetBit(i);
		}
		else if (str[bf.BitLen - i - 1] == '0'){
			bf.ClrBit(i);
		}
		else{
			throw invalid_argument("Input string must contain only '0' or '1'");
		}
	}
	return is;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) {
	for (int i = bf.BitLen - 1; i >= 0; --i) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}