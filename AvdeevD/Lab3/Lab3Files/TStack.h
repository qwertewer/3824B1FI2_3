#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class TStack {
private:
    std::vector<T> data;
    int topIndex;
    int capacity;

public:
    TStack(int size = 100);
    TStack(const TStack& other);
    ~TStack();

    void Push(const T& value);
    T Pop();
    T Peek() const;
    bool IsEmpty() const;
    bool IsFull() const;
    int GetSize() const;
    void Clear();

    TStack& operator=(const TStack& other);
};

template <typename T>
TStack<T>::TStack(int size) : capacity(size), topIndex(-1) {
    if (size <= 0) {
        throw std::invalid_argument("Stack size should be >= 0.");
    }
    data.reserve(size);
}

template <typename T>
TStack<T>::TStack(const TStack& other)
    : data(other.data), topIndex(other.topIndex), capacity(other.capacity) {
}

template <typename T>
TStack<T>::~TStack() {
    Clear();
}

template <typename T>
void TStack<T>::Push(const T& value) {
    if (IsFull()) {
        throw std::overflow_error("Stack is full");
    }
    data.push_back(value);
    topIndex++;
}

template <typename T>
T TStack<T>::Pop() {
    if (IsEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    T value = data[topIndex];
    data.pop_back();
    topIndex--;
    return value;
}

template <typename T>
T TStack<T>::Peek() const {
    if (IsEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[topIndex];
}

template <typename T>
bool TStack<T>::IsEmpty() const {
    return topIndex == -1;
}

template <typename T>
bool TStack<T>::IsFull() const {
    return topIndex == capacity - 1;
}

template <typename T>
int TStack<T>::GetSize() const {
    return topIndex + 1;
}

template <typename T>
void TStack<T>::Clear() {
    data.clear();
    topIndex = -1;
}

template <typename T>
TStack<T>& TStack<T>::operator=(const TStack& other) {
    if (this != &other) {
        data = other.data;
        topIndex = other.topIndex;
        capacity = other.capacity;
    }
    return *this;
}