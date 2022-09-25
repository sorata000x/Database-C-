#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H_
#define LINKEDLISTFUNCTIONSTEMPLATED_H_

#include "../node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T> *head)
{
    printf("Head->");
    for (node<T> *np = head; np != nullptr; np = np->_next)
    {
        printf(" <-");
        printf("[%d]", np->_item);
        printf("->");
    }
    printf(" |||");
    printf("\n");
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    // Base Case
    if (head == nullptr)
        return;

    // call itself with head point to the next node
    _print_list_backwards(head->_next);

    // print the node after recursion done
    printf(" <-");
    printf("[%d]", head->_item);
    printf("->");
}

//return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head,
                      T key)
{
    for (node<T> *np = head; np != nullptr; np = np->_next)
    {
        if (np->_item == key)
        {
            return np; // ptr point to key
        }
    }
    return NULL;
}

template <typename T>
node<T> *_insert_head(node<T> *&head,
                      T insert_this)
{
    // allocate new node
    node<T> *np = new node<T>(insert_this);

    // make next of new node point to head and prev point to NULL
    np->_next = head;
    np->_prev = nullptr;

    // change previous head point to new node
    if (head != nullptr)
        head->_prev = np;

    // change head to new node
    head = np;

    return np;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T> *_insert_after(node<T> *&head,
                       node<T> *after_this,
                       T insert_this)
{
    // allocate new node
    node<T> *np = new node<T>(insert_this);

    if (head == nullptr)
    { // list is empty, insert head
        head = np;
    }
    else
    { // list is not empty, insert after ptr

        if (after_this->_next != NULL)
        {
            // change the next of after_this point prev to np
            after_this->_next->_prev = np;
            // make np point next to the next of after_this
            np->_next = after_this->_next;
        }

        // change after_this point next to np
        after_this->_next = np;
        // make np point prev to after_this
        np->_prev = after_this;
    }
    return np;
}

//insert before ptr: insert head if marker null
template <typename T>
node<T> *_insert_before(node<T> *&head,
                        node<T> *before_this,
                        T insert_this)
{
    node<T> *np = new node<T>(insert_this);
    if (head == nullptr)
    { // list is empty, insert head
        head = np;
    }
    else
    { // list is not empty, insert before ptr

        if (before_this->_prev != NULL)
        {
            // change the prev of before_this point next to np
            before_this->_prev->_next = np;
            // make np point prev to the prev of before_this
            np->_prev = before_this->_prev;
        }

        // change before_this point prev to np
        before_this->_prev = np;
        // make np point next to before_this
        np->_next = before_this;

        // change head
        if (before_this == head)
        {
            head = np;
        }
    }
    return np; // what inserted
}

//ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this)
{
    // NOTE: not sure what it means
    return prev_to_this->_prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    T item;
    // empty
    if (head == nullptr)
        return 0;

    if (head->_next == nullptr)
    {
        item = head->_item;
        head = nullptr;
        return item;
    }

    if (head == delete_this)
    {
        // change head to the next node
        head = delete_this->_next;
    }

    if (delete_this->_prev != NULL)
        // change prev node of delete_this point to next node of delete_this
        delete_this->_prev->_next = delete_this->_next;

    if (delete_this->_next != NULL)
        // change next node of delete_this point to prev node of delete_this
        delete_this->_next->_prev = delete_this->_prev;

    item = delete_this->_item;

    delete delete_this;

    return item; // what deleted
}

//duplicate the list... (return head)
template <typename T>
node<T> *_copy_list(node<T> *head)
{
    // Base case
    if (head == nullptr)
        return nullptr;

    node<T> *copy = new node<T>(); // Allocate a new list/node

    copy = new node<T>(head->_item); // copy head
    copy->_next = nullptr;           // no next node yet

    node<T> *const chead = copy; // keep track the head

    // copy node one by one and repeat until end
    for (node<T> *cur = head->_next; cur != nullptr; cur = cur->_next)
    {
        copy->_next = new node<T>(cur->_item);
        copy->_next->_prev = copy;
        copy = copy->_next;
        copy->_next = nullptr;
    }

    return chead;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T> *&head)
{
    // create a temp node
    node<T> *temp = new node<T>();

    // delete node one by one
    while (head != NULL)
    {
        temp = head;
        head = head->_next;
        free(temp);
    }
}

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos)
{
    node<T> *null = new node<T>();
    // Base case
    if (pos < 0)
        return null->_item;

    // find the pointer at the position
    node<T> *temp = head;
    for (int i = 0; i < pos; i++)
    {
        if (temp != nullptr)
        {
            temp = temp->_next;
        }
    }

    return temp->_item; // _item at the position
}

template <typename T>
node<T> *_search_tail(node<T> *head, int size)
{

    // Base case
    if (size <= 0)
        return nullptr;

    node<T> *temp = head;
    for (int i = 1; i < size; i++)
    {
        if (temp != nullptr)
        {
            temp = temp->_next;
        }
    }
    return temp;
}

#endif // LINKEDLISTFUNCTIONSTEMPLATED_H_
