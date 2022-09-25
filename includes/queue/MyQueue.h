#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;         //give access to list to access _ptr
        Iterator() { _ptr = NULL; } //default ctor
        Iterator(node<T> *p)
        { //Point Iterator to where
            //  p is pointing to
            _ptr = p;
        }
        T operator*() //dereference operator
        {
            return _ptr->_item;
        }
        bool is_null() //true if _ptr is NULL
        {
            return _ptr == NULL;
        }
        friend bool operator!=(const Iterator &left,
                               const Iterator &right) //true if left != right
        {
            return left._ptr != right._ptr;
        }
        friend bool operator==(const Iterator &left,
                               const Iterator &right) //true if left == right
        {
            return left._ptr == right._ptr;
        }
        Iterator &operator++()
        { //member operator:++it
            // or ++it = new_value
            return _ptr->_next;
        }
        friend Iterator operator++(Iterator &it,
                                   int unused)
        { //friend operator: it++
            assert(it._ptr != NULL);
            it._ptr = it._ptr->_next;
            return it._ptr;
        }

    private:
        node<T> *_ptr; //pointer being encapsulated
    };

    Queue()
    {
        _front = _rear = nullptr;
        _size = 0;
    }

    Queue(const Queue<T> &copyMe)
    {
        this->_front = _copy_list(copyMe._front);              // Inherit copied list by makeing the head point to it
        this->_size = copyMe._size;                            // Inherit size
        this->_rear = _search_tail(this->_front, this->_size); // Set rear
    }
    ~Queue()
    {
        _clear_list(_front);
    }
    Queue<T> &operator=(const Queue<T> &RHS)
    {
        if (this != &RHS)
        {
            _clear_list(this->_front);
            // if use copy constructor then can only copy once when initialize
            this->_front = _copy_list(RHS._front);
            this->_size = RHS._size;
            this->_rear = _search_tail(this->_front, this->_size);
        }
        return *this;
    }
    // Check if the list is empty
    bool empty()
    {
        return _size == 0;
    }
    // Find front element
    T front()
    {
        return _at(_front, 0);
    }
    // Find back element
    T back()
    {
        return _at(_rear, 0);
    }
    // Insert rear elements (First in)
    void push(T item)
    {
        _rear = _insert_after(_front, _rear, item);
        _size++;
        // point _front to where _rear point to if only one node
        if (_size == 1)
            _rear = _front;
    }
    // Remove front elements (First out)
    T pop()
    {
        if (_size > 0)
            _size--;
        T item = _delete_node(_front, _front);
        return item;
    }

    Iterator begin() const //Iterator to the head node
    {
        return Iterator(_front);
    }
    Iterator end() const //Iterator to NULL
    {
        return Iterator(nullptr);
    }
    void print_pointers() // What is this for?
    {
    }

    int size() const { return _size; }

    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe)
    {
        _print_list_backwards(printMe._front);
        return outs;
    }

private:
    node<T> *_front; // head
    node<T> *_rear;
    int _size;
};

#endif // QUEUE_H_
