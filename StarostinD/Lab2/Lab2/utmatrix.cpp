#include "utmatrix.h"
#include <exception>

//TVector
template <class ValType>
TVector<ValType>::TVector(int s, int si) {
	if (s < 0 || s > MAX_VECTOR_SIZE) {
		throw std::invalid_argument("The size can't be less than 0 or greater than MAX_VECTOR_SIZE");
	}
	if (si < 0 || si >= s) {
		throw std::invalid_argument("The start index can't be greater than size or less than 0");
	}
	pVector = new ValType[s - si]();
	Size = s;
	StartIndex = si;
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {      // конструктор копирования
	pVector = new ValType[v.Size - v.StartIndex]();
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i = 0; i < Size  - StartIndex; ++i) {
		pVector[i] = v.pVector[i];
	}
}

template <class ValType>
TVector<ValType>::~TVector() {					   // деструктор 
	delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {   // доступ
	if (pos >= Size || pos < StartIndex) {
		throw std::out_of_range("Wrong index");
	}
	return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {  // сравнение
	if (Size != v.Size) {
		return false;
	}
	int i = v.StartIndex;
	if (StartIndex > v.StartIndex) {
		i = v.StartIndex;
		while (i < StartIndex) {
			if (v.pVector[i++ - v.StartIndex] != ValType()) {
				return false;
			}
		}
	} else if(v.StartIndex > StartIndex) {
		i = StartIndex;
		while (i < v.StartIndex) {
			if (pVector[i++ - StartIndex] != ValType()) {
				return false;
			}
		}
	}
	for (i; i < Size; ++i) {
		if (pVector[i- StartIndex] != v.pVector[i - v.StartIndex]) {
			return false;
		}
	}
	return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {  // сравнение
	return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {     // присваивание
	if (this == &v) {
		return *this;
	}
	if (Size != v.Size) {
		ValType* pTmp = new ValType[v.Size - v.StartIndex]();
		delete[] pVector;
		Size = v.Size;
		pVector = pTmp;
	}
	StartIndex = v.StartIndex;
	std::copy(v.pVector, v.pVector + Size - StartIndex, pVector);
	return *this;
}

// скалярные операции

template <class ValType>
TVector<ValType>  TVector<ValType>::operator+(const ValType& val) {   // прибавить скаляр
	TVector<ValType> sum(*this);
	for (int i = 0; i < Size - StartIndex; ++i) {
		sum.pVector[i] = sum.pVector[i] + val;
	}
	return sum;
}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator-(const ValType& val) {   // вычесть скаляр
	TVector<ValType> diff(*this);
	for (int i = 0; i < Size - StartIndex; ++i) {
		diff.pVector[i] = diff.pVector[i] - val;
	}
	return diff;
}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator*(const ValType& val) {   // умножить на скаляр
	TVector<ValType> product(*this);
	for (int i = 0; i < Size - StartIndex; ++i) {
		product.pVector[i] = product.pVector[i] * val;
	}
	return product;
}

// векторные операции

template <class ValType>
TVector<ValType>  TVector<ValType>::operator+(const TVector& v) {   // сложение векторов
	if (Size != v.Size) {
		throw std::invalid_argument("Addition of vectors of different sizes is undefined");
	}
	if (StartIndex < v.StartIndex) {
		TVector<ValType> sum(*this);
		int gap = v.StartIndex - StartIndex;
		for (int i = 0; i < v.Size - v.StartIndex; ++i) {
			sum.pVector[i + gap] = sum.pVector[i + gap] + v.pVector[i];
		}
		return sum;
	}
	else {
		TVector<ValType> sum(v);
		int gap = StartIndex - v.StartIndex;
		for (int i = 0; i < Size - StartIndex; ++i) {
			sum.pVector[i + gap] = sum.pVector[i + gap] + pVector[i];
		}
		return sum;
	}
}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator-(const TVector& v) {   // вычитание векторов
	if (Size != v.Size) {
		throw std::invalid_argument("Subtraction of vectors of different sizes is undefined");
	}
	if (StartIndex < v.StartIndex) {
		TVector<ValType> diff(*this);
		int gap = v.StartIndex - StartIndex;
		for (int i = v.StartIndex; i < v.Size - v.StartIndex; ++i) {
			diff.pVector[i + gap] = diff.pVector[i + gap] + v.pVector[i];
		}
		return diff;
	}
	else {
		TVector<ValType> diff(v);
		int gap = StartIndex - v.StartIndex;
		for (int i = 0; i < gap; ++i) {
			diff.pVector[i] = -diff.pVector[i];
		}
		for (int i = 0; i < Size - StartIndex; ++i) {
			diff.pVector[i + gap] = -diff.pVector[i + gap] + pVector[i];
		}
		return diff;
	}
}

template <class ValType>
ValType  TVector<ValType>::operator*(const TVector& v) {            // скалярное произведение
	if (Size != v.Size) {
		throw std::invalid_argument("The scalar product of vectors of different sizes is undefined");
	}
	ValType prod{};
	int gap = StartIndex - v.StartIndex;
	gap *= gap < 0 ? -1 : 1;
	if (StartIndex > v.StartIndex) {
		for (int i = 0; i < Size - StartIndex; ++i) {
			prod = prod + pVector[i] * v.pVector[i + gap];
		}
	}
	else {
		for (int i = 0; i < Size - v.StartIndex; ++i) {
			prod = prod + pVector[i + gap] * v.pVector[i];
		}
	}
	return prod;
}



//Верхнетреугольная матрица TMatrix

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType>>(s, 0) {
	if (s < 0 || s > MAX_MATRIX_SIZE) {
		throw std::invalid_argument("The size can't be less than 0 or greater than MAX_MATRIX_SIZE");
	}
	for (int i = 0; i < s; ++i) {
		this->pVector[i] = TVector<ValType>(s, i);
	}
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {};

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) {
	TVector<TVector<ValType>> cp = mt;
	if (cp.GetStartIndex() != 0) {
		throw std::invalid_argument("Not an upper triangular matrix");
	}
	this->StartIndex = 0;
	for (int i = 0; i < cp.GetSize(); ++i) {
		if (cp[i].GetSize() != cp.GetSize() || cp[i].GetStartIndex() != i) {
			throw std::invalid_argument("Not an upper triangular matrix");
		}
		else {
			this->pVector[i] = cp[i];
		}
	}
	this->Size = cp.GetSize();
};

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
	return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
	return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
	if (this == &mt) {
		return *this;
	}
	if (this->Size != mt.Size) {
		TVector<ValType>* pTmp = new TVector<ValType>[mt.Size]();
		delete[] this->pVector;
		this->Size = mt.Size;
		this->pVector = pTmp;
	}
	std::copy(mt.pVector, mt.pVector + mt.Size, this->pVector);
	return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) {
	if (this->Size != mt.Size) {
		throw std::invalid_argument("It is impossible to add matrices of different sizes");
	}
	TMatrix<ValType> sum(*this);
	for (int i = 0; i < this->Size; ++i) {
		sum[i] = this->pVector[i] + mt.pVector[i];
	}
	return sum;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) {
	if (this->Size != mt.Size) {
		throw std::invalid_argument("It is impossible to subtract matrices of different sizes");
	}
	TMatrix<ValType> diff(*this);
	for (int i = 0; i < this->Size; ++i) {
		diff[i] = this->pVector[i] - mt.pVector[i];
	}
	return diff;
}
