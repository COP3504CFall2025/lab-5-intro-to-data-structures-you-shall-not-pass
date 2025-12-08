#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor  
    LLS()
    {
    }

    // Insertion
    void push(const T& item) override
    {
        list.addTail(item);
    }

    // Deletion
    T pop() override
    {
        if (list.getCount() == 0)
            throw std::runtime_error("Cannot pop an empty stack");

        T o = list.getTail()->data;
        list.removeTail();
        return o;
    }

    // Access
    T peek() const override
    {
        if (list.getCount() == 0)
            throw std::runtime_error("Cannot peek an empty stack");

        return list.getTail()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override
    {
        return list.getCount();
    }
};


