#ifndef BTREE_ARRAY_FUNCTIONS_H_
#define BTREE_ARRAY_FUNCTIONS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>

using namespace std;

template <class T>
T maximal(const T &a, const T &b) //return the larger of the two items
{
    return (a >= b ? a : b);
}

template <class T>
void _swap(T &a, T &b) //swap the two items
{
    T c = a; // holds valud of a
    a = b;   // assign b to a
    b = c;   // assign original a to b
}

template <class T>
int index_of_maximal(T data[], int n) //return index of the largest item in data
{
    assert(n >= 0 && "Array size should be greater or equal to 0");

    if (n == 0) // Base case
        return 0;

    int index = 0;

    for (int i = 1; i < n; i++)
    {
        if (data[index] < data[i]) // find the greater item and set the index
            index = i;
    }
    return index;
}

template <class T>
void ordered_insert(T data[], int &n, T entry) //insert entry into the sorted array
{                                              //data with length n
    assert(n >= 0 && "Array size should be greater or equal to 0");

    T temp = entry;

    for (int i = 0; i < n; i++)
    {
        if (data[i] > temp)
            _swap(data[i], temp);
    }
    data[n] = temp; //temp was data[n-1] or is entry at this point
}

template <class T>
int first_ge(const T data[], int n, const T &entry) //return the index of the first item
{                                                   //that is not less than item
    assert(n >= 0);

    for (int i = 0; i < n; i++)
    {
        if (data[i] >= entry)
            return i;
    }
    return n; // return sze if item is larger than the last element in the list
}

template <class T>
void attach_item(T data[], int &n, const T &entry) //append entry to the right of data
{
    assert(n >= 0);

    data[n] = entry;
    n++;
}

template <class T>
void insert_item(T data[], int i, int &n, T entry) //insert entry at index i in data
{
    assert(i >= 0 && n >= 0 && i <= n);

    T temp = entry;

    if (data[i] == entry) //Overwritte
        data[i] = entry;
    for (int j = i; j < n; j++)
    {
        _swap(data[j], temp);
    }
    attach_item(data, n, temp);
}

template <class T>
void detach_item(T data[], int &n, T &entry) //remove the last element in data and place
{                                            //it in entry
    assert(n >= 0);

    if (n == 0)
        return;
    entry = data[n - 1]; // place last element of data in entry
    n--;
}

template <class T>
void delete_item(T data[], int i, int &n, T &entry) //delete item at index i and place it in entry
{
    assert(i >= 0 && n >= 0 && i <= n);

    if (n == 0)
        return;
    entry = data[i];
    for (int j = i; j < n - 1; j++)
    {
        _swap(data[j], data[j + 1]);
    }
    detach_item(data, n, entry);
}

template <class T>
void merge(T data1[], int &n1, T data2[], int &n2) //append data2 to the right of data1
{
    assert(n1 >= 0 && n2 >= 0);

    for (int i = 0; i < n2; i++)
    {
        data1[n1 + i] = data2[i];
    }
    n1 += n2;
    n2 = 0;
}

template <class T>
void split(T data1[], int &n1, T data2[], int &n2) //move n/2 elements from the right of data1
{                                                  //and move to data2
    assert(n1 > 1 && n2 >= 0);

    int half = n1 / 2;

    for (int i = 0; i < half; i++)
    {
        data2[i] = data1[(n1 - half) + i];
    }
    n2 += half;
    n1 -= half;
}

template <class T>
void copy_array(T dest[], const T src[],
                int &dest_size, int src_size) //copy src[] into dest[]
{
    assert(dest_size >= 0 && src_size >= 0);

    for (int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
    dest_size = src_size;
}

template <class T>
void print_array(const T data[], int n, int pos = -1) //print array data
{
    bool debug = false;
    for (int i = 0; i < n; i++)
    {
        std::cout << "[" << data[i] << "]";
    }
    if (debug)
        std::cout << std::endl
                  << std::setw(4 * pos) << "^" << std::endl;
    std::cout << std::endl;
}

template <class T>
bool is_gt(const T data[], int n, const T &item) //item > all data[i]
{
    for (int i = 0; i < n; i++)
    {
        if (data[i] >= item)
            return false;
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T &item) //item <= all data[i]
{
    for (int i = 0; i < n; i++)
    {
        if (data[i] < item)
            return false;
    }
    return true;
}

#endif // BTREE_ARRAY_FUNCTIONS_H_
