#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ()
    {
        LinkedList<T> list = new LinkedList<T>();
    }

    // Core Insertion Operations
    void pushFront(const T& item) override
    {
        list.addHead(item);
    }
    void pushBack(const T& item) override
    {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override
    {
        list.removeHead();
    }
    T popBack() override
    {
        list.removeTail();
    }  

    // Element Accessors
    const T& front() const override
    {
        return list.head();
    }
    const T& back() const override
    {
        return list.tail();
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return list.getCount();
    }
};






