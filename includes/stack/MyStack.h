#ifndef STACK_H_
#define STACK_H_

#include <iostream> //ostream
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename ITEM_TYPE>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack; //give access to list to access _ptr

        Iterator() { _ptr = NULL; } //default ctor

        Iterator(node<ITEM_TYPE> *p)
        {   //Point Iterator to where
            //p is pointing to
            _ptr = p;
        }

        ITEM_TYPE operator*() //dereference operator
        {
            return _ptr->_item;
        }

        bool is_null() { return _ptr == NULL; } //true if _ptr is NULL

        friend bool operator!=(const Iterator &left,
                               const Iterator &right)
        {
            return left._ptr != right._ptr; //true if left != right
        }
        friend bool operator==(const Iterator &left,
                               const Iterator &right)
        {
            return left._ptr == right._ptr; //true if left == right
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
        node<ITEM_TYPE> *_ptr; //pointer being encapsulated
    };

    Stack()
    {
        _top = nullptr;
        _size = 0;
    }
    Stack(const Stack<ITEM_TYPE> &copyMe)
    {
        this->_top = _copy_list(copyMe._top);
        this->_size = copyMe._size;
    }
    ~Stack()
    {
        _clear_list(_top);
    }
    Stack<ITEM_TYPE> &operator=(const Stack<ITEM_TYPE> &RHS)
    {
        if (this != &RHS)
        {
            _clear_list(this->_top);
            // if use copy constructor then can only copy once when initialize
            this->_top = _copy_list(RHS._top);
            this->_size = RHS._size;
        }
        return *this;
    }
    // Find top element
    ITEM_TYPE top()
    {
        return _at(_top, 0);
    }
    // See if stack is empty
    bool empty()
    {
        return _size == 0;
    }
    // Insert element (Last in)
    void push(ITEM_TYPE item)
    {
        _insert_before(_top, _top, item);
        _size++;
    }
    // Remove top element (First out)
    ITEM_TYPE pop()
    {
        _size--;
        return _delete_node(_top, _top);
    }
    template <typename T>
    friend ostream &operator<<(ostream &outs, const Stack<T> &printMe)
    {
        _print_list(printMe._top);
        return outs;
    }
    Iterator begin() const //Iterator to the head node
    {
        return Iterator(_top);
    }
    Iterator end() const //Iterator to NULL
    {
        return Iterator(nullptr);
    }
    int size() const
    {
        return _size;
    }

private:
    node<ITEM_TYPE> *_top; // Point to top node (head)
    int _size;             // Size of the stack (list)
};

#endif // STACK_H_
