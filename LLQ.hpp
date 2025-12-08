#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor 
    LLQ()
    {
    }

    // Insertion
    void enqueue(const T& item) override
    {
        list.addHead(item);
    }

    // Deletion
    T dequeue() override
    {
        if (list.getCount() == 0)
            throw std::runtime_error("Cannot dequeue from an empty queue.");

        T o = list.getTail()->data;
        list.removeTail();
        return o;
    }

    // Access
    T peek() const override
    {
        if (list.getCount() == 0)
            throw std::runtime_error("Cannot peek into an empty queue.");

        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return list.getCount();
    }

};