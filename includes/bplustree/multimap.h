#ifndef MULTIMAP_H_
#define MULTIMAP_H_

#include <vector>
#include <iomanip>
#include "bplustree.h"

template <typename K, typename V>
struct MPair
{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K &k = K()) : key(k)
    {
        //WENT THOUGH TESTB
    }
    MPair(const K &k, const V &v) : key(k)
    {
        //NOT TESTED

        value_list.push_back(v);
    }
    MPair(const K &k, const vector<V> &vlist) : key(k), value_list(vlist)
    {
        //NOT TESTED
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream &operator<<(ostream &outs, const MPair<K, V> &print_me)
    {
        //WENT THOUGH TESTB

        cout << setw(10) << print_me.key << ":   ";
        for (auto i = print_me.value_list.begin(); i != print_me.value_list.end(); ++i)
        {
            cout << *i << " ";
        }
        return outs;
    }

    friend bool operator==(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key == rhs.key;
    }
    friend bool operator!=(const MPair<K, V> &lhs, const MPair<K, V> &rhs) //custom
    {
        //WENT THOUGH TESTB

        return lhs.key != rhs.key;
    }
    friend bool operator<(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key < rhs.key;
    }
    friend bool operator<=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key <= rhs.key;
    }
    friend bool operator>(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key > rhs.key;
    }
    friend bool operator>=(const MPair<K, V> &lhs, const MPair<K, V> &rhs) //custom
    {
        //WENT THOUGH TESTB

        return lhs.key >= rhs.key;
    }
    friend MPair<K, V> operator+(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        //TESTED

        MPair<K, V> copy;
        copy = lhs;
        for (auto i = rhs.value_list.begin(); i != rhs.value_list.end(); ++i)
            copy.value_list.push_back(*i);

        return copy;
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V>> map_base;
    class Iterator
    {
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it) : _it(it)
        {
            //TESTED
        }
        Iterator operator++(int unused)
        {
            //NOT TESTED

            Iterator original(_it);
            _it++;
            return original;
        }
        Iterator operator++()
        {
            //WENT THOUGH TESTB

            ++_it;
            return *this;
        }
        MPair<K, V> operator*()
        {
            //WENT THOUGH TESTB

            MPair<K, V> mpair = *_it;
            return mpair;
        }
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            //WENT THOUGH TESTB

            return lhs._it == rhs._it; //true if left == right
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            //WENT THOUGH TESTB

            return lhs._it != rhs._it; //true if left != right
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap() : mmap(BPlusTree<MPair<K, V>>(true))
    {
        //WENT THOUGH TESTB
    }

    //  Iterators
    Iterator begin()
    {
        //WENT THOUGH TESTB

        return mmap.begin();
    }
    Iterator end()
    {
        //WENT THOUGH TESTB

        return mmap.end();
    }

    //  Capacity
    int size() const
    {
        //TESTED

        return mmap.size();
    }
    bool empty() const
    {
        //TESTED

        return mmap.empty();
    }

    //  Element Access
    const vector<V> &operator[](const K &key) const
    {
        //TESTED

        MPair<K, V> mpair(key);
        return mmap.get(mpair).value_list;
    }
    vector<V> &operator[](const K &key)
    {
        //WENT THOUGH TESTB

        return get(key);
    }
    //  Modifiers
    void insert(const K &k, const V &v)
    {
        //WENT THOUGH TESTB

        MPair<K, V> mpair(k, v);
        mmap.insert(mpair);
    }
    void erase(const K &key)
    {
        //WENT THOUGH TESTB

        MPair<K, V> mpair(key);
        mmap.remove(key);
    }
    void clear()
    {
        //WENT THOUGH TESTB

        mmap.clear_tree();
    }

    //  Operations:
    bool contains(const K &key) const
    {
        //WENT THOUGH TESTB

        MPair<K, V> mpair(key);
        return mmap.contains(mpair);
    }
    vector<V> &get(const K &key)
    {
        //WENT THOUGH TESTB

        MPair<K, V> mpair(key);
        return mmap.get(mpair).value_list;
    }

    Iterator find(const K &key)
    {
        //WENT THOUGH TESTB

        MPair<K, V> mpair(key);
        return mmap.find(mpair);
    }
    int count(const K &key)
    {
        //NOT TESTED

        int _count = 0;
        vector<V> vec = get(key);
        for (auto i = vec.begin(); i != vec.end(); ++i)
            _count++;
        return _count;
    }

    // I have not writtent hese yet, but we will need them:
    //    equal_range:

    Iterator lower_bound(const K &key)
    {
        //TESTED

        return mmap.lower_bound(MPair<K, V>(key));
    }
    Iterator upper_bound(const K &key)
    {
        //TESTED

        return mmap.upper_bound(MPair<K, V>(key));
    }

    bool is_valid()
    {
        //WENT THOUGH TESTB

        return mmap.is_valid();
    }

    friend ostream &operator<<(ostream &outs, const MMap<K, V> &print_me)
    {
        // UNTOUCHED

        outs << print_me.mmap << endl;
        return outs;
    }

    void print_lookup() //print mmap as a table
    {
        // TESTED: in Table

        mmap.print_table();
    }

private:
    BPlusTree<MPair<K, V>> mmap;
};

#endif // MULTIMAP_H_
