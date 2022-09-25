#ifndef VECTOR_UTILITIES_H_
#define VECTOR_UTILITIES_H_

#include <algorithm> //sort
#include <iostream> 
#include <vector>

using namespace std;

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) //print vector list
{
    //WENT THOUGH BASIC TEST

    for(auto i = list.begin(); i != list.end(); ++i)
    {
        cout << *i << " ";
    }
    return outs;
}

template <typename T>
vector<T>& operator += (vector<T>& list, const T& addme) //add element to vector
{
    //WENT THOUGH BASIC TEST

    list.push_back(addme);
    return list;
}

// template <typename T, typename U>
// vector<T>& operator += (vector<T>& list, const U& addme) //DONNO
// {
//     //NOT TESTED

//     list.push_back(addme);
//     return list;
// }

template <typename T>
vector<T>& operator +=(vector<T>& list, const vector<T>& append_me) //add rvector to lvector
{
    //WENT THOUGH BASIC TEST

    for(auto i : append_me)
    {
        list.push_back(i);
    }
    return list;
}

template <typename T>
vector<T> vector_instersection(vector<T> &v1, vector<T> &v2) 
{
    //WENT THOUGH BASIC TEST

    vector<T> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(),
                     v2.begin(), v2.end(),
                     back_inserter(v3));
    return v3;
}

template <typename T>
vector<T> vector_union(vector<T> &v1, vector<T> &v2)
{
    //WENT THOUGH BASIC TEST

    vector<T> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_union(v1.begin(), v1.end(),
              v2.begin(), v2.end(),
              back_inserter(v3));
    return v3;
}

template <typename T>
bool is_subset(vector<T> v1, vector<T> v2)
{
    //WENT THOUGH BASIC TEST

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    return includes(v1.begin(), v1.end(), v2.begin(), v2.end());
}

#endif  // VECTOR_UTILITIES_H_
