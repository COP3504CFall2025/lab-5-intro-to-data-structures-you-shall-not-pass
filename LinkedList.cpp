#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

public:
	// Behaviors
	void printForward() const 
    {
        Node* curr = getHead();
        for (int i = 0; i < count; i++)
        {
            cout << *curr.data << ", ";
            curr = curr.next;
        }
        cout << endl;
    }
	void printReverse() const
    {
        Node* curr = getTail();
        for (int i = 0; i < count; i++)
        {
            cout << *curr.data << ", ";
            curr = curr.prev;
        }
        cout << endl;
    }

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }

	Node* getHead() { return head; }

	const Node* getHead() const { return head; }

	Node* getTail() { return tail; }

	const Node* getTail() const { return tail; }

	// Insertion
	void addHead(const T& data)
    {
        if (count == 0 || getHead() == nullptr)
        {
            Node newNode = {data, nullptr, nullptr}
            this->head = *newNode;
            this->tail = *newNode;
            count = 1;
        }
        else
        {
            Node* currHead = getHead();
            Node newHead = { data, nullptr, &currHead };
            if (*currHead.prev != nullptr)
                *currHead.prev = &newHead; 
            this->head = &newHead;
            this->count++;
        }
    }
	void addTail(const T& data)
    {
        if (count == 0 || getTail() == nullptr)
        {
            Node newNode = {data, nullptr, nullptr}
            this->head = *newNode;
            this->tail = *newNode;
            count = 1;
        }
        else
        {
            Node* currTail = getTail();
            Node newTail = { data, &currTail, nullptr };
            if (*currHead.next != nullptr)
                *currHead.next = &newTail;
            this->tail = &newTail;
            this->count++;
        }
    }

	// Removal
	bool removeHead()
    {
        if (!(count == 0 || getTail() = nullptr))
        {
            Node* currHead = getHead();
            Node* newHead = currHead.next;
            delete currHead;
            if (*newHead.prev != nullptr)
                *newHead.prev = nullptr;
            this->head = newHead;
            this->count--;
        }
    }
	bool removeTail()
    {
        if (count == 0 || getTail() = nullptr)
        {
            // idk why i did this
        }
        else
        {
            Node* currTail = getTail();
            Node* newTail = currTail.prev;
            delete currTail; 
            if (*newTail.next != nullptr)
                *newTail.next = nullptr;
            this->tail = newTail;
            this->count--;
        }
    }
	void Clear()
    {
        if (!(count == 0 || getHead() = nullptr))
        {    
            Node* curr = getHead();
            for (int i = 0; i < count; i++)
            {
                Node* temp = curr;
                curr = *curr.next;
                delete temp;
            }
            this->count = 0;
        }
    }

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
    {
        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other->head = nullptr;
        other->tail = nullptr;
        other->count = 0;

        return this;
    }
	LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        this->Clear();
    
        if (this->count == 0 || rhs.count == 0)
        {
            return this;
        }

        Node* currNode = rhs.getHead();
        for (int i = 0; i < count; i ++)
        {
            this->addTail(currNode);
            *currNode = *currNode.next;
        }

        this->count = rhs.count;

        return this;
    }

	// Construction/Destruction
	LinkedList()
    {
        this->head = nullptr;
        this->head = nullptr;
        this->count = 0;
    }
	LinkedList(const LinkedList<T>& list)
    {
        Node* currNode = other.getHead();
        for (int i = 0; i < count; i ++)
        {
            this->addTail(currNode);
            *currNode = *currNode.next;
        }
    }
	LinkedList(LinkedList<T>&& other) noexcept
    {
        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other->head = nullptr;
        other->tail = nullptr;
        other->count = 0;
    }
	~LinkedList()
    {
        this->Clear();
    }

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};


