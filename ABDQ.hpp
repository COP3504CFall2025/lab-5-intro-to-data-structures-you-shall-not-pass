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

    size_t getMaxCapacity() 
    {
        return capacity_;
    }

    T* getData()
    {
        return data_;
    }

    void ensureCapacity()
    {
        capacity_ *= SCALE_FACTOR;
        T* temp = new T[capacity_];
        size_t i = 0;
        for (i = 0; i < size_ - 1; i++)
        {
            *(temp + i) = *((data_ + front_ + i) % (capacity_ - 1));
        }
        delete[] data_;
        data_ = temp;
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
        size_++;
        if (size_ > capacity_)
        {
            ensureCapacity();
        }
        front_ = (front_ - 1) % capacity_;
        *((data_ + front_) % capacity_) = item;
    }
    void pushBack(const T& item) override
    {
        size_++;
        if (size_ > capacity_)
        {
            ensureCapacity();
        }
        back_ = (back_ + 1) % capacity_;
        *((data_ + back_) % capacity_) = item;
    }

    // Deletion
    T popFront() override
    {
        T o = *(data_ + front_);
        return o;
        front_ = (front_ + 1) % capacity_;
    }
    T popBack() override
    {
        T o = *(data_ + back_);
        back_ = (back_ - 1) % capacity_;
        return o;
    }

    // Access
    const T& front() const override
    {
        return *((data_ + front_) % capacity_);
    }
    const T& back() const override
    {
        return *((data_ + back_) % capacity_);
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
        this->back_ = other.back_;
        this->front_ = other.front_;

        this->data_ = new T[capacity_];
        T* curr = other.getData(); // points to curr element to copy into new data_
        T* temp = data_; // points to curr element of the new data_ to copy into 
        for (int i = 0; i < size_; i++)
        {
            *temp = *curr;
            curr++;
            temp++;
        }
    }
    template<typename T>
    ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs)
    {
        if (&rhs = this)
            return *this;
        
        delete[] this->data_;
        this->data_ = new T[capacity_];
        
        this->capacity_ = rhs.getMaxCapacity();
        this->size_ = rhs.getSize();
        this->back_ = rhs.back_;
        this->front_ = rhs.front_;


        T* curr = rhs.getData(); // points to curr element to copy into new data_
        T* temp = data_; // points to curr element of the new data_ to copy into 
        for (int i = 0; i < size_; i++)
        {
            *temp = *curr;
            curr++;
            temp++;
        }

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
        other.data_ = 0;
    }
    template<typename T>
    ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept
    {
        this->capacity_ = rhs.capacity_;
        this->size_ = rhs.size_;
        this->front_ = rhs.front_;
        this->back_ = rhs.back_;
        this->data_ = rhs.data_;

        rhs.capacity_ = 0;
        rhs.size_ = 0;
        rhs.front_ = 0;
        rhs.back_ = 0;
        rhs.data_ = 0;

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