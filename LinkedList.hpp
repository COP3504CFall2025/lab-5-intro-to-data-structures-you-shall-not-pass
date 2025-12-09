#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;
};

template <typename T>
class LinkedList {

public:
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last Node<T>s and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


	// Behaviors
    template <typename T>
	void LinkedList<T>::printForward() const 
    {
        if (!(count == 0 || getHead() == nullptr))
        {
            const Node<T>* curr = getHead();
            for (size_t i = 0; i < count; i++)
            {
				if (curr != nullptr) {
                	cout << (*curr).data << ", ";
                	curr = (*curr).next;
				}
            }
            cout << endl;
        }
    }
    template <typename T>
	void LinkedList<T>::printReverse() const
    {
        if (!(count == 0 || getTail() == nullptr))
        {
            const Node<T>* curr = getTail();
            for (size_t i = 0; i < count; i++)
            {
				if (curr != nullptr) {
                	cout << (*curr).data << ", ";
                	curr = (*curr).prev;
				}
            }
            cout << endl;
        }
    }

	// Accessors
    
    template <typename T>
	[[nodiscard]] unsigned int LinkedList<T>::getCount() const { return count; }

    template <typename T>
	Node<T>* LinkedList<T>::getHead() { return head; }

    template <typename T>
	const Node<T>* LinkedList<T>::getHead() const { return head; }

    template <typename T>
	Node<T>* LinkedList<T>::getTail() { return tail; }

    template <typename T>
	const Node<T>* LinkedList<T>::getTail() const { return tail; }

	// Insertion
    template <typename T>
	void LinkedList<T>::addHead(const T& data)
    {
        if (count == 0 || getHead() == nullptr)
        {
            Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
            this->head = newNode;
            this->tail = newNode;
            count = 1;
        }
        else
        {
            Node<T>* currHead = getHead();
            Node<T>* newHead = new Node<T>{ data, nullptr, currHead };
            (*currHead).prev = newHead; 
            this->head = newHead;
            this->count++;
        }
    }
    template <typename T>
	void LinkedList<T>::addTail(const T& data)
    {
        if (count == 0 || getTail() == nullptr)
        {
            Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
            this->head = newNode;
            this->tail = newNode;
            count = 1;
        }
        else
        {
            Node<T>* currTail = getTail();
            Node<T>* newTail = new Node<T>{ data, currTail, nullptr };
            (*currTail).next = newTail;
            this->tail = newTail;
            this->count++;
        }
    }

	// Removal
    template <typename T>
	bool LinkedList<T>::removeHead()
    {
        if (!(count == 0 || getHead() == nullptr))
        {
			Node<T>* prevHead = head;
            Node<T>* newHead = head->next;
            this->head = newHead;

            if (newHead == nullptr)
                this->tail = nullptr;
            else  
                newHead->prev = nullptr;
            
            delete prevHead;

            this->count--;

            return true;
        }
		else
		{
			return false;
		}
    }
    template <typename T>
	bool LinkedList<T>::removeTail()
    {
        if (!(count == 0 || getHead() == nullptr))
        {
			Node<T>* pastTail = tail;
            Node<T>* newTail = tail->prev;
            this->tail = newTail;

            if (newTail == nullptr)
                this->head = nullptr;
            else  
                newTail->next = nullptr;
            
            delete pastTail;

            this->count--;

            return true;
        }
		else
		{
			return false;
		}
    }
    template <typename T>
	void LinkedList<T>::clear()
    {   
        Node<T>* curr = this->head;

        while (curr != nullptr)
        {
            Node<T>* tempNext = curr->next;
            delete curr;
		    curr = tempNext;
        }

        this->count = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

	// Operators
    template <typename T>
	LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept
    {
        if (this == &other) return *this;

        this->clear();

        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

        return *this;
    }
    template <typename T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
    {
        if (&rhs == this)
            return *this;

        this->clear();

        if (rhs.getCount() == 0)
            return *this;
            
        const Node<T>* currNode = rhs.getHead();

        this->addHead((*currNode).data);
        currNode = (*currNode).next;

        unsigned int i = 1;
        for (i = 1; i < rhs.getCount(); i ++)
        {
            this->addTail((*currNode).data);
            currNode = (*currNode).next;
        }

        return *this;
    }

	// Construction/Destruction
    template <typename T>
	LinkedList<T>::LinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    template <typename T>
	LinkedList<T>::LinkedList(const LinkedList<T>& list)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;

        if (list.getCount() == 0)
            return;

        const Node<T>* currNode = list.getHead();

        this->addHead((*currNode).data);
        currNode = (*currNode).next;

        unsigned int i = 1;
        for (; i < list.count; i++)
        {
            this->addTail((*currNode).data);
            currNode = (*currNode).next;
        }
    }
    template <typename T>
	LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
    {
        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
    template <typename T>
	LinkedList<T>::~LinkedList()
    {
        this->clear();
    }