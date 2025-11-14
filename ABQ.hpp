#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept;

    // Get the number of items in the ABQ
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABQ
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

private:
    size_t capacity_;
    size_t curr_size_;
    T* top;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

    // Big 5 + Parameterized Constructor
    template<typename T>
    ABQ<T>::ABQ()
    {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
        top = array_;
    }
    template<typename T>
    ABQ<T>::ABQ(const size_t capacity)
    {
        this->capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
        top = array_;
    }
    template<typename T>
    ABQ<T>::ABQ(const ABQ& other)
    {
        this->capacity_ = other.getMaxCapacity();
        this->curr_size_ = other.getSize();
        this->top = other.top;

        this->array_ = new T[capacity_];
        T* curr = other.getData(); // points to curr element to copy into new array
        T* temp = array_; // points to curr element of the new array to copy into 
        for (size_t i = 0; i < curr_size_; i++)
        {
            *temp = *curr;
            curr++;
            temp++;
        }
    }
    template<typename T>
    ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs)
    {
        if (&rhs = this)
            return *this;
        
        delete[] this->array_;
        this->array = new T[capacity_];
        
        this->capacity_ = rhs.getMaxCapacity();
        this->curr_size_ = rhs.getSize();
        this->top = rhs.peek();

        T* curr = rhs.getData(); // points to curr element to copy into new array
        T* temp = array_; // points to curr element of the new array to copy into 
        for (size_t i = 0; i < curr_size_; i++)
        {
            *temp = *curr;
            curr++;
            temp++;
        }

        return *this;
    }
    template<typename T>
    ABQ<T>::ABQ(ABQ&& other) noexcept
    {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->top = other.top;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.top = nullptr;
        other.array_ = nullptr;
    }
    template<typename T>
    ABQ<T>& ABQ<T>::operator=(ABQ<T>&& rhs) noexcept
    {
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->top = rhs.top;
        this->array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.top = nullptr;
        rhs.array_ = nullptr;

        return *this;
    }
    template<typename T>
    ABQ<T>::~ABQ() noexcept 
    {
        capacity_ = 0;
        curr_size_ = 0;
        
        top = nullptr;

        delete[] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABQ
    template<typename T>
    [[nodiscard]] size_t ABQ<T>::getSize() const noexcept
    {
        return curr_size_;
    }

    // Get the max size of the ABQ
    template<typename T>
    [[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept
    {
        return capacity_;
    }

    // Return underlying data for the stack
    template<typename T>
    [[nodiscard]] T* ABQ<T>::getData() const noexcept
    {
        return array_;
    }

    // Push item onto the stack
    template<typename T>
    void ABQ<T>::enqueue(const T& data) 
    {
        curr_size_++;
        if (curr_size_ > capacity_)
        {
            capacity_ *= scale_factor_;
            
        }
        
        T* temp = new T[capacity_];
        for (size_t i = 1; i < curr_size_; i++)
        {
            *(temp + i) = *(array_ + i);
        }
        delete[] array_;
        array_ = temp;
        temp = nullptr;
        
        *(array_) = data;
        top = (array_ + (curr_size_ - 1));
    }

    template<typename T>
    T ABQ<T>::peek() const 
    {
        if (curr_size_ == 0)
            throw;
        return *top;
    }

    template<typename T>
    T ABQ<T>::dequeue() 
    {
        T o = this->peek();

        if (curr_size_ == 0)
            throw;

        curr_size_--;

        top = (array_ + (curr_size_ - 1));

        return o;
    }