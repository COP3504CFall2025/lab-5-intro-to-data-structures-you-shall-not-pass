#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

private:
    size_t capacity_;
    size_t curr_size_;
    T* top;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

    // Big 5 + Parameterized Constructor
    template<typename T>
    ABS<T>::ABS()
    {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
        top = array_;
    }
    template<typename T>
    ABS<T>::ABS(const size_t capacity)
    {
        this->capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
        top = array_;
    }
    template<typename T>
    ABS<T>::ABS(const ABS& other)
    {
        this->capacity_ = other.getMaxCapacity();
        this->curr_size_ = other.getSize();
        this->top = other.top;

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
    ABS<T>& ABS<T>::operator=(const ABS<T>& rhs)
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
        for (int i = 0; i < curr_size_; i++)
        {
            *temp = *curr;
            curr++;
            temp++;
        }
    }
    template<typename T>
    ABS<T>::ABS(ABS&& other) noexcept
    {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->top = other.top;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.top = nullptr;
        other.array_ = nullptr;

        delete other;
        other = nullptr;
    }
    template<typename T>
    ABS<T>& ABS<T>::operator=(ABS<T>&& rhs) noexcept
    {
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->top = rhs.top;
        this->array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.top = nullptr;
        rhs.array_ = nullptr;

        delete rhs;
        rhs = nullptr;
    }
    template<typename T>
    ABS<T>::~ABS() noexcept 
    {
        capacity_ = 0;
        curr_size_ = 0;
        
        top = nullptr;

        delete[] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABS
    template<typename T>
    [[nodiscard]] size_t ABS<T>::getSize() const noexcept
    {
        return curr_size_;
    }

    // Get the max size of the ABS
    template<typename T>
    [[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept
    {
        return capacity_;
    }

    // Return underlying data for the stack
    template<typename T>
    [[nodiscard]] T* ABS<T>::getData() const noexcept
    {
        return array_;
    }

    // Push item onto the stack
    template<typename T>
    void ABS<T>::push(const T& data) 
    {
        curr_size_++;
        if (curr_size_ > capacity_)
        {
            capacity_ *= scale_factor_;
            T* temp = new T[capacity_];
            for (int i = 0; i < curr_size_ - 1; i++)
            {
                *(temp + i) = *(array_ + i);
            }
            delete[] array_;
            array_ = temp;
            temp = nullptr;
        }
        
        *(array_ + (curr_size_ - 1)) = data;
        top = (array_ + (curr_size_ - 1));
    }

    template<typename T>
    T ABS<T>::peek() const 
    {
        if (curr_size_ == 0)
            throw;
        return *top;
    }

    template<typename T>
    T ABS<T>::pop() 
    {
        T o = this->peek();

        if (curr_size_ == 0)
            throw;

        curr_size_--;

        top = (array_ + (curr_size_ - 1));

        return o;
    }