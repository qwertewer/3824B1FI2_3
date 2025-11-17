#pragma once

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
// Ўаблон вектора
template <typename ValType>
class TVector
{
protected:
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
    ValType* pVector;
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // конструктор копировани€
    ~TVector();
    int GetSize() const { return Size; } // размер вектора
    int GetStartIndex() const { return StartIndex; } // индекс первого элемента
    ValType& operator[](int pos);             // доступ
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание

    // скал€рные операции
    TVector  operator+(const ValType& val);   // прибавить скал€р
    TVector  operator-(const ValType& val);   // вычесть скал€р
    TVector  operator*(const ValType& val);   // умножить на скал€р

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    ValType  operator*(const TVector& v);     // скал€рное произведение

    // ввод-вывод
    //‘ормат ввода - последовательность чисел разделенных пробелами или же ввод чисел поочередно
    friend std::istream& operator>> (std::istream& in, TVector& v) {
        for (int i = 0; i < v.Size- v.StartIndex; ++i) {
            in >> v.pVector[i];
        }
        return in;
    }
    friend std::ostream& operator<< (std::ostream& out, const TVector& v) {
        for (int i = 0; i < v.StartIndex; ++i) {
            out << "0 ";
        }
        for (int i = 0; i < v.Size- v.StartIndex; ++i) {
            out << v.pVector[i] << " ";
        }
        return out;
    }
};

// ¬ерхнетреугольна€ матрица

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
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si), pVector(nullptr) {
    if (s > MAX_VECTOR_SIZE || s < 0 || si > MAX_VECTOR_SIZE || si < 0 || s < si) {
        throw std::out_of_range("Incorrect output data");
    }
    pVector = new ValType[Size - StartIndex]();
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size - StartIndex];
    for (size_t i = 0; i < Size- StartIndex; ++i) {
        pVector[i] = v.pVector[i];
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
    pVector = nullptr;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos >= Size) {
        throw std::out_of_range("Index is out of range");
    }
    if (pos < StartIndex) { //Ќа случай если мы не вполне понимаем что €вл€етс€ нулем, например у некоего сложного класса
        throw std::out_of_range("Vector didn't get initialized at all before the start index");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        return false;
    }
    for (size_t i = 0; i < Size-StartIndex; ++i) {
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
    if (this == &v) {
        return *this;
    }
    TVector temp(v);
    std::swap(Size, temp.Size);
    std::swap(StartIndex, temp.StartIndex);
    std::swap(pVector, temp.pVector);
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) {
    TVector result(Size, 0); //¬ итоговом векторе все элементы будут инициализированы
    for (int i = 0; i < StartIndex; ++i) {
        result.pVector[i] = val;
    }
    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i + StartIndex] = pVector[i] + val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) {
    TVector result(Size, 0);
    for (int i = 0; i < StartIndex; ++i) {
        result.pVector[i] = -val;
    }
    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i + StartIndex] = pVector[i] - val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size- StartIndex; ++i) {
        result.pVector[i] = pVector[i] * val;//”множаем на ненулевые элементы
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) {
    if (Size != v.Size) {
        throw std::runtime_error("The vectors have different sizes");
    }
    int Min = std::min(StartIndex, v.StartIndex);
    TVector<ValType> result(Size, Min);

    if (Min == StartIndex) {
        for (size_t i = Min; i < v.StartIndex; ++i) {
            result[i] = (*this)[i];
        }
        for (size_t i = v.StartIndex; i < Size; ++i) {
            result[i] = (*this)[i] + v.pVector[i - v.StartIndex];
        }
    }
    else {
        for (size_t i = Min; i < StartIndex; ++i) {
            result[i] = v.pVector[i - v.StartIndex];
        }
        for (size_t i = StartIndex; i < Size; ++i) {
            result[i] = (*this)[i] + v.pVector[i - v.StartIndex];
        }
    }

    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) {
    if (this->Size != v.Size) {
        throw std::runtime_error("The vectors have different sizes");
    }
    int Min = std::min(StartIndex, v.StartIndex);
    TVector<ValType> result(Size, Min);

    if (Min == StartIndex) {
        for (size_t i = Min; i < v.StartIndex; ++i) {
            result[i] = (*this)[i];
        }
        for (size_t i = v.StartIndex; i < Size; ++i) {
            result[i] = (*this)[i] - v.pVector[i - v.StartIndex];
        }
    }
    else {
        for (size_t i = Min; i < StartIndex; ++i) {
            result[i] = -v.pVector[i - v.StartIndex];
        }
        for (size_t i = StartIndex; i < Size; ++i) {
            result[i] = (*this)[i] - v.pVector[i - v.StartIndex];
        }
    }

    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) {
    if (Size != v.Size) {
        throw std::invalid_argument("Vectors must be of the same size");
    }
    ValType result = 0;
    int maxStartIndex = std::max(StartIndex, v.StartIndex);

    for (int i = maxStartIndex; i < Size; ++i) {
        ValType val1 = (i >= StartIndex) ? pVector[i - StartIndex] : ValType(0);
        ValType val2 = (i >= v.StartIndex) ? v.pVector[i - v.StartIndex] : ValType(0);
        result += val1 * val2;
    }
    return result;
}

//–еализаци€ TMatrix
//”брал некоторые исключени€, поскольку их бросают операции вектора
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
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    return static_cast<const TVector<TVector<ValType>>&>(*this) == static_cast<const TVector<TVector<ValType>>&>(mt);
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
    TMatrix<ValType> result(this->Size);
    for (int i = 0; i < this->Size; i++) {
        result.pVector[i] = this->pVector[i] + mt.pVector[i];
    }
    return result;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator- (const TMatrix& mt) {
    TMatrix<ValType> result(this->Size);
    for (int i = 0; i < this->Size; i++) {
        result.pVector[i] = this->pVector[i] - mt.pVector[i];
    }
    return result;
}