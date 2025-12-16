#include "../../../include/Lab1/tbitfield.h"
#include <string>
#include <exception>
#include <cmath>

int TBitField::GetMemIndex(const int n) const {
	if (n + 1 > BitLen) {
		throw std::out_of_range("out of range");
	}
	else if (n < 0) {
		throw std::invalid_argument("index must be positive");
	}
	return MemLen - n / (sizeof(TELEM) * 8) - 1; // вычисление и возврат индекса
}

TELEM TBitField::GetMemMask(const int n) const {
	if (n + 1 > BitLen) {
		throw std::out_of_range("out of range");
	}
	else if (n < 0) {
		throw std::invalid_argument("index must be positive");
	}
	int bit_index = n % (sizeof(TELEM) * 8); // Позиция искомого бита в pMem[pMem_index]
	TELEM mask = 1 << bit_index;
	return mask;
}

TBitField::TBitField(int len) {
	if (len <= 0) {
		throw std::invalid_argument("Size must be >= 0");
	}
	BitLen = len;
	MemLen = (BitLen + (sizeof(TELEM) * 8) - 1) / (sizeof(TELEM) * 8); //MemLen с округлением вверх
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) {
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() {
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetLength() const {
	return BitLen;
}

void TBitField::SetBit(const int n) {
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] |= mask;
}

void TBitField::ClrBit(const int n) {
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const {
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	TELEM elem = pMem[index] & mask;
	if (elem) {
		return 1;
	}
	else {
		return 0;
	}
}

int TBitField::operator==(const TBitField& bf) const {
	if (MemLen != bf.MemLen) {
		return 0;
	}
	int minLen, maxLen;
	const size_t size = sizeof(TELEM);
	TELEM zeroTELEM{};
	TELEM* mx;
	MemLen > bf.MemLen ? (mx = pMem, maxLen = MemLen, minLen = bf.MemLen) : (mx = bf.pMem, maxLen = bf.MemLen, minLen = MemLen);
	int i = 0;
	for (; i < minLen; ++i) {
		if (pMem[i] ^ bf.pMem[i]) {  //Проверка равенства нулю суммы по модулю 2 между двумя элементами 
			return 0;				  //на одинаковых позициях в pMem
		}
	}
	for (; i < maxLen; ++i) {
		if (mx[i] ^ zeroTELEM) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const {
	return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf) {
	if (this == &bf) {
		return *this;
	}
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

TBitField TBitField::operator|(const TBitField& bf) {
	TBitField Or(BitLen > bf.BitLen ? *this : bf);
	int minLen;
	MemLen > bf.MemLen ? minLen = bf.MemLen : minLen = MemLen;
	for (int i = 0; i < minLen; ++i) {
		Or.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return Or;
}

TBitField TBitField::operator&(const TBitField& bf) {
	TBitField And(BitLen > bf.BitLen ? BitLen : bf.BitLen);
	int minLen;
	MemLen > bf.MemLen ? minLen = bf.MemLen : minLen = MemLen;
	for (int i = 0; i < minLen; ++i) {
		And.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return And;
}

TBitField TBitField::operator~(void) {
	TBitField inv(*this);
	TELEM remainder = std::pow(2, BitLen % (sizeof(TELEM) * 8)) - 1;
	inv.pMem[0] = ~pMem[0];
	inv.pMem[0] &= remainder;
	// Необходимо для того, чтобы инвертировались только биты, относящиеся к полю
	// пусть Bitlen = 34, inv.pMem[0] = 111...1101, remainder = 000...0011, inv.pMem[1] & remainder = 000...0001  
	for (int i = 1; i < MemLen; ++i) {
		inv.pMem[i] = ~pMem[i];
	}
	return inv;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {
	for (int i = 0; i < bf.MemLen; ++i) {
		bf.pMem[i] &= 0;
	}
	std:: string field;
	istr >> field;
	if (field.length() != bf.BitLen) {
		throw std::length_error(std::string("Error! Size of entered bitfield must be a equal ") 
								+ std::string(std::to_string(bf.BitLen)));
	}
	for (int i = 0; i < bf.BitLen; ++i) {
		if (field[bf.BitLen - 1 - i] - '0' == 1) {
			bf.SetBit(i);
		}
		else if (field[bf.BitLen - 1 - i] - '0' != 0) {
			throw std::invalid_argument("BitField elements must be only 0 and 1");
		}
	}
	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
	for (int i = bf.BitLen - 1; i >= 0; --i) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}