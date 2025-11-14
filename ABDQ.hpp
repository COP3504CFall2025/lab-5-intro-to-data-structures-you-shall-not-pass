#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
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
    ~ABDQ() override;

    void expand()
    {
        capacity_ *= SCALE_FACTOR;
        T* temp = new T[capacity_];
        for (int i = 0; i < size_ - 1; i++)
        {
            *(temp + i) = *((array_ + front_ + i) % (capacity_ - 1));
        }
        delete[] array_;
        array_ = temp;
        temp = nullptr;        
    }

    // Insertion
    void pushFront(const T& item) override
    {
        size_++;
        size_++;
        if (size_ > capacity_)
        {
            
        }
        front_ = (front_ - 1) % capacity_;
        if ()
    }
    void pushBack(const T& item) override;
    {

    }

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;
};


    // Big 5 + Parameterized Constructor
    template<typename T>
    ABDQ<T>::ABDQ()
    {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
        back_ = 0;
        front_ = 0;
    }
    template<typename T>
    ABDQ<T>::ABDQ(const size_t capacity)
    {
        this->capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
        back_ = 0;
        front_ = 0;
    }
    template<typename T>
    ABDQ<T>::ABDQ(const ABDQ& other)
    {
        this->capacity_ = other.getMaxCapacity();
        this->curr_size_ = other.getSize();
        this->back_ = other.back_;
        this->front_ = other.front_;

        this->array_ = new T[capacity_];
        T* curr = other.getData(); // points to curr element to copy into new array
        T* temp = array_; // points to curr element of the new array to copy into 
        for (int i = 0; i < curr_size_; i++)
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
        
        delete[] this->array_;
        this->array = new T[capacity_];
        
        this->capacity_ = rhs.getMaxCapacity();
        this->curr_size_ = rhs.getSize();
        this->back_ = rhs.back();
        this->front_ = rhs.front();


        T* curr = rhs.getData(); // points to curr element to copy into new array
        T* temp = array_; // points to curr element of the new array to copy into 
        for (int i = 0; i < curr_size_; i++)
        {
            *temp = *curr;
            curr++;
            temp++;
        }
    }
    template<typename T>
    ABDQ<T>::ABDQ(ABDQ&& other) noexcept
    {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->back_ = other.back_;
        this->front_ = other.front_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        this->front_ = nullptr;
        other.back_ = nullptr;
        other.array_ = nullptr;

        delete other;
        other = nullptr;
    }
    template<typename T>
    ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept
    {
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->front_ = rhs.front_;
        this->back_ = rhs.back_;
        this->array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        this->front_ = nullptr;
        rhs.back_ = nullptr;
        rhs.array_ = nullptr;

        delete rhs;
        rhs = nullptr;
    }
    template<typename T>
    ABDQ<T>::~ABDQ() noexcept 
    {
        capacity_ = 0;
        curr_size_ = 0;
        
        back_ = nullptr;

        delete[] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABDQ
    template<typename T>
    [[nodiscard]] size_t ABDQ<T>::getSize() const noexcept
    {
        return curr_size_;
    }