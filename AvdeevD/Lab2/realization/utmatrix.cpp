#pragma once

#include <iostream>
#include "utmatrix.h"
#include <exception>


using namespace std;

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
	if (s > MAX_VECTOR_SIZE || s < 0) {
		throw invalid_argument("Invalid size.");
	}
	Size = s;
	if (si < 0 || si > s) {
		throw out_of_range("Invalid starting index.");
	}
	StartIndex = si;
	if (Size > 0) {
		pVector = new ValType[Size];
		for (size_t i = 0; i < Size; i++) {
			pVector[i] = ValType();
		}
	}
	else {
		pVector = nullptr;
	}
}
template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
	if (v.Size > 0) {
		Size = v.Size;
		StartIndex = v.StartIndex;
		pVector = new ValType[Size];
		for (size_t i = 0; i < Size; i++) {
			pVector[i] = v.pVector[i];
		}
	}
	else {
		pVector = nullptr;
		Size = 0;
		StartIndex = 0;
	}
}
template <class ValType>
TVector<ValType>::~TVector() {
	delete[] pVector;
	pVector = nullptr;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
	if (pos < StartIndex || pos >= Size) {
		throw out_of_range("Wrong position.");
	}
	return pVector[pos];
}
template <class ValType>
bool TVector<ValType>::operator==(const TVector &v) const {
	if (Size == 0 && v.Size == 0) {
		return true;
	}
	if (Size == v.Size) {
		if (StartIndex == v.StartIndex) {
			for (size_t i = StartIndex; i < Size; i++) {
				if (pVector[i] != v.pVector[i]) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
	if (Size == 0 && v.Size == 0) {
		return false;
	}
	if (Size == v.Size) {
		if (StartIndex == v.StartIndex) {
			for (size_t i = StartIndex; i < Size; i++) {
				if (pVector[i] != v.pVector[i]) {
					return true;
				}
			}
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}
template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
	if (this == &v) {
		return *this;
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
	delete[] pVector;
	if (Size == 0) {
		pVector = nullptr;
		return *this;
	}
	pVector = new ValType[Size];
	for (size_t i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
	return *this;
}
//skalyar
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) {
	TVector<ValType> result(Size, 0);
	for (size_t i = 0; i < Size; i++) {
		result.pVector[i] = pVector[i] + val;
	}
	return result;
}
template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) {
	TVector<ValType> result(Size, 0);
	for (size_t i = 0; i < Size; i++) {
		result.pVector[i] = pVector[i] * val;
	}
	return result;
}
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) {
	TVector<ValType> result(Size, 0);
	for (size_t i = 0; i < Size; i++) {
		result.pVector[i] = pVector[i] - val;
	}
	return result;
}
//vector
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) {
	if (Size != v.Size) {
		throw invalid_argument("Unable to sum vectors with different sizes.");
	}
	if (StartIndex < v.StartIndex) {
		TVector<ValType> result(*this);
		for (size_t i = v.StartIndex; i < Size; i++) {
			result.pVector[i] = pVector[i] + v.pVector[i];
		}
		return result;
	}
	else {
		TVector<ValType> result(v);
		for (size_t i = StartIndex; i < Size; i++) {
			result.pVector[i] = pVector[i] + v.pVector[i];
		}
		return result;
	}
}
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) {
	if (Size != v.Size) {
		throw invalid_argument("Unable to substract vectors with different sizes.");
	}
	if (StartIndex < v.StartIndex) {
		TVector<ValType> result(*this);
		for (size_t i = v.StartIndex; i < Size; i++) {
			result.pVector[i] = pVector[i] - v.pVector[i];
		}
		return result;
	}
	else {
		TVector<ValType> result(Size, v.StartIndex);
		for (size_t i = v.StartIndex; i < Size; i++) {
			result.pVector[i] = pVector[i] - v.pVector[i];
		}
		return result;
	}
}
template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) {
	if (Size != v.Size) {
		throw invalid_argument("Different sizes of vectors.");
	}
	if (Size == 0) {
		return ValType(0);
	}
	if (StartIndex < v.StartIndex) {
		ValType result{};
		for (size_t i = v.StartIndex; i < Size; i++) {
			result += pVector[i] * v.pVector[i];
		}
		return result;
	}
	else {
		ValType result{};
		for (size_t i = StartIndex; i < Size; i++) {
			result += pVector[i] * v.pVector[i];
		}
		return result;
	}
}

//matrix
template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType>>(s, 0) {
	if (s < 0 || s > MAX_MATRIX_SIZE) {
		throw invalid_argument("Invalid size.");
	}
	for (size_t i = 0; i < s; i++) {
		pVector[i] = TVector<ValType>(s, i);
	}
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

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
	TVector<TVector<ValType>>::operator=(mt);
	return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) {
	return TVector<TVector<ValType>>::operator+(mt);
}
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) {
	return TVector<TVector<ValType>>::operator-(mt);
}

