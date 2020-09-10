#pragma once

#include <array>
#include <stdexcept>

template<typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    typename std::array<T, N>::iterator begin();
    typename std::array<T, N>::iterator end();
    const typename std::array<T, N>::const_iterator begin() const;
    const typename std::array<T, N>::const_iterator end() const;

    size_t Size() const;
    size_t Capacity() const;

    void PushBack(const T& value);
    T PopBack();
private:
    std::array<T, N> data_;
    size_t capacity_ = N;
    size_t size_ = 0;
};

template<typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) {
    if (a_size > N) {
        throw std::invalid_argument("invalid_argument");
    }
    capacity_ = N;
    size_ = a_size;
}

template<typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index) {
    return data_[index];
}

template<typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const {
    return data_[index];
}

template<typename T, size_t N>
typename std::array<T, N>::iterator StackVector<T, N>::begin() {
    return data_.begin();
}

template<typename T, size_t N>
typename std::array<T, N>::iterator StackVector<T, N>::end() {
    return data_.begin() + size_;
}

template<typename T, size_t N>
const typename std::array<T, N>::const_iterator StackVector<T, N>::begin() const {
    return data_.begin();
}

template<typename T, size_t N>
const typename std::array<T, N>::const_iterator StackVector<T, N>::end() const {
    return data_.begin() + size_;
}

template<typename T, size_t N>
size_t StackVector<T, N>::Size() const {
    return size_;
}

template<typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
    return capacity_;
}

template<typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value) {
    if (size_ < capacity_) {
        data_[size_++] = value;
    }
    else {
        throw std::overflow_error("overflow_error");
    }
}

template<typename T, size_t N>
T StackVector<T, N>::PopBack() {
    if (!size_) throw std::underflow_error("underflow_error");
    return data_[--size_];
}
