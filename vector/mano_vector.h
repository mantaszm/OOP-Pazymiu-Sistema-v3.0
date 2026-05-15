#pragma once

#include <cstddef>
#include <algorithm>
#include <initializer_list>
#include <utility>

/**
 * @brief Dinaminis masyvas (std::vector analogas)
 * @tparam T elementų tipas
 */
template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    size_t reallocations_;

    /**
     * @brief Vidinis atminties didinimas
     */
    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;

        ++reallocations_;
    }

public:
    using iterator = T*;
    using const_iterator = const T*;

    /**
     * @brief Default konstruktorius
     */
    Vector()
        : data_(nullptr), size_(0), capacity_(0), reallocations_(0) {}

    /**
     * @brief Sukuria vector su n elementų
     */
    explicit Vector(size_t n, const T& value = T())
        : data_(new T[n]), size_(n), capacity_(n), reallocations_(0) {
        for (size_t i = 0; i < n; ++i)
            data_[i] = value;
    }

    /**
     * @brief initializer_list konstruktorius
     */
    Vector(std::initializer_list<T> init)
        : Vector(init.size()) {
        size_t i = 0;
        for (const auto& v : init)
            data_[i++] = v;
    }

    /**
     * @brief Destruktorius
     */
    ~Vector() {
        delete[] data_;
    }

    /**
     * @brief Copy konstruktorius
     */
    Vector(const Vector& other)
        : data_(new T[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_),
          reallocations_(0) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    /**
     * @brief Copy assignment
     */
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

    /**
     * @brief Move konstruktorius
     */
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

    /**
     * @brief Move assignment
     */
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

        return *this;
    }

    // =========================
    // ELEMENT ACCESS
    // =========================

    /**
     * @brief operator []
     */
    T& operator[](size_t i) { return data_[i]; }

    const T& operator[](size_t i) const { return data_[i]; }

    T& front() { return data_[0]; }
    T& back() { return data_[size_ - 1]; }

    const T& front() const { return data_[0]; }
    const T& back() const { return data_[size_ - 1]; }

    // =========================
    // CAPACITY
    // =========================

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    size_t getReallocations() const noexcept { return reallocations_; }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_)
            reallocate(new_cap);
    }

    void shrink_to_fit() {
        if (size_ < capacity_)
            reallocate(size_);
    }

    // =========================
    // MODIFIERS
    // =========================

    /**
     * @brief push_back
     */
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

    /**
     * @brief pop_back
     */
    void pop_back() {
        if (size_ > 0)
            --size_;
    }

    /**
     * @brief clear
     */
    void clear() {
        size_ = 0;
    }

    /**
     * @brief erase pagal index
     */
    void erase(size_t index) {
        if (index >= size_) return;

        for (size_t i = index; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);

        --size_;
    }

    /**
     * @brief erase iterator (vienas elementas)
     */
    iterator erase(iterator it) {
        size_t index = it - data_;

        for (size_t i = index; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);

        --size_;
        return data_ + index;
    }

    /**
     * @brief erase intervalas
     */
    iterator erase(iterator first, iterator last) {
        size_t start = first - data_;
        size_t endPos = last - data_;

        size_t shift = endPos - start;

        for (size_t i = start; i < size_ - shift; ++i)
            data_[i] = std::move(data_[i + shift]);

        size_ -= shift;
        return data_ + start;
    }

    /**
     * @brief insert
     */
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

    // =========================
    // ITERATORS
    // =========================

    iterator begin() { return data_; }
    iterator end() { return data_ + size_; }

    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ + size_; }

    // =========================
    // OPERATORS
    // =========================

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

    // =========================
    // UTILITY
    // =========================

    /**
     * @brief swap
     */
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(reallocations_, other.reallocations_);
    }
};
