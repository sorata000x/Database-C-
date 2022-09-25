#ifndef NODE_H_
#define NODE_H_

#include <iostream>

using namespace std;

template <class T>
struct node
{
    T _item;
    node<T> *_next;
    node<T> *_prev;
    node(const T &item = T(), node<T> *next = NULL, node<T> *prev = NULL) : _item(item),
                                                                            _next(next),
                                                                            _prev(prev) {}
    friend ostream &operator<<(ostream &outs, const node<T> &print_me)
    {
        outs << "[" << print_me._item << "]->";
        return outs;
    }
};

#endif // NODE_H_
