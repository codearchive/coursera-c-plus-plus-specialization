#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    ~SimpleVector();
    T& operator[](size_t index);
    const T* begin() const;
    const T* end() const;
    T* begin();
    T* end();
    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
    : data_(new T[size]), size_(size), capacity_(size)
{}

template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data_;
}

template<typename T>
T& SimpleVector<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
const T* SimpleVector<T>::begin() const {
    return data_;
}

template<typename T>
const T* SimpleVector<T>::end() const {
    return data_ + size_;
}

template<typename T>
T* SimpleVector<T>::begin() {
    return data_;
}

template<typename T>
T* SimpleVector<T>::end() {
    return data_ + size_;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return size_;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}

template<typename T>
void SimpleVector<T>::PushBack(const T& value) {
    if (capacity_ == 0) {
        capacity_ = 1;
        data_ = new T[capacity_];
    }
    else if (size_ >= capacity_) {
        capacity_ *= 2;
        T* new_data_ = new T[capacity_];
        std::copy(data_, data_ + size_, new_data_);
        delete[] data_;
        data_ = new_data_;
    }
    data_[size_++] = value;
}
