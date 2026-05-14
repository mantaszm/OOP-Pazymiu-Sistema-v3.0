#pragma once

#include <cstddef>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    size_t reallocations_;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;

        ++reallocations_;
    }

public:
    // Constructors / Destructor
    Vector()
        : data_(nullptr), size_(0), capacity_(0), reallocations_(0) {}

    explicit Vector(size_t n, const T& value = T())
        : data_(new T[n]), size_(n), capacity_(n), reallocations_(0) {
        for (size_t i = 0; i < n; ++i)
            data_[i] = value;
    }

    Vector(std::initializer_list<T> init)
        : Vector(init.size()) {
        size_t i = 0;
        for (const auto& v : init)
            data_[i++] = v;
    }

    ~Vector() {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        reallocations_ = 0;
    }

    // Copy
    Vector(const Vector& other)
        : data_(new T[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_),
          reallocations_(0) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        T* new_data = new T[other.capacity_];

        for (size_t i = 0; i < other.size_; ++i)
            new_data[i] = other.data_[i];

        delete[] data_;

        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }

    //Move
    Vector(Vector&& other) noexcept
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_),
          reallocations_(other.reallocations_) {

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.reallocations_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        reallocations_ = other.reallocations_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.reallocations_ = 0;

        return *this;
    }

    // Element access
    T& operator[](size_t i) {
        return data_[i];
    }

    const T& operator[](size_t i) const {
        return data_[i];
    }

    T& front() { return data_[0]; }
    T& back() { return data_[size_ - 1]; }

    const T& front() const { return data_[0]; }
    const T& back() const { return data_[size_ - 1]; }

    // Capacity
    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    size_t getReallocations() const noexcept { return reallocations_; }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) return;
        reallocate(new_cap);
    }

    void shrink_to_fit() {
        if (size_ < capacity_) {
            reallocate(size_);
        }
    }

    // Modifiers
    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ > 0) --size_;
    }

    void clear() {
        size_ = 0;
    }

    void erase(size_t index) {
        if (index >= size_) return;

        for (size_t i = index; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);

        --size_;
    }

    void insert(size_t index, const T& value) {
        if (index > size_) return;

        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }

        for (size_t i = size_; i > index; --i)
            data_[i] = std::move(data_[i - 1]);

        data_[index] = value;
        ++size_;
    }

    // Iterators
    T* begin() { return data_; }
    T* end() { return data_ + size_; }

    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    // Operators
    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;

        for (size_t i = 0; i < size_; ++i)
            if (data_[i] != other.data_[i])
                return false;

        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // Utility
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(reallocations_, other.reallocations_);
    }
};