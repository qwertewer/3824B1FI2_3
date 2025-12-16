#include "tbitfield.h"
#include <limits>
#include <sstream> //для тестов ввода и вывода

int TBitField::GetMemIndex(const int n) const {  //индекс элемента pMem, в котором находится бит n
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Error! Incorrect bit index");
	}

	int bitsInElem = std::numeric_limits<TELEM>::digits;  //сколько битов в типе TELEM 
	int a = 1;
	size_t count = 0;
	while (a < bitsInElem) {
		a <<= 1;
		++count;
	}

	return n >> count; //32=2^5 ~ n/(sizeof(TELEM)*8) 
}

TELEM TBitField::GetMemMask(const int n) const
{
	size_t bitsInElem = std::numeric_limits<TELEM>::digits;

	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Error! Incorrect bit index");
	}
	size_t bitInd = n & (bitsInElem - 1); //индекс бита в элементе
	return 1 << bitInd; //получим маску, в которой все нули, кроме бита n
}



//конструкторы и деструктор
TBitField::TBitField(int len)
{
	if (len < 0) {
		throw std::invalid_argument("Error! The length is less than zero");
	}

	BitLen = len;
	MemLen = (len + (8 * sizeof(TELEM) - 1)) / (8 * sizeof(TELEM));
	pMem = len > 0 ? new TELEM[MemLen]() : nullptr;

}


TBitField::TBitField(const TBitField& bf)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (BitLen != 0) {
		pMem = new TELEM[bf.MemLen];
		for (size_t i = 0; i < bf.MemLen; ++i) {
			pMem[i] = bf.pMem[i];
		}
	}
	else {
		pMem = nullptr;
	}
}


TBitField::~TBitField()
{
	delete[]pMem;
	pMem = nullptr;
}


//доступ к битам
int TBitField::GetLength(void) const {
	return BitLen;
}

void TBitField::SetBit(const int n) //установить бит
{
	if (pMem == nullptr) {
		throw std::runtime_error("The length of the bit field is 0. No memory allocated for objects");
	}

	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Error! Incorrect bit index");
	}

	pMem[GetMemIndex(n)] |= GetMemMask(n); //1 бит меняется на единицу


}

void TBitField::ClrBit(const int n)
{
	if (pMem == nullptr) {
		throw std::runtime_error("The length of the bit field is 0. No memory allocated for objects");
	}

	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Error! Incorrect bit index");
	}

	pMem[GetMemIndex(n)] &= ~(GetMemMask(n));


}

int TBitField::GetBit(const int n) const
{
	if (pMem == nullptr) {
		throw std::runtime_error("The length of the bit field is 0. No memory allocated for objects");
	}

	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Error! Incorrect bit index");
	}

	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0);

}

//битовые операции

int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen != bf.BitLen) { //из BitLen следует MemLen
		return 0;
	}

	if (this->pMem == nullptr && bf.pMem == nullptr) { //объекты равны
		return 1;
	}

	for (size_t i = 0; i < bf.MemLen; ++i) {
		if (this->pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(*this==bf); 
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	if (&pMem == &bf.pMem) {
		return *this;
	};
	delete[]pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (BitLen != 0) {
		pMem = new TELEM[bf.MemLen];
		for (size_t i = 0; i < bf.MemLen; ++i) {
			pMem[i] = bf.pMem[i];
		}
	}
	else {
		pMem = nullptr;
	}
	return *this;
}

TBitField TBitField::operator|(const TBitField& bf)
{
	/////
	if (this->pMem == nullptr) {
		return bf;
	}
	else if (bf.pMem == nullptr) {
		return *this;
	}
	/////

	int new_len = (this->BitLen >= bf.BitLen ? this->BitLen : bf.BitLen); //выбираем наибольшую длину
	TBitField new_field(new_len);

	for (size_t i = 0; i < this->MemLen; ++i) {
		new_field.pMem[i] = this->pMem[i]; //в новый объект скопировали старый
	}
	for (size_t i = 0; i < bf.MemLen; ++i) {
		new_field.pMem[i] |= bf.pMem[i]; //делаем побитовое или
	}

	return new_field;
}

TBitField TBitField::operator&(const TBitField& bf)
{
	//////
	if (this->pMem == nullptr) {
		return bf;
	}
	else if (bf.pMem == nullptr) {
		return *this;
	}
	//////
	
	int max_len = (this->BitLen >= bf.BitLen ? this->BitLen : bf.BitLen); 
	TBitField new_field(max_len);

	int min_mem_len = (this->MemLen >= bf.MemLen ? bf.MemLen : this->MemLen);
	for (size_t i = 0; i < min_mem_len; ++i) {
		new_field.pMem[i] = this->pMem[i] & bf.pMem[i];
	}

	if (this->MemLen > bf.MemLen) {
		for (size_t i = min_mem_len; i < this->MemLen; ++i) {
			new_field.pMem[i] = 0;
		}
	}
	else {
		for (size_t i = min_mem_len; i < bf.MemLen; ++i) { 
			new_field.pMem[i] = 0;
		}
	}
	return new_field; 
}

TBitField TBitField::operator~(void) {
	TBitField new_field(this->BitLen);

	if (this->BitLen == 0) {
		throw std::runtime_error("Error! The field length is 0");
	}

	for (int i = 0; i < this->MemLen; ++i) {
		new_field.pMem[i] = ~this->pMem[i];
	}

	size_t bits_in_last_elem = this->BitLen % (sizeof(TELEM) * 8); // количество используемых битов в последнем элементе
	if (bits_in_last_elem > 0) {
		TELEM mask = ((TELEM)1 << bits_in_last_elem) - 1; // маска для используемых битов 
		new_field.pMem[this->MemLen - 1] &= mask; // применение маски к последнему элементу
	}
	return new_field;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {

	std::string str;
	istr >> str;

	int len = str.size();

	if (len != bf.BitLen) {
		throw std::runtime_error("Error!! Incorrect length");
	}

	for (int i = 0; i < len; ++i) {
		if (str[i] != '1' && str[i] != '0') {
			throw std::invalid_argument("Incorrect symbol");
		}
	}

	for (int i = len - 1, j = 0; i >= 0, j < len; --i, ++j) {
		if (str[j] == '1') {
			bf.SetBit(i);
		}
		else {
			bf.ClrBit(i);
		}
	}
	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf)
{
	if (bf.BitLen == 0) {
		throw std::runtime_error("The field length is 0");
	}

	for (int i = bf.BitLen - 1; i >= 0; --i) {
		ostr << static_cast<char>('0' + bf.GetBit(i));
	}

	return ostr;
}