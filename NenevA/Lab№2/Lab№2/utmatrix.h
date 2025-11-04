#pragma once

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
// Шаблон вектора
template <typename ValType>
class TVector
{
protected:
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
    ValType* pVector;
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() const { return Size; } // размер вектора
    int GetStartIndex() const { return StartIndex; } // индекс первого элемента
    ValType& operator[](int pos);             // доступ
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание

    // скалярные операции
    TVector  operator+(const ValType& val);   // прибавить скаляр
    TVector  operator-(const ValType& val);   // вычесть скаляр
    TVector  operator*(const ValType& val);   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    ValType  operator*(const TVector& v);     // скалярное произведение

    // ввод-вывод
    //Формат ввода - последовательность чисел разделенных пробелами или же ввод чисел поочередно
    friend std::istream& operator>> (std::istream& in, TVector& v) {
        for (int i = v.StartIndex; i < v.Size; ++i) {
            in >> v.pVector[i];
        }
        return in;
    }
    friend std::ostream& operator<< (std::ostream& out, const TVector& v) {
        for (int i = 0; i < v.StartIndex; ++i) {
            out << "0 ";
        }
        for (int i = v.StartIndex; i < v.Size; ++i) {
            out << v.pVector[i] << " ";
        }
        return out;
    }
};

// Верхнетреугольная матрица

