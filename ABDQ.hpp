#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic data_
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() noexcept;

    size_t getMaxCapacity() const
    {
        return capacity_;
    }

    T* getData() const
    {
        return data_;
    }

    void ensureCapacity()
    {
        std::size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* temp = new T[newCapacity];

        size_t i = 0;

        for (i = 0; i < size_; i++)
        {
            *(temp + i) = *(data_ + ((front_ + i) % (capacity_)));
        }
        
        delete[] data_;
        data_ = temp;

        capacity_ = newCapacity;

        temp = nullptr;        
        front_ = 0;
        back_ = i;  
    }

    void shrinkIfNeeded()
    {
        capacity_ /= 2;
    }

    // Insertion
    void pushFront(const T& item) override
    {
        if (size_ == capacity_)
        {
            ensureCapacity();
        }

        front_ = (front_ + capacity_ - 1) % capacity_;
        *(data_ + front_) = item;
        size_++;
    }
    void pushBack(const T& item) override
    {
        if (size_ == capacity_)
        {
            ensureCapacity();
        }
        *(data_ + back_) = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override
    {
        if (size_ == 0)
        {
            throw std::runtime_error("PopFront on Empty Deque");
        }

        T o = *(data_ + front_);
        front_ = (front_ + 1) % capacity_;

        size_--;

        return o;
    }
    T popBack() override
    {
        if (size_ == 0)
        {
            throw std::runtime_error("PopBack on Empty Deque");
        }

        back_ = (back_ + capacity_ - 1) % capacity_;
        T o = *(data_ + back_);

        size--;

        return o;
    }

    // Access
    const T& front() const override
    {
        if (size_ == 0)
            throw std::runtime_error("front() on empty deque");
        return *(data_ + front_);
    }
    const T& back() const override
    {
        if (size_ == 0)
            throw std::runtime_error("back() on empty deque");
        return *(data_ + ((back_ + capacity_ - 1) % capacity_));
    }

    // Getters
    [[nodiscard]] std::size_t getSize() const noexcept override
    {
        return size_;
    }
};


    // Big 5 + Parameterized Constructor
    template<typename T>
    ABDQ<T>::ABDQ()
    {
        capacity_ = 1;
        size_ = 0;
        data_ = new T[capacity_];
        back_ = 0;
        front_ = 0;
    }
    template<typename T>
    ABDQ<T>::ABDQ(const size_t capacity)
    {
        this->capacity_ = capacity;
        size_ = 0;
        data_ = new T[capacity_];
        back_ = 0;
        front_ = 0;
    }
    template<typename T>
    ABDQ<T>::ABDQ(const ABDQ& other)
    {
        this->capacity_ = other.getMaxCapacity();
        this->size_ = other.getSize();

        this->data_ = new T[capacity_];
        
        for (size_t i = 0; i < size_; i++)
        {
            *(data_ + i) = *(other.data_ + ((other.front_ + i) % other.capacity_));
        }

        this->front_ = 0;
        this->back_ = size_;
    }
    template<typename T>
    ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs)
    {
        if (&rhs == this)
            return *this;
        
        delete[] this->data_;

        this->capacity_ = rhs.getMaxCapacity();
        this->size_ = rhs.getSize();

        this->data_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++)
        {
            *(data_ + i) = *(rhs.data_ + ((rhs.front_ + i) % rhs.capacity_));
        }

        this->back_ = size_;
        this->front_ = 0;

        return *this;
    }
    template<typename T>
    ABDQ<T>::ABDQ(ABDQ&& other) noexcept
    {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->back_ = other.back_;
        this->front_ = other.front_;
        this->data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }
    template<typename T>
    ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept
    {
        if (&rhs == this) return *this;

        this->capacity_ = rhs.capacity_;
        this->size_ = rhs.size_;
        this->front_ = rhs.front_;
        this->back_ = rhs.back_;
        this->data_ = rhs.data_;

        rhs.capacity_ = 0;
        rhs.size_ = 0;
        rhs.front_ = 0;
        rhs.back_ = 0;
        rhs.data_ = nullptr;

        return *this;
    }
    template<typename T>
    ABDQ<T>::~ABDQ() noexcept 
    {
        capacity_ = 0;
        size_ = 0;
        
        back_ = 0;
        front_ = 0;

        delete[] data_;
        data_ = nullptr;
    }