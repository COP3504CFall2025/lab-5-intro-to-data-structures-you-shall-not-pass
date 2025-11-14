#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T>* list;

public:
    // Constructor
    LLDQ()
    {
        LinkedList<T>* list = new LinkedList<T>();
    }

    // Core Insertion Operations
    void pushFront(const T& item) override
    {
        list->addHead(item);
    }
    void pushBack(const T& item) override
    {
        list->addTail(item);
    }

    // Core Removal Operations
    T popFront() override
    {
        Node<T>* o = list->getHead();
        list->removeHead();
        return *o;
    }
    T popBack() override
    {
        Node<T>* o = list->getTail();
        list->removeTail();
        return o;
    }  

    // Element Accessors
    const T& front() const override
    {
        return list->getHead();
    }
    const T& back() const override
    {
        return list->getTail();
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return list->getCount();
    }
};