template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<ValType>>& mt);  // преобразование типа
    bool operator==(const TMatrix& mt) const;      // сравнение
    bool operator!=(const TMatrix& mt) const;      // сравнение
    TMatrix& operator= (const TMatrix& mt);        // присваивание
    TMatrix  operator+ (const TMatrix& mt);        // сложение
    TMatrix  operator- (const TMatrix& mt);        // вычитание

    // ввод / вывод
    friend std::istream& operator>>(std::istream& in, TMatrix& mt) {
        for (int i = 0; i < mt.Size; ++i) {
            in >> mt.pVector[i];
        }
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) {
        for (int i = 0; i < mt.Size; ++i) {
            out << mt.pVector[i] << "\n";
        }
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si) {
    if (Size > MAX_VECTOR_SIZE || Size < 0 || si > MAX_VECTOR_SIZE || si < 0 || Size < si) {
        throw std::out_of_range("Incorrect output data");
    }
    pVector = new ValType[Size];
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (size_t i = StartIndex; i < Size; ++i) {
        pVector[i] = v.pVector[i]; // При этом элементы до StartIndex не инициализируются, но полагаются нулями
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
    pVector = nullptr;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < 0 || pos >= Size) {
        throw std::out_of_range("Index is out of range");
    }
    if (pos < StartIndex) { //На случай если мы не вполне понимаем что является нулем, например у некоего сложного класса
        throw std::out_of_range("Vector didn't get initialized at all before the start index");
    }
    return pVector[pos];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        return false;
    }
    for (size_t i = StartIndex; i < Size; ++i) {
        if (pVector[i] != v.pVector[i]) {
            return false;
        }
    }
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (*this == v) {
        return *this;
    }
    delete[] pVector;
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (size_t i = StartIndex; i < Size; ++i) {
        pVector[i] = v.pVector[i];
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) {
    TVector result(Size, 0); //В итоговом векторе все элементы будут инициализированы
    for (int i = 0; i < StartIndex; ++i) {//Инициализируем элементы, что были нулями значением val
        result.pVector[i] = val;
    }
    for (int i = StartIndex; i < Size; ++i) {
        result.pVector[i] = pVector[i] + val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) {
    TVector result(Size, 0);
    for (int i = 0; i < StartIndex; ++i) {
        result.pVector[i] = -val;//Инициализируем элементы, что были нулями значением  -val
    }
    for (int i = StartIndex; i < Size; ++i) {
        result.pVector[i] = pVector[i] - val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) {
    TVector result(Size, StartIndex);
    for (int i = StartIndex; i < Size; ++i) {
        result.pVector[i] = pVector[i] * val;//Умножаем на ненулевые элементы
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) {
    if (Size != v.Size) {
        throw std::invalid_argument("Operation is defined only for the vectors of the same dimension");
    }
    TVector result(Size, std::min(StartIndex, v.StartIndex));
    if (StartIndex < v.StartIndex) {//Если StartIndex операндов отличаются складываем значение pVector[i] с нулем
        for (int i = StartIndex; i < v.StartIndex; ++i) {
            result.pVector[i] = pVector[i];
        }
    }
    else {
        for (int i = v.StartIndex; i < StartIndex; ++i) {
            result.pVector[i] = v.pVector[i];
        }
    }
    int Max = std::max(StartIndex, v.StartIndex);
    for (int i = Max; i < Size; ++i) {
        result.pVector[i] = pVector[i] + v.pVector[i];
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) {
    if (Size != v.Size) {
        throw std::invalid_argument("Operation is defined only for the vectors of the same dimension");
    }
    TVector result(Size, std::min(StartIndex, v.StartIndex));
    if (StartIndex < v.StartIndex) {
        for (int i = StartIndex; i < v.StartIndex; ++i) {
            result.pVector[i] = pVector[i];
        }
    }
    else {
        for (int i = v.StartIndex; i < StartIndex; ++i) {
            result.pVector[i] = -v.pVector[i];
        }
    }
    int Max = std::max(StartIndex, v.StartIndex);
    for (int i = Max; i < Size; ++i) {
        result.pVector[i] = pVector[i] - v.pVector[i];
    }
    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) {
    if (Size != v.Size) {
        throw std::invalid_argument("Operation is defined only for the vectors of the same dimension");
    }
    ValType result = 0;
    int Max = std::max(StartIndex, v.StartIndex);
    for (int i = Max; i < Size; ++i) {//Начинаем с максимального StartIndex поскольку до него все слагаемые обратятся в ноль
        result += pVector[i] * v.pVector[i];
    }
    return result;
}

//Реализация TMatrix

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0) {
    if (s <= 0 || s > MAX_MATRIX_SIZE) {
        throw std::out_of_range("Incorrect matrix size provided");
    }
    for (int i = 0; i < s; ++i) {
        this->pVector[i] = TVector<ValType>(s, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt_vec) : TVector<TVector<ValType>>(mt_vec) {
    if (this->Size != mt_vec.GetSize() || this->StartIndex != mt_vec.GetStartIndex()) {
        throw std::invalid_argument("Internal error during TMatrix conversion construction based on base TVector copy.");
    }
    for (int i = 0; i < this->Size; ++i) {
        if (this->pVector[i].GetStartIndex() != i || this->pVector[i].GetSize() != this->Size) {
            throw std::invalid_argument("Input TVector<TVector<ValType>> does not represent a valid upper triangular matrix (invalid StartIndex or Size in row " + std::to_string(i) + ").");
        }
    }
}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        return false;
    }
    for (int i = 0; i < mt.Size; ++i) {//Сравниваем построчно
        if (this->pVector[i] != mt.pVector[i]) {
            return false;
        }
    }
    return true;
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    if (this != &mt) {
        TVector<TVector<ValType>>::operator=(mt);
    }
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+ (const TMatrix& mt) {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("Matrix addition is only defined for matrices of the same dimension");
    }
    TMatrix<ValType> result(this->Size);
    for (int i = 0; i < this->Size; i++) {
        result.pVector[i] = this->pVector[i] + mt.pVector[i];
    }
    return result;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator- (const TMatrix& mt) {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("Matrix subtraction is only defined for matrices of the same dimension");
    }
    TMatrix<ValType> result(this->Size);
    for (int i = 0; i < this->Size; i++) {
        result.pVector[i] = this->pVector[i] - mt.pVector[i];
    }
    return result;
}